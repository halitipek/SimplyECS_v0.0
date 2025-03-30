/**
* @file TransformComponent.hpp
 * @brief Component that defines an entity's position, rotation, and scale.
 */
#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP
#include <Core/Math/Vec2.hpp>

struct TransformComponent
{
    Vec2<float> position;  // Position in 2D space
    float rotation = 0.f;  // Rotation in degrees
    float scale = 1.f;     // Scale factor
    float angle = 0.f;     // Angular velocity
};

#endif //TRANSFORMCOMPONENT_HPP