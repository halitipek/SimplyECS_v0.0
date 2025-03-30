/**
 * @file CollisionResponseSystem.hpp
 * @brief System that determines what happens when entities collide.
 * 
 * This system listens for collision events and implements appropriate
 * responses based on the types of entities involved in the collision.
 */
#ifndef COLLISIONRESPONSESYSTEM_HPP
#define COLLISIONRESPONSESYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include <ecs/System.hpp>
#include <SFML/Graphics.hpp>
#include "Events/CollisionEvent.hpp"

class CollisionResponseSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the collision response system.
     * @param window The SFML window reference.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for collision events.
     */
    CollisionResponseSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus);
    
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
     * @brief Event handler for collision events.
     * @param event The collision event.
     */
    void OnCollision(CollisionEvent event);
    
    /**
     * @brief Handles collision between player and enemy entities.
     * @param event The collision event.
     */
    void HandlePlayerEnemyCollision(const CollisionEvent& event);
    
    /**
     * @brief Handles collision between bullet and enemy entities.
     * @param event The collision event.
     */
    void HandleBulletEnemyCollision(const CollisionEvent &event);
    
    /**
     * @brief Handles collision between sound wave and enemy entities.
     * @param event The collision event.
     */
    void HandleSoundWaveEnemyCollision(const CollisionEvent &event);
    
    /**
     * @brief Handles collision between two enemy entities.
     * @param event The collision event.
     */
    void HandleEnemyEnemyCollision(const CollisionEvent &event);
};

#endif //COLLISIONRESPONSESYSTEM_HPP