/**
* @file EnemySpawnSystem.cpp
 * @brief Implementation of the EnemySpawnSystem.
 */
#include "EnemySpawnSystem.hpp"
#include "Managers/ConfigManager.hpp"

#include "Events/PlayerSpawnedEvent.hpp"
#include "Events/PlayerDeadEvent.hpp"
#include "Events/SpawnEnemyEvent.hpp"
#include "Factory/EntityFactory.hpp"

EnemySpawnSystem::EnemySpawnSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus)
: m_window(window)
, m_coordinator(coordinator)
, m_eventBus(eventBus)
, m_maxEnemyCount(gConfig.GetGameConfig().enemy.maxEnemyCount)
, m_spawnInterval(gConfig.GetGameConfig().enemy.spawnInterval)
, m_timer(0.f)
, m_advancedEnemyInterval(gConfig.GetGameConfig().enemy.advancedEnemy.at("interval"))
, m_advancedEnemyTimer(0.f)
{
    m_eventBus.AddListener<SpawnEnemyEvent>(
        [this](const SpawnEnemyEvent &event) {
            OnSpawnEnemy(event);
        }
    );

    m_eventBus.AddListener<PlayerSpawnedEvent>(
        [this](const PlayerSpawnedEvent& event) {
            m_playerEntity = event.entity;
        }
    );

    m_eventBus.AddListener<PlayerDeadEvent>(
        [this](const PlayerDeadEvent& event) {
            m_playerEntity = ecs::NullEntity;
        }
    );
}

void EnemySpawnSystem::Update(const float dt)
{
    if (m_timer <= 0.f)
        m_timer = m_spawnInterval;
    m_timer -= dt;

    m_advancedEnemyTimer -= dt;

    if (m_timer <= 0.f && m_maxEnemyCount > m_entities.Size() && m_playerEntity != ecs::NullEntity)
    {
        EntityFactory::SpawnEnemy(m_window, m_coordinator, m_playerEntity, (m_advancedEnemyTimer <= 0.f));

        if (m_advancedEnemyTimer <= 0.f)
            m_advancedEnemyTimer = m_advancedEnemyInterval;
    }
}

void EnemySpawnSystem::OnSpawnEnemy(const SpawnEnemyEvent& event)
{
    EntityFactory::SpawnEnemy(m_window, m_coordinator, m_playerEntity);
}


