/**
* @file CollisionResponseSystem.cpp
 * @brief Implementation of the CollisionResponseSystem.
 */
#include "CollisionResponseSystem.hpp"

#include "Core/Math/Vec2.hpp"

#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>

#include "Events/CollisionEvent.hpp"
#include "Events/ScoredEvent.hpp"

#include "Components/TagComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/VelocityComponent.hpp"
#include "Components/SoundWaveComponent.hpp"
#include "Components/AdvancedEnemyComponent.hpp"
#include "Components/HealthChangeComponent.hpp"

CollisionResponseSystem::CollisionResponseSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus)
: m_window(window)
, m_coordinator(coordinator)
, m_eventBus(eventBus)
{
    m_eventBus.AddListener<CollisionEvent>(
        [this](const CollisionEvent &ev) {
            OnCollision(ev);
        }
    );
}

void CollisionResponseSystem::Update(const float dt)
{
}

void CollisionResponseSystem::OnCollision(CollisionEvent event)
{
    auto type1 = m_coordinator.GetComponent<TagComponent>(event.entity1).type;
    auto type2 = m_coordinator.GetComponent<TagComponent>(event.entity2).type;

    if ((type1 == EntityType::PLAYER && type2 == EntityType::ENEMY) ||
        (type1 == EntityType::ENEMY && type2 == EntityType::PLAYER))
    {
        if (type1 != EntityType::PLAYER) std::swap(event.entity1, event.entity2);
        HandlePlayerEnemyCollision(event);
    }
    else if ((type1 == EntityType::BULLET && type2 == EntityType::ENEMY) ||
             (type1 == EntityType::ENEMY && type2 == EntityType::BULLET))
    {
        if (type1 != EntityType::BULLET) std::swap(event.entity1, event.entity2);
        HandleBulletEnemyCollision(event);
    }
    else if ((type1 == EntityType::SOUNDWAVE && type2 == EntityType::ENEMY) ||
             (type1 == EntityType::ENEMY && type2 == EntityType::SOUNDWAVE))
    {
        if (type1 != EntityType::SOUNDWAVE) std::swap(event.entity1, event.entity2);
        HandleSoundWaveEnemyCollision(event);
    }
    else if (type1 == EntityType::ENEMY && type2 == EntityType::ENEMY &&
             (m_coordinator.HasComponent<AdvancedEnemyComponent>(event.entity1) || m_coordinator.HasComponent<AdvancedEnemyComponent>(event.entity2)))
    {
        HandleEnemyEnemyCollision(event);
    }
}

void CollisionResponseSystem::HandlePlayerEnemyCollision(const CollisionEvent &event)
{
    ecs::Entity player = event.entity1;
    ecs::Entity enemy = event.entity2;

    int playerHealtChangeAmount = -1;
    int enemyHealtChangeAmount  = -1;
    if (m_coordinator.IsEntityAlive(player) && !m_coordinator.HasComponent<HealthChangeComponent>(player)) {
        m_coordinator.AddComponent<HealthChangeComponent>(player, {playerHealtChangeAmount});
    }
    if (m_coordinator.IsEntityAlive(enemy) && !m_coordinator.HasComponent<HealthChangeComponent>(enemy)) {
        m_coordinator.AddComponent<HealthChangeComponent>(enemy, {enemyHealtChangeAmount});
    }
    if (m_coordinator.IsEntityAlive(player) && m_coordinator.IsEntityAlive(enemy)) {
        auto& pPos = m_coordinator.GetComponent<TransformComponent>(player).position;
        auto& ePos = m_coordinator.GetComponent<TransformComponent>(enemy).position;
        auto& eVel = m_coordinator.GetComponent<VelocityComponent>(enemy);
        auto& eCol = m_coordinator.GetComponent<CollisionComponent>(enemy);

        Vec2<float> dir = (ePos - pPos).Normalized();
        eVel.vec = dir * eVel.speed;
        ePos    += dir * (eCol.radius * 0.5f);
    }
}

void CollisionResponseSystem::HandleBulletEnemyCollision(const CollisionEvent &event)
{
    ecs::Entity bullet = event.entity1;
    ecs::Entity enemy  = event.entity2;
    if (!m_coordinator.IsEntityAlive(bullet) || !m_coordinator.IsEntityAlive(enemy)) {
        return;
    }

    int enemyHeathChangeAmount = -1;
    if (!m_coordinator.HasComponent<HealthChangeComponent>(enemy))
        m_coordinator.AddComponent<HealthChangeComponent>(enemy, {enemyHeathChangeAmount});
    m_coordinator.DestroyEntity(bullet);

    m_eventBus.Emit<ScoredEvent>({});
}

void CollisionResponseSystem::HandleSoundWaveEnemyCollision(const CollisionEvent &event)
{
    if (!m_coordinator.IsEntityAlive(event.entity1) || !m_coordinator.IsEntityAlive(event.entity2)) return;
    auto& sPos = m_coordinator.GetComponent<TransformComponent>(event.entity1).position;
    auto& sWave = m_coordinator.GetComponent<SoundWaveComponent>(event.entity1);
    auto& ePos = m_coordinator.GetComponent<TransformComponent>(event.entity2).position;
    auto& eVel = m_coordinator.GetComponent<VelocityComponent>(event.entity2);

    Vec2<float> dirVel = (ePos - sPos).Normalized();
    eVel.vec = dirVel * eVel.speed;
    ePos    += dirVel * sWave.power;
}

void CollisionResponseSystem::HandleEnemyEnemyCollision(const CollisionEvent &event)
{
     if (!m_coordinator.IsEntityAlive(event.entity1) || !m_coordinator.IsEntityAlive(event.entity2)) return;
    auto& e1Pos = m_coordinator.GetComponent<TransformComponent>(event.entity1).position;
    auto& e1Vel = m_coordinator.GetComponent<VelocityComponent>(event.entity1);
    auto e1CR = m_coordinator.GetComponent<CollisionComponent>(event.entity1).radius;
    auto& e2Pos = m_coordinator.GetComponent<TransformComponent>(event.entity2).position;
    auto& e2Vel = m_coordinator.GetComponent<VelocityComponent>(event.entity2);
    auto e2CR = m_coordinator.GetComponent<CollisionComponent>(event.entity2).radius;

    Vec2<float> dir = (e1Pos - e2Pos).Normalized();
    e1Vel.vec = dir * e1Vel.speed;
    e1Pos    += dir * (e1CR * 0.1f);
    e2Vel.vec = dir * (-e2Vel.speed);
    e2Pos    -= dir * (e2CR * 0.1f);
}