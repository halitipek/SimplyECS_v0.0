/**
 * @file PlayerSpawnSystem.hpp
 * @brief System responsible for spawning the player entity.
 *
 * The PlayerSpawnSystem listens for spawn player events and creates
 * the player entity with all necessary components when triggered.
 */
#ifndef PLAYERSPAWNSYSTEM_HPP
#define PLAYERSPAWNSYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include <ecs/System.hpp>
#include <SFML/Graphics.hpp>

#include "Events/SpawnPlayerEvent.hpp"

class PlayerSpawnSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the player spawn system.
     * @param window The SFML window for determining spawn position.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for spawn events.
     */
    PlayerSpawnSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus);

    /**
     * @brief Updates the system.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    sf::RenderWindow& m_window;      // Reference to the SFML window
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator
    ecs::EventBus&    m_eventBus;     // Reference to the event bus

    /**
     * @brief Event handler for player spawn events.
     */
    void OnSpawnPlayer(const SpawnPlayerEvent& event);
};

#endif //PLAYERSPAWNSYSTEM_HPP