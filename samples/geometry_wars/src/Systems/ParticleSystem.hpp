/**
 * @file ParticleSystem.hpp
 * @brief System that manages particle effects.
 *
 * The ParticleSystem creates and updates visual particle effects
 * used for explosions, impacts, and other visual feedback.
 */
#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include <ecs/System.hpp>

#include "Events/SpawnEnemyParticlesEvent.hpp"

class ParticleSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the particle system.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for particle events.
     */
    explicit ParticleSystem(ecs::Coordinator& coordinator, ecs::EventBus& eventBus);

    /**
     * @brief Updates particle effects.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator
    ecs::EventBus&    m_eventBus;     // Reference to the event bus

    /**
     * @brief Spawns particles for enemy destruction or damage.
     * @param event The spawn enemy particles event.
     */
    void SpawnEnemyParticle(SpawnEnemyParticlesEvent event);
};

#endif //PARTICLESYSTEM_HPP