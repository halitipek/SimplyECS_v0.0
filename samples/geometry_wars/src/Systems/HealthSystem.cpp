/**
* @file HealthSystem.cpp
 * @brief Implementation of the HealthSystem.
 */
#include "HealthSystem.hpp"

#include <Components/PlayerComponent.hpp>
#include <Events/PlayerDeadEvent.hpp>

#include "Components/HealthComponent.hpp"
#include "Components/EnemyComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/AdvancedEnemyComponent.hpp"
#include "Components/HealthChangeComponent.hpp"
#include "Events/SpawnEnemyParticlesEvent.hpp"
#include "Managers/ConfigManager.hpp"

HealthSystem::HealthSystem(ecs::Coordinator &coordinator, ecs::EventBus &eventBus)
: m_coordinator(coordinator)
, m_eventBus(eventBus)
{
};

void HealthSystem::Update(float dt)
{
    m_damagedThisFrame.clear();

    const auto& eConfig = gConfig.GetGameConfig().enemy;
    auto m_entitiesCopy = m_entities;

    for (auto const& [entity, _] : m_entitiesCopy)
    {
        if(m_damagedThisFrame.contains(entity))
        {
            m_coordinator.RemoveComponent<HealthChangeComponent>(entity);
            continue;
        }

        m_damagedThisFrame.insert(entity);

        bool isEnemy = m_coordinator.HasComponent<EnemyComponent>(entity);
        auto& health = m_coordinator.GetComponent<HealthComponent>(entity);
        auto amount = m_coordinator.GetComponent<HealthChangeComponent>(entity).amount;
        m_coordinator.RemoveComponent<HealthChangeComponent>(entity);

        if(isEnemy)
            m_eventBus.Emit<SpawnEnemyParticlesEvent>({ entity, health.remaining });

        health.remaining = std::min(health.remaining + amount, health.max);

        if (health.remaining >= 3)
        {
            auto& shape = m_coordinator.GetComponent<ShapeComponent>(entity);
            shape.points = health.remaining;

            if (isEnemy)
            {
                if(!m_coordinator.HasComponent<AdvancedEnemyComponent>(entity))
                    shape.outlineColor = eConfig.outlineColor[health.remaining - eConfig.pointCountMin];
            }

            continue;
        }

        if(m_coordinator.HasComponent<PlayerComponent>(entity))
            m_eventBus.Emit<PlayerDeadEvent>({entity});

        m_coordinator.DestroyEntity(entity);
    }
}
