/**
* @file GameOverState.hpp
 * @brief Game state for the game over screen.
 *
 * The GameOverState displays the final score and provides an option
 * to restart the game.
 */
#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>

class StateMachine;

class GameOverState final : public State
{
public:
    /**
     * @brief Constructs the game over state.
     * @param machine Reference to the state machine for state transitions.
     * @param window Reference to the SFML window.
     * @param coordinator Reference to the ECS coordinator.
     * @param eventBus Reference to the event bus.
     * @param font Reference to the font used for text rendering.
     * @param score The final score to display.
     */
    GameOverState(StateMachine &machine, sf::RenderWindow &window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus, sf::Font& font, int score);

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

    int m_score;                         // Final score to display
    sf::Font& m_font;                    // Font used for text rendering
    std::vector<sf::Text> m_text;        // Text elements to display
};

#endif //GAMEOVERSTATE_HPP