/**
* @file InputSystem.hpp
 * @brief System that processes player input.
 *
 * The InputSystem interprets keyboard and mouse input and translates
 * it into movement vectors and weapon activations for the player entity.
 */
#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include <ecs/System.hpp>
#include <SFML/Graphics.hpp>

class InputSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the input system.
     * @param window The SFML window for mouse coordinates.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for input events.
     */
    InputSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus);

    /**
     * @brief Processes input and updates player entity.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    sf::RenderWindow& m_window;      // Reference to the SFML window
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator
    ecs::EventBus&    m_eventBus;     // Reference to the event bus
};

#endif //INPUTSYSTEM_HPP