/**
* @file StateMachine.hpp
 * @brief Manages game state transitions using the State Pattern.
 *
 * The StateMachine holds the current game state and handles transitions
 * between different states, delegating events, updates, and rendering
 * to the active state.
 */
#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <memory>
#include "State.hpp"

class StateMachine
{
public:
    /**
     * @brief Changes to a new game state.
     * @param newState The state to transition to.
     *
     * Calls OnExit() on the current state if it exists,
     * then sets the new state and calls OnEnter() on it.
     */
    void ChangeState(std::unique_ptr<State> newState);

    /**
     * @brief Delegates event handling to the current state.
     * @param event The SFML event to handle.
     */
    void HandleEvent(sf::Event &event) const;

    /**
     * @brief Delegates update logic to the current state.
     * @param dt Delta time since last update.
     */
    void Update(float dt) const;

    /**
     * @brief Delegates rendering to the current state.
     * @param dt Delta time since last render.
     * @param window The SFML window to render to.
     */
    void Render(float dt, sf::RenderWindow &window) const;

private:
    std::unique_ptr<State> m_currentState;  // Currently active game state
};

#endif //STATEMACHINE_HPP