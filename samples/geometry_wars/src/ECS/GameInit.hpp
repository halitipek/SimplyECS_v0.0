/**
 * @file GameInit.hpp
 * @brief Initializes the ECS components and systems for the game.
 *
 * The GameInit namespace provides functions to register all components and systems
 * with the ECS coordinator at game startup.
 */
#ifndef GAMEINIT_HPP
#define GAMEINIT_HPP

#include <SFML/Graphics.hpp>
#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>

namespace GameInit
{
    /**
     * @brief Registers all component types with the ECS coordinator.
     * @param coordinator The ECS coordinator.
     */
    void RegisterAllComponents(ecs::Coordinator& coordinator);

    /**
     * @brief Creates and registers all game systems with the ECS coordinator.
     * @param window The render window for systems that need it.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for systems that use events.
     */
    void RegisterAllSystems(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus);

} // namespace GameInit

#endif //GAMEINIT_HPP