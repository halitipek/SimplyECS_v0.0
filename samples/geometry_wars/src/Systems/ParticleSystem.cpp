/**
* @file ParticleSystem.cpp
 * @brief Implementation of the ParticleSystem.
 */
#include "ParticleSystem.hpp"
#include "Components/ShapeComponent.hpp"
#include "Events/SpawnEnemyParticlesEvent.hpp"
#include "Factory/EntityFactory.hpp"

ParticleSystem::ParticleSystem(ecs::Coordinator& coordinator, ecs::EventBus& eventBus)
: m_coordinator(coordinator)
, m_eventBus(eventBus)
{
    m_eventBus.AddListener<SpawnEnemyParticlesEvent>(
        [this](const SpawnEnemyParticlesEvent &ev) {
            SpawnEnemyParticle(ev);
        }
    );
}

void ParticleSystem::Update(const float dt)
{
    for (auto [e, _] : m_entities)
    {
        auto& shape = m_coordinator.GetComponent<ShapeComponent>(e);
        shape.radius += dt * 6;
    }
}

void ParticleSystem::SpawnEnemyParticle(const SpawnEnemyParticlesEvent ev)
{
    auto& [enemy, count] = ev;

    if(count <= 0)
        return;

    for(int i = 0.f; i < count; ++i)
    {
        float angle = 360.f / static_cast<float>(count) * (i + 1);
        EntityFactory::SpawnParticle(m_coordinator, enemy, angle, count);
    }
}
