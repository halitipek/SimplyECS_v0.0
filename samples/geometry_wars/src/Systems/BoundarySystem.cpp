/**
* @file BoundarySystem.cpp
 * @brief Implementation of the BoundarySystem.
 */
#include "BoundarySystem.hpp"

#include "Components/BulletComponent.hpp"
#include "Components/EnemyComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/VelocityComponent.hpp"

BoundarySystem::BoundarySystem(sf::RenderWindow &window, ecs::Coordinator &coordinator)
: m_window(window)
, m_coordinator(coordinator)
{
}

void BoundarySystem::Update(float dt)
{
    for (auto [e, _] : m_entities)
        BounceIfOutside(e);
}

void BoundarySystem::BounceIfOutside(const ecs::Entity e) const
{
    auto& pos   = m_coordinator.GetComponent<TransformComponent>(e).position;
    auto& shape = m_coordinator.GetComponent<ShapeComponent>(e);
    auto& vel   = m_coordinator.GetComponent<VelocityComponent>(e).vec;

    const float radius = shape.radius;
    const sf::Vector2u windowSize = m_window.getSize();

    bool hasBullet = m_coordinator.HasComponent<BulletComponent>(e);
    bool hasEnemy = m_coordinator.HasComponent<EnemyComponent>(e);

    float maxWidth  = static_cast<float>(windowSize.x) - radius;
    float maxHeight = static_cast<float>(windowSize.y) - radius;

    if (pos.x < radius || pos.x > maxWidth)
    {
        if(hasBullet)
        {
            m_coordinator.DestroyEntity(e);
            return;
        }

        pos.x = std::clamp(pos.x, radius, maxWidth);

        if(hasEnemy)
            vel.x *= -1.f;
    }

    if (pos.y < radius || pos.y > maxHeight)
    {
        if(hasBullet)
        {
            m_coordinator.DestroyEntity(e);
            return;
        }

        pos.y = std::clamp(pos.y, radius, maxHeight);

        if(hasEnemy)
            vel.y *= -1.f;
    }
}
