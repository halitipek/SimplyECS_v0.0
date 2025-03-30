/**
* @file CollisionComponent.hpp
 * @brief Component that enables collision detection for an entity.
 */
#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

struct CollisionComponent
{
    float radius;  // Collision radius for circle-based collision detection

    CollisionComponent(float radius = 0.f)
    : radius(radius)
    {
    }
};

#endif //COLLISIONCOMPONENT_HPP