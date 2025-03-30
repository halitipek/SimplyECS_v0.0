/**
* @file CollisionSystem.hpp
 * @brief System that detects collisions between entities.
 *
 * The CollisionSystem checks for collisions between entities with
 * collision components and dispatches events when collisions occur.
 */
#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include <ecs/System.hpp>
#include "Events/CollisionEvent.hpp"

class CollisionSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the collision system.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus to dispatch collision events.
     */
    explicit CollisionSystem(ecs::Coordinator &coordinator, ecs::EventBus &eventBus);

    /**
     * @brief Checks for collisions between entities.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    ecs::Coordinator&           m_coordinator;     // Reference to the ECS coordinator
    ecs::EventBus&              m_eventBus;        // Reference to the event bus
    std::vector<CollisionEvent> m_collisionBuffer;  // Buffer to store collision events before dispatching

    /**
     * @brief Checks if an entity collides with another entity.
     * @param position Position component of the first entity.
     * @param collision Collision component of the first entity.
     * @param entity The second entity to check collision with.
     * @return True if collision detected, false otherwise.
     */
    bool CheckCollision(auto& position, auto& collision, ecs::Entity entity);

    /**
     * @brief Dispatches all buffered collision events.
     */
    void DispatchCollisions();
};

#endif //COLLISIONSYSTEM_HPP