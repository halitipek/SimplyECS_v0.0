/**
 * @file MenuState.cpp
 * @brief Implementation of the MenuState.
 */
#include "MenuState.hpp"
#include "StateMachine.hpp"
#include "PlayState.hpp"

MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus, sf::Font& font)
: m_stateMachine(machine)
, m_window(window)
, m_coordinator(coordinator)
, m_eventBus(eventBus)
, m_font(font)
{
}

void MenuState::OnEnter()
{
    sf::Text title;
    title.setFont(m_font);
    title.setString("Geometry Wars");
    title.setCharacterSize(64);
    title.setFillColor(sf::Color(176, 161, 28));
    title.setOutlineColor(sf::Color(101, 92, 147));
    title.setOutlineThickness(8);

    sf::Text subtitle;
    subtitle.setFont(m_font);
    subtitle.setString("Press space to start the game");
    subtitle.setCharacterSize(32);
    subtitle.setFillColor(sf::Color::White);

    float winWidth  = static_cast<float>(m_window.getSize().x);
    float winHeight = static_cast<float>(m_window.getSize().y);

    sf::FloatRect title_rect = title.getLocalBounds();
    sf::FloatRect subtitle_rect = subtitle.getLocalBounds();

    float spacing = 80.f;
    float totalHeight = title_rect.height + spacing + subtitle_rect.height;

    title.setOrigin(title_rect.width / 2.f, title_rect.height / 2.f);
    subtitle.setOrigin(subtitle_rect.width / 2.f, subtitle_rect.height / 2.f);

    float centerX = winWidth / 2.f;
    float centerY = winHeight / 2.f;

    title.setPosition(centerX, centerY - (totalHeight / 2.f) + (title_rect.height / 2.f));
    subtitle.setPosition(centerX, centerY + (totalHeight / 2.f) - (subtitle_rect.height / 2.f));

    m_text.push_back(title);
    m_text.push_back(subtitle);
}

void MenuState::OnExit()
{
    m_text.clear();
}

void MenuState::HandleEvent(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Space)
            m_stateMachine.ChangeState(std::make_unique<PlayState>(
                m_stateMachine, m_window, m_coordinator, m_eventBus, m_font));
    }
}

void MenuState::Update(float dt)
{
}

void MenuState::Render(const float dt, sf::RenderWindow &window)
{
    for (auto& t : m_text)
        window.draw(t);
}
