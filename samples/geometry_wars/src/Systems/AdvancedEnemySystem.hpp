/**
* @file AdvancedEnemySystem.hpp
 * @brief System that handles AI behavior for advanced enemies.
 *
 * The AdvancedEnemySystem implements more sophisticated enemy behavior,
 * including bullet avoidance and player tracking.
 */
#ifndef ADVANCEDENEMYSYSTEM_HPP
#define ADVANCEDENEMYSYSTEM_HPP

#include <Core/Math/Vec2.hpp>
#include <ecs/System.hpp>
#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include <SFML/Graphics.hpp>

class AdvancedEnemySystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the advanced enemy system.
     * @param window The SFML window for screen bounds.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for responding to player events.
     */
    AdvancedEnemySystem(sf::RenderWindow& window, ecs::Coordinator &coordinator, ecs::EventBus &eventBus);

    /**
     * @brief Updates advanced enemy behavior.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    sf::RenderWindow& m_window;       // Reference to the SFML window
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator
    ecs::EventBus&    m_eventBus;     // Reference to the event bus
    ecs::Entity       m_playerEntity;  // Reference to the player entity
    Vec2<float>       m_chaseDir;     // Direction vector towards player
    Vec2<float>       m_avoidDir;     // Direction vector away from bullets
    Vec2<float>       m_finalDir;     // Final direction after combining chase and avoid
    Vec2<float>       m_bulletToEnemy;  // Vector from bullet to enemy
    Vec2<float>       m_bulletPos;    // Position of the nearest threatening bullet
    float             m_chaseWeight;   // Weight for chasing behavior
    float             m_avoidWeight;   // Weight for avoidance behavior
};

#endif //ADVANCEDENEMYSYSTEM_HPP