/**
* @file GameOverState.cpp
 * @brief Implementation of the GameOverState.
 */
#include "GameOverState.hpp"
#include "PlayState.hpp"
#include "StateMachine.hpp"

GameOverState::GameOverState(StateMachine &machine, sf::RenderWindow &window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus, sf::Font& font, int score)
: m_stateMachine(machine)
, m_window(window)
, m_coordinator(coordinator)
, m_eventBus(eventBus)
, m_font(font)
, m_score(score)
{
}

void GameOverState::OnEnter()
{
    sf::Text score;
    score.setFont(m_font);
    score.setString("Your score is: " + std::to_string(m_score));
    score.setCharacterSize(32);
    score.setFillColor(sf::Color::White);

    sf::Text title;
    title.setFont(m_font);
    title.setString("Game Over");
    title.setCharacterSize(64);
    title.setFillColor(sf::Color(176, 161, 28));
    title.setOutlineColor(sf::Color(255, 255, 255));
    title.setOutlineThickness(8);

    sf::Text subtitle;
    subtitle.setFont(m_font);
    subtitle.setString("Press space to restart the game");
    subtitle.setCharacterSize(32);
    subtitle.setFillColor(sf::Color::White);

    float winWidth  = static_cast<float>(m_window.getSize().x);
    float winHeight = static_cast<float>(m_window.getSize().y);

    sf::FloatRect score_rect = score.getLocalBounds();
    sf::FloatRect title_rect = title.getLocalBounds();
    sf::FloatRect subtitle_rect = subtitle.getLocalBounds();

    float spacing = 80.f;
    float totalHeight = score_rect.height + spacing + title_rect.height + spacing + subtitle_rect.height;

    score.setOrigin(score_rect.width / 2.f, score_rect.height / 2.f);
    title.setOrigin(title_rect.width / 2.f, title_rect.height / 2.f);
    subtitle.setOrigin(subtitle_rect.width / 2.f, subtitle_rect.height / 2.f);

    float centerX = winWidth / 2.f;
    float centerY = winHeight / 2.f;

    score.setPosition(centerX, centerY - (totalHeight / 2.f) + (score_rect.height / 2.f));
    title.setPosition(centerX, centerY);
    subtitle.setPosition(centerX, centerY + (totalHeight / 2.f) - (subtitle_rect.height / 2.f));

    m_text.push_back(score);
    m_text.push_back(title);
    m_text.push_back(subtitle);
}

void GameOverState::OnExit()
{
    m_text.clear();
}

void GameOverState::HandleEvent(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        m_stateMachine.ChangeState(std::make_unique<PlayState>(
            m_stateMachine, m_window, m_coordinator, m_eventBus, m_font));
    }
}

void GameOverState::Update(float dt)
{
}

void GameOverState::Render(const float dt, sf::RenderWindow &window)
{
    for (auto& t : m_text)
        window.draw(t);
}

