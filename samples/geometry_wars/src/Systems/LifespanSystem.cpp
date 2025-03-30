/**
* @file LifespanSystem.cpp
 * @brief Implementation of the LifespanSystem.
 */
#include "LifespanSystem.hpp"

#include <Components/BulletComponent.hpp>
#include <Components/CollisionComponent.hpp>
#include <Components/ParticleComponent.hpp>
#include <Managers/ConfigManager.hpp>
#include <SFML/Config.hpp>

#include "Components/LifespanComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/SoundWaveComponent.hpp"

LifespanSystem::LifespanSystem(ecs::Coordinator& coordinator)
: m_coordinator(coordinator)
{
}

void LifespanSystem::Update(float dt)
{
    auto m_entitiesCopy = m_entities;
    for (auto [e, v] : m_entitiesCopy)
    {
        auto&[total, remaining] = m_coordinator.GetComponent<LifespanComponent>(e);
        auto& shape = m_coordinator.GetComponent<ShapeComponent>(e);
        remaining -= dt;

        if(remaining <= 0.f)
        {
            m_coordinator.DestroyEntity(e);
            continue;
        }

        float lifeProgress = (total - remaining) / total;

        if(m_coordinator.HasComponent<BulletComponent>(e) || m_coordinator.HasComponent<ParticleComponent>(e))
        {
            auto alpha = static_cast<sf::Uint8>((remaining / total) * 255);
            shape.fillColor.a    = alpha;
            shape.outlineColor.a = alpha;
        }

        if (m_coordinator.HasComponent<SoundWaveComponent>(e))
        {
            auto& wave = m_coordinator.GetComponent<SoundWaveComponent>(e);
            auto& collision = m_coordinator.GetComponent<CollisionComponent>(e);

            float currentRadius = wave.minRadius + (wave.maxRadius - wave.minRadius) * lifeProgress;
            auto alpha = static_cast<sf::Uint8>((1.f - lifeProgress) * gConfig.GetGameConfig().sonar.color.a);
            shape.vertexShapeData.radius = currentRadius;
            collision.radius = currentRadius;
            shape.vertexShapeData.color.a = alpha;
        }
    }
}