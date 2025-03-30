/**
* @file CollisionEvent.hpp
 * @brief Event emitted when two entities collide.
 *
 * Used by the collision system to notify other systems about
 * collisions between entities.
 */
#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include <ecs/Types.hpp>

struct CollisionEvent
{
    ecs::Entity entity1, entity2;  // The two entities involved in the collision

    CollisionEvent() = default;
    CollisionEvent(const ecs::Entity entity1, const ecs::Entity entity2)
    : entity1(entity1)
    , entity2(entity2)
    {
    };
};

#endif //COLLISIONEVENT_HPP