/**
* @file CollisionSystem.cpp
 * @brief Implementation of the CollisionSystem.
 */
#include "CollisionSystem.hpp"

#include <Components/EnemyComponent.hpp>

#include "Core/Math//Vec2.hpp"

#include "Components/TransformComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Events/CollisionEvent.hpp"

CollisionSystem::CollisionSystem(ecs::Coordinator& coordinator, ecs::EventBus &eventBus)
: m_coordinator(coordinator)
, m_eventBus(eventBus)
{
}

void CollisionSystem::Update(float dt)
{
    m_collisionBuffer.clear();
    auto& list   = m_entities.GetDataVector();
    size_t count = m_entities.Size();

    for(size_t i = 0; i < count; i++)
    {
        ecs::Entity eX = list[i];
        if(!m_coordinator.IsEntityAlive(eX))
            continue;

        auto& xPos      = m_coordinator.GetComponent<TransformComponent>(eX).position;
        auto& xCol      = m_coordinator.GetComponent<CollisionComponent>(eX);
        bool isExEnemy  = m_coordinator.HasComponent<EnemyComponent>(eX);

        for(size_t j = i+1; j < count; j++)
        {
            ecs::Entity eY = list[j];
            if(!m_coordinator.IsEntityAlive(eY))
                continue;
            if(!isExEnemy && !m_coordinator.HasComponent<EnemyComponent>(eY))
                continue;

            if(CheckCollision(xPos, xCol, eY))
                m_collisionBuffer.emplace_back(eX, eY);
        }
    }

    DispatchCollisions();
}

bool CollisionSystem::CheckCollision(auto& position, auto& collision, const ecs::Entity entity)
{
    auto& yPos = m_coordinator.GetComponent<TransformComponent>(entity).position;
    auto& yCol = m_coordinator.GetComponent<CollisionComponent>(entity);

    float dx    = position.x - yPos.x;
    float dy    = position.y - yPos.y;
    float dist2 = dx*dx + dy*dy;
    float rSum  = collision.radius + yCol.radius;

    return dist2 < rSum*rSum;
}

void CollisionSystem::DispatchCollisions()
{
    for(const auto &ev : m_collisionBuffer)
        m_eventBus.Emit<CollisionEvent>(ev);

    m_collisionBuffer.clear();
}