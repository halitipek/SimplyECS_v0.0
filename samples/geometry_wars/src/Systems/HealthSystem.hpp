/**
* @file HealthSystem.hpp
 * @brief System that manages entity health and damage.
 *
 * The HealthSystem processes health changes, handles entity death
 * when health reaches zero, and updates visual representations of health.
 */
#ifndef HEALTHSYSTEM_HPP
#define HEALTHSYSTEM_HPP

#include <unordered_set>
#include <ecs/System.hpp>
#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>

class HealthSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the health system.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for health-related events.
     */
    HealthSystem(ecs::Coordinator &coordinator, ecs::EventBus &eventBus);

    /**
     * @brief Processes health changes and updates entities.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    ecs::Coordinator&               m_coordinator;      // Reference to the ECS coordinator
    ecs::EventBus&                  m_eventBus;         // Reference to the event bus
    std::unordered_set<ecs::Entity> m_damagedThisFrame;  // Set to track entities damaged this frame
};

#endif //HEALTHSYSTEM_HPP