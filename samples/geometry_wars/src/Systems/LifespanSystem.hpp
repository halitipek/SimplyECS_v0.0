/**
 * @file LifespanSystem.hpp
 * @brief System that manages time-limited entities.
 *
 * The LifespanSystem decreases the remaining lifespan of entities
 * and destroys them when their time expires. It also handles visual
 * effects related to entity aging.
 */
#ifndef LIFESPANSYSTEM_HPP
#define LIFESPANSYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/System.hpp>

class LifespanSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the lifespan system.
     * @param coordinator The ECS coordinator.
     */
    explicit LifespanSystem(ecs::Coordinator& coordinator);

    /**
     * @brief Updates entity lifespans and handles expiration.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator
};

#endif //LIFESPANSYSTEM_HPP