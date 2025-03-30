/**
* @file MenuState.hpp
 * @brief Game state for the main menu.
 *
 * The MenuState displays the game title and instructions to start,
 * handling user input to transition to the play state.
 */
#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>

class StateMachine;

class MenuState final : public State
{
public:
    /**
     * @brief Constructs the menu state.
     * @param machine Reference to the state machine for state transitions.
     * @param window Reference to the SFML window.
     * @param coordinator Reference to the ECS coordinator.
     * @param eventBus Reference to the event bus.
     * @param font Reference to the font used for text rendering.
     */
    MenuState(StateMachine& machine, sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus, sf::Font& font);

    void OnEnter() override;
    void OnExit() override;

    void HandleEvent(sf::Event& event) override;
    void Update(float dt) override;
    void Render(float dt, sf::RenderWindow& window) override;

private:
    StateMachine&     m_stateMachine;    // Reference to the state machine
    sf::RenderWindow& m_window;          // Reference to the SFML window
    ecs::Coordinator& m_coordinator;     // Reference to the ECS coordinator
    ecs::EventBus&    m_eventBus;        // Reference to the event bus

    sf::Font&             m_font;        // Font used for text rendering
    std::vector<sf::Text> m_text;        // Text elements to display
};

#endif //MENUSTATE_HPP