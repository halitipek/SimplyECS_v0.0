/**
* @file State.hpp
 * @brief Abstract base class for game states in the State Pattern.
 *
 * The State interface defines the contract for all concrete game states,
 * allowing for different behaviors during various game phases like menu,
 * gameplay, and game over.
 */
#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

class StateMachine;

class State
{
public:
    virtual ~State() = default;

    /**
     * @brief Called when the state becomes active.
     *
     * Use this for initialization that should happen each time
     * the state is entered.
     */
    virtual void OnEnter() = 0;

    /**
     * @brief Called when the state is exited.
     *
     * Use this for cleanup before transitioning to another state.
     */
    virtual void OnExit() = 0;

    /**
     * @brief Handles input events in the current state.
     * @param event The SFML event to process.
     */
    virtual void HandleEvent(sf::Event& event) = 0;

    /**
     * @brief Updates game logic specific to this state.
     * @param dt Delta time since last update.
     */
    virtual void Update(float dt) = 0;

    /**
     * @brief Renders state-specific elements.
     * @param dt Delta time since last render.
     * @param window The SFML window to render to.
     */
    virtual void Render(float dt, sf::RenderWindow& window) = 0;
};

#endif //STATE_HPP