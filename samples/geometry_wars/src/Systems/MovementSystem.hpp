/**
* @file MovementSystem.hpp
 * @brief System that updates entity positions based on velocities.
 *
 * The MovementSystem applies velocity vectors to entity positions,
 * accounting for delta time to ensure smooth movement.
 */
#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/System.hpp>

class MovementSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the movement system.
     * @param coordinator The ECS coordinator.
     */
    explicit MovementSystem(ecs::Coordinator& coordinator);

    /**
     * @brief Updates entity positions based on velocities.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator
};

#endif //MOVEMENTSYSTEM_HPP