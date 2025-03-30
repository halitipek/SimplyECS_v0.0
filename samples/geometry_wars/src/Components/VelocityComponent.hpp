/**
* @file VelocityComponent.hpp
 * @brief Component that defines an entity's movement velocity.
 */
#ifndef VELOCITYCOMPONENT_HPP
#define VELOCITYCOMPONENT_HPP

struct VelocityComponent
{
    Vec2<float> vec;    // Velocity vector
    float speed = 0.f;  // Maximum speed
};

#endif //VELOCITYCOMPONENT_HPP