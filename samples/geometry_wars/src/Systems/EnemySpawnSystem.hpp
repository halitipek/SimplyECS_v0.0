/**
* @file EnemySpawnSystem.hpp
 * @brief System that manages enemy spawning.
 *
 * The EnemySpawnSystem periodically spawns new enemies based on
 * configured intervals and ensures enemies spawn at appropriate positions.
 */
#ifndef ENEMYSPAWNSYSTEM_HPP
#define ENEMYSPAWNSYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include <ecs/System.hpp>
#include <SFML/Graphics.hpp>

#include "Events/SpawnEnemyEvent.hpp"

class EnemySpawnSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the enemy spawn system.
     * @param window The SFML window for screen bounds.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for spawn events.
     */
    EnemySpawnSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus);

    /**
     * @brief Updates spawn timers and creates new enemies.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    sf::RenderWindow& m_window;        // Reference to the SFML window
    ecs::Coordinator& m_coordinator;   // Reference to the ECS coordinator
    ecs::EventBus&    m_eventBus;      // Reference to the event bus
    ecs::Entity       m_playerEntity;  // Reference to the player entity

    int   m_maxEnemyCount;            // Maximum number of enemies allowed
    float m_spawnInterval;            // Time between regular enemy spawns
    float m_timer;                    // Current spawn timer
    float m_advancedEnemyInterval;    // Time between advanced enemy spawns
    float m_advancedEnemyTimer;       // Current advanced enemy spawn timer

    /**
     * @brief Event handler for enemy spawn events.
     */
 void OnSpawnEnemy(const SpawnEnemyEvent& event);
};

#endif //ENEMYSPAWNSYSTEM_HPP