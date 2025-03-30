/**
 * @file Game.cpp
 * @brief Implementation of the Game.
 */
#include "Game.hpp"
#include "ECS/GameInit.hpp"
#include "Managers/ConfigManager.hpp"

#include "GameStates/MenuState.hpp"

Game::Game(const std::string& configPath)
: m_fpsCounter(0)
, m_currentFps(0)
{
    gConfig.LoadConfig(configPath);
    auto& [width, height, fps, title] = gConfig.GetGameConfig().window;

    m_window.create(sf::VideoMode(width, height), title);
    m_window.setFramerateLimit(fps);

    assert(m_font.loadFromFile(std::string(HOME_DIR) + "/resources/tech.ttf")
        && "Game: Font cannot load.");

    m_fpsText.setFont(m_font);
    m_fpsText.setString("FPS: " + std::to_string(m_currentFps));
    m_fpsText.setCharacterSize(18);
    m_fpsText.setFillColor(sf::Color::White);
    m_fpsText.setPosition(10.f, 10.f);
}

void Game::Init()
{
    m_coordinator.Init();
    GameInit::RegisterAllComponents(m_coordinator);
    GameInit::RegisterAllSystems(m_window, m_coordinator, m_eventBus);

    m_stateMachine.ChangeState(std::make_unique<MenuState>(m_stateMachine, m_window, m_coordinator, m_eventBus, m_font));
}

void Game::Run()
{
    sf::Clock clock;

    while(m_window.isOpen())
    {
        ProcessEvents();

        const float dt = clock.restart().asSeconds();

        Update(dt);
        Render(dt);
    }
}

void Game::ProcessEvents()
{
    sf::Event ev;
    while(m_window.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
            m_window.close();

        m_stateMachine.HandleEvent(ev);
    }
}

void Game::Update(const float dt)
{
    ++m_fpsCounter;

    if (m_fpsClock.getElapsedTime().asSeconds() >= 1.f)
    {
        m_currentFps = m_fpsCounter;
        m_fpsCounter = 0;
        m_fpsClock.restart();
    }

    m_stateMachine.Update(dt);
}

void Game::Render(const float dt)
{
    m_window.clear();

    m_stateMachine.Render(dt, m_window);

    m_fpsText.setString("FPS: " + std::to_string(m_currentFps));
    m_window.draw(m_fpsText);

    m_window.display();
}
