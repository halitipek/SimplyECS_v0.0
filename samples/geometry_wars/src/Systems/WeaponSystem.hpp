/**
* @file WeaponSystem.hpp
 * @brief System that manages weapon firing and cooldowns.
 *
 * The WeaponSystem handles weapon activation, such as firing bullets
 * and sonar waves, while enforcing cooldown periods between uses.
 */
#ifndef WEAPONSYSTEM_HPP
#define WEAPONSYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include <ecs/System.hpp>

#include "Events/FireBulletEvent.hpp"
#include "Events/SonarAttackEvent.hpp"

class WeaponSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the weapon system.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for weapon events.
     */
    WeaponSystem(ecs::Coordinator& coordinator, ecs::EventBus& eventBus);

    /**
     * @brief Updates weapon cooldowns and status.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator
    ecs::EventBus&    m_eventBus;     // Reference to the event bus

    /**
     * @brief Event handler for bullet firing events.
     * @param event The fire bullet event.
     */
    void OnFireBullet(const FireBulletEvent& event);

    /**
     * @brief Event handler for sonar attack events.
     * @param event The sonar attack event.
     */
    void OnSonarAttack(const SonarAttackEvent& event);
};

#endif //WEAPONSYSTEM_HPP