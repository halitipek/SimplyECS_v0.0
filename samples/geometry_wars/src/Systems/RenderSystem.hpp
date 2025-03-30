/**
* @file RenderSystem.hpp
 * @brief System that renders all entities with visual components.
 *
 * The RenderSystem iterates through entities with shape components
 * and renders them to the SFML window with appropriate transformations.
 */
#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/System.hpp>
#include <SFML/Graphics.hpp>

class RenderSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the render system.
     * @param window The SFML window to render to.
     * @param coordinator The ECS coordinator.
     */
    explicit RenderSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator);

    /**
     * @brief Renders all visual entities.
     * @param dt Delta time since last render.
     */
    void Update(float dt) override;

private:
    sf::RenderWindow& m_window;     // Reference to the SFML render window
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator

    /**
     * @brief Creates a circular gradient using a vertex array.
     * @param positionX X-coordinate of the center.
     * @param positionY Y-coordinate of the center.
     * @param radius Radius of the circle.
     * @param color Base color of the gradient.
     * @param segments Number of segments to create a smooth circle.
     * @param startAlpha Alpha value at the center.
     * @param endAlpha Alpha value at the edge.
     * @param variance Random variation in radius for visual effect.
     * @return Vertex array representing the gradient circle.
     */
    sf::VertexArray CreateVertexCircleGradient(float positionX, float positionY, float radius, sf::Color color,
                                              int segments, int startAlpha, int endAlpha, float variance = 0.f);
};

#endif //RENDERSYSTEM_HPP