/**
* @file FireBulletEvent.hpp
 * @brief Event emitted when a weapon fires a bullet.
 *
 * Used to request bullet creation at a specified target position.
 */
#ifndef FIREBULLETEVENT_HPP
#define FIREBULLETEVENT_HPP

struct FireBulletEvent
{
    ecs::Entity entity;      // Entity that fired the bullet
    float targetX, targetY;  // Target position to aim at

    FireBulletEvent() = default;
    FireBulletEvent(const ecs::Entity entity, const float targetX, const float targetY)
    : entity(entity)
    , targetX(targetX)
    , targetY(targetY)
    {
    };
};

#endif //FIREBULLETEVENT_HPP