/**
* @file BoundarySystem.hpp
 * @brief System that keeps entities within screen boundaries.
 *
 * The BoundarySystem prevents entities from moving outside the screen bounds
 * and handles special cases like bullets being destroyed at the edge.
 */
#ifndef BOUNDARYSYSTEM_HPP
#define BOUNDARYSYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/System.hpp>
#include <SFML/Graphics.hpp>

class BoundarySystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the boundary system.
     * @param window The SFML window for screen bounds.
     * @param coordinator The ECS coordinator.
     */
    explicit BoundarySystem(sf::RenderWindow &window, ecs::Coordinator &coordinator);

    /**
     * @brief Checks and corrects entity positions against screen boundaries.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    sf::RenderWindow& m_window;      // Reference to the SFML window
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator

    /**
     * @brief Handles boundary interactions for a specific entity.
     * @param entity The entity to check.
     */
    void BounceIfOutside(ecs::Entity entity) const;
};

#endif //BOUNDARYSYSTEM_HPP