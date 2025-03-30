/**
* @file GlowComponent.hpp
 * @brief Component for entities with a pulsating glow effect.
 *
 * Extends ShapeComponent with additional properties for
 * rendering a glowing aura that changes color over time.
 */
#ifndef GLOWCOMPONENT_HPP
#define GLOWCOMPONENT_HPP

#include "ShapeComponent.hpp"

struct GlowComponent : ShapeComponent
{
    float hue = 0.f;        // Current color hue (0-360)
    float interval = .03f;  // Time between color changes
    float timer = 0.f;      // Current timer value

    /**
     * @brief Constructs a glow component based on an existing shape component.
     * @param shape The base shape component to inherit properties from.
     */
    GlowComponent(const ShapeComponent& shape)
    {
        shapeType = shape.shapeType;
        radius = shape.radius;
        points = shape.points;
        fillColor = shape.fillColor;
        outlineColor = shape.outlineColor;
        outlineThickness = shape.outlineThickness;
        originX = shape.originX;
        originY = shape.originY;
    }
};

#endif //GLOWCOMPONENT_HPP