/**
 * @file AdvancedEnemySystem.cpp
 * @brief Implementation of the AdvancedEnemySystem.
 */
#include "AdvancedEnemySystem.hpp"

#include <Components/CollisionComponent.hpp>

#include "Core/Math/Vec2.hpp"

#include "Components/AdvancedEnemyComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/VelocityComponent.hpp"
#include "Components/BulletComponent.hpp"

#include <Events/PlayerDeadEvent.hpp>
#include <Events/PlayerSpawnedEvent.hpp>

AdvancedEnemySystem::AdvancedEnemySystem(sf::RenderWindow& window, ecs::Coordinator &coordinator, ecs::EventBus &eventBus)
: m_window(window)
, m_coordinator(coordinator)
, m_eventBus(eventBus)
, m_playerEntity(ecs::NullEntity)
, m_chaseWeight(.2f)
, m_avoidWeight(.8f)
{
    // Listen for player spawn events to track the player entity
    m_eventBus.AddListener<PlayerSpawnedEvent>(
        [this](const PlayerSpawnedEvent& ev) {
            m_playerEntity = ev.entity;
        }
    );

    // Listen for player death events to stop tracking the player
    m_eventBus.AddListener<PlayerDeadEvent>(
        [this](const PlayerDeadEvent& ev) {
            m_playerEntity = ecs::NullEntity;
        }
    );
}

void AdvancedEnemySystem::Update(float dt)
{
    // Don't process if there's no player
    if (m_playerEntity == ecs::NullEntity)
        return;

    const auto& playerPos = m_coordinator.GetComponent<TransformComponent>(m_playerEntity).position;

    for (auto [e, _] : m_entities)
    {
        auto& eAdv = m_coordinator.GetComponent<AdvancedEnemyComponent>(e);
        auto& ePos = m_coordinator.GetComponent<TransformComponent>(e).position;
        auto& eVel = m_coordinator.GetComponent<VelocityComponent>(e).vec;
        auto& eCol = m_coordinator.GetComponent<CollisionComponent>(e);

        // Default behavior: chase the player
        m_chaseDir = (playerPos - ePos).Normalized();

        bool shouldEvade = false;
        float finalSpeed = eAdv.chaseSpeed;

        // Scan for bullets that might hit this enemy
        for (auto bulletEntity : m_coordinator.GetLivingEntities())
        {
            if (!m_coordinator.HasComponent<BulletComponent>(bulletEntity))
                continue;

            auto& bPos = m_coordinator.GetComponent<TransformComponent>(bulletEntity).position;
            auto& bVel = m_coordinator.GetComponent<VelocityComponent>(bulletEntity).vec;
            auto& bCol = m_coordinator.GetComponent<CollisionComponent>(bulletEntity);

            m_bulletToEnemy = bPos - ePos;

            // Skip bullets that are too far away
            if (m_bulletToEnemy.LengthSquared() > eAdv.evadeThreshold * eAdv.evadeThreshold)
                continue;

            // Bullet trajectory analysis
            // Calculate if the bullet is moving toward the enemy
            float bVelDotVel = bVel.x * bVel.x + bVel.y * bVel.y;
            float bulletToEnemyDotVel = m_bulletToEnemy.x * bVel.x + m_bulletToEnemy.y * bVel.y;

            // Skip if bullet is stationary or moving away from enemy
            if (bVelDotVel <= 0.0001f || bulletToEnemyDotVel > 0.f)
                continue;

            // Calculate time of closest approach
            // tStar is the time when the bullet will be closest to the enemy
            float tStar = -(bulletToEnemyDotVel / bVelDotVel);
            if (tStar < 0.f)
                continue;  // Closest approach already happened

            // Calculate position of closest approach
            auto closestPoint = m_bulletToEnemy + (bVel * tStar);

            // Check if this closest approach would result in a collision
            float collisionDist = eCol.radius + bCol.radius;
            if (closestPoint.LengthSquared() < collisionDist * collisionDist)
            {
                // Bullet will hit enemy, trigger evasion
                shouldEvade = true;
                m_bulletPos = bPos;
                break;
            }
        }

        if (shouldEvade)
        {
            // Calculate evasion direction - perpendicular to bullet path
            Vec2<float> toBullet = m_bulletPos - ePos;
            float cross = m_chaseDir.x * toBullet.y - m_chaseDir.y * toBullet.x;
            m_avoidDir = toBullet.Normalized();

            // Choose direction based on cross product to ensure enemy doesn't move into bullet
            m_avoidDir.RotateDegrees((cross > 0.f) ? -90.f : 90.f);
            finalSpeed = eAdv.evadeSpeed;  // Move faster when evading
        }
        else
        {
            m_avoidDir = {0.f, 0.f};  // No evasion needed
        }

        // Combine chase and avoid vectors with their weights
        m_finalDir = (m_chaseDir * m_chaseWeight) + (m_avoidDir * m_avoidWeight);
        m_finalDir.Normalize();
        m_finalDir *= finalSpeed;

        // Update enemy velocity
        eVel = m_finalDir;
    }
}