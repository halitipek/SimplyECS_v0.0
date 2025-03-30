/**
* @file ShapeComponent.hpp
 * @brief Component that defines an entity's visual appearance.
 */
#ifndef SHAPECOMPONENT_HPP
#define SHAPECOMPONENT_HPP

#include <cstddef>
#include <SFML/Graphics/Color.hpp>

/**
 * @brief Types of shapes that can be rendered.
 */
enum class ShapeType
{
    Circle,  // Circle shape using SFML's CircleShape
    Vertex   // Custom shape using SFML's VertexArray
};

/**
 * @brief Additional data for vertex-based shapes.
 */
struct VertexShapeData {
    int segments = 32;             // Number of segments/vertices
    sf::Color color = sf::Color::White;  // Color of the vertex shape
    float radius = 0.f;            // Radius for circular arrangement
};

/**
 * @brief Component for rendering entities with various shapes.
 */
struct ShapeComponent
{
    ShapeType shapeType = ShapeType::Circle;  // Type of shape to render
    float radius = 10.f;                      // Radius of the shape
    std::size_t points = 32;                  // Number of points/vertices
    sf::Color fillColor = sf::Color::White;   // Fill color
    sf::Color outlineColor = sf::Color::Black;  // Outline color
    float outlineThickness = 1.f;             // Outline thickness
    float originX = 0.f;                      // X-coordinate of origin/center
    float originY = 0.f;                      // Y-coordinate of origin/center
    VertexShapeData vertexShapeData;          // Data for vertex-based shapes
};

#endif //SHAPECOMPONENT_HPP