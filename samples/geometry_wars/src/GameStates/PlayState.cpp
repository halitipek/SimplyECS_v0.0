/**
 * @file PlayState.cpp
 * @brief Implementation of the PlayState.
 */
#include <ecs/Coordinator.hpp>

#include "StateMachine.hpp"
#include "PlayState.hpp"

#include <Components/PlayerComponent.hpp>
#include <Components/ScoreComponent.hpp>
#include <Events/PlayerSpawnedEvent.hpp>
#include <Systems/CollisionResponseSystem.hpp>

#include "GameOverState.hpp"

#include "Systems/BoundarySystem.hpp"
#include "Systems/CollisionSystem.hpp"
#include "Systems/EnemySpawnSystem.hpp"
#include "Systems/HealthSystem.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/LifespanSystem.hpp"
#include "Systems/MovementSystem.hpp"
#include "Systems/ParticleSystem.hpp"
#include "Systems/WeaponSystem.hpp"

#include "Events/SpawnPlayerEvent.hpp"
#include "Events/ScoredEvent.hpp"
#include "Systems/AdvancedEnemySystem.hpp"

#include "Systems/RenderSystem.hpp"

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus, sf::Font& font)
: m_stateMachine(machine)
, m_window(window)
, m_coordinator(coordinator)
, m_eventBus(eventBus)
, m_font(font)
, m_currentFrame(0)
, m_frameCount(10)
, m_frameDuration(0.12f)
, m_elapsedTime(0.f)
, m_score(0)
, m_gameOver(false)
, m_paused(false)
, m_playerEntity(ecs::NullEntity)
{
    m_listenerIDArr[0] = m_eventBus.AddListener<PlayerSpawnedEvent>(
        [this](const PlayerSpawnedEvent& event) {
            m_playerEntity = event.entity;
        }
    );

    m_listenerIDArr[1] = m_eventBus.AddListener<PlayerDeadEvent>(
        [this](const PlayerDeadEvent& ev) {
            OnPlayerDead(ev);
        }
    );

    m_listenerIDArr[2] = m_eventBus.AddListener<ScoredEvent>(
        [this](const ScoredEvent& ev)
        {
            m_score += 10;
        }
    );

    m_blackOverlay.setSize(sf::Vector2f(
        static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y)));
    m_blackOverlay.setFillColor(sf::Color(0, 0, 0, 190));

    assert(m_texture.loadFromFile(std::string(HOME_DIR) + "/resources/bg.png")
        && "PlayState: Texture cannot load.");
    m_background.setTexture(m_texture);
    m_background.setPosition(0, 0);
    m_background.setTextureRect(sf::IntRect(0, 0,
        static_cast<int>(m_window.getSize().x), static_cast<int>(m_window.getSize().y)));

    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(18);
    m_scoreText.setFillColor(sf::Color(176, 161, 28, 255));

    m_coordinator.DestroyAllEntities();
    m_eventBus.Emit<SpawnPlayerEvent>({}, true);
}

void PlayState::OnPlayerDead(const PlayerDeadEvent& event)
{
    m_gameOver = true;
    m_score    = m_coordinator.GetComponent<ScoreComponent>(event.entity).value;
}

void PlayState::OnEnter()
{
}

void PlayState::OnExit()
{
    m_eventBus.RemoveListener<PlayerSpawnedEvent>(m_listenerIDArr[0]);
    m_eventBus.RemoveListener<PlayerDeadEvent>(m_listenerIDArr[1]);
    m_eventBus.RemoveListener<ScoredEvent>(m_listenerIDArr[2]);
    m_coordinator.DestroyAllEntities();
}

void PlayState::HandleEvent(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::P)
            m_paused = !m_paused;

        if(event.key.code == sf::Keyboard::Escape)
            m_eventBus.Emit<PlayerDeadEvent>({m_playerEntity});
    }
}

void PlayState::Update(const float dt)
{
    m_elapsedTime += dt;

    while (m_elapsedTime >= m_frameDuration)
    {
        m_elapsedTime -= m_frameDuration;
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;

        m_background.setTextureRect(sf::IntRect(
            static_cast<int>(m_window.getSize().x) * m_currentFrame, 0,
            static_cast<int>(m_window.getSize().x), static_cast<int>(m_window.getSize().y)));
    }

    auto sInput         = m_coordinator.GetSystem<InputSystem>();
    auto sWeapon        = m_coordinator.GetSystem<WeaponSystem>();
    auto sEnemySpawn    = m_coordinator.GetSystem<EnemySpawnSystem>();
    auto sAdvancedEnemy = m_coordinator.GetSystem<AdvancedEnemySystem>();
    auto sMovement      = m_coordinator.GetSystem<MovementSystem>();
    auto sBoundary      = m_coordinator.GetSystem<BoundarySystem>();
    auto sCollision     = m_coordinator.GetSystem<CollisionSystem>();
    auto sHealth        = m_coordinator.GetSystem<HealthSystem>();
    auto sLifespan      = m_coordinator.GetSystem<LifespanSystem>();
    auto sParticle      = m_coordinator.GetSystem<ParticleSystem>();

    if(!m_paused && !m_gameOver)
    {
        sInput->Update(dt);
        sWeapon->Update(dt);
        sEnemySpawn->Update(dt);
        sAdvancedEnemy->Update(dt);
        sMovement->Update(dt);
        sBoundary->Update(dt);
        sCollision->Update(dt);

        m_eventBus.ProcessEvents(); // *** PROCESS SYNC EVENTS ***

        sHealth->Update(dt);
        sLifespan->Update(dt);
        sParticle->Update(dt);
    }

    m_eventBus.ProcessEvents();
    m_coordinator.DestroyQueuedEntities();

    if (m_gameOver)
    {
        m_stateMachine.ChangeState(std::make_unique<GameOverState>(
            m_stateMachine, m_window, m_coordinator, m_eventBus, m_font, m_score));
    }
}

void PlayState::Render(const float dt, sf::RenderWindow &window)
{
    m_window.draw(m_background);
    m_window.draw(m_blackOverlay);

    auto sRender = m_coordinator.GetSystem<RenderSystem>();
    sRender->Update(dt);

    float winWidth = static_cast<float>(m_window.getSize().x);
    m_scoreText.setString("Score: " + std::to_string(m_score));
    sf::FloatRect score_rect = m_scoreText.getLocalBounds();
    m_scoreText.setPosition(winWidth - score_rect.width - 10, 10);
    m_window.draw(m_scoreText);
}
