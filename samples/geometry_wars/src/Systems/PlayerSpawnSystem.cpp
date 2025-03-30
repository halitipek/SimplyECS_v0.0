/**
* @file PlayerSpawnSystem.cpp
 * @brief Implementation of the PlayerSpawnSystem.
 */
#include "PlayerSpawnSystem.hpp"
#include "Events/PlayerSpawnedEvent.hpp"
#include "Factory/EntityFactory.hpp"

PlayerSpawnSystem::PlayerSpawnSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus)
: m_window(window)
, m_coordinator(coordinator)
, m_eventBus(eventBus)
{
    m_eventBus.AddListener<SpawnPlayerEvent>(
        [this](const SpawnPlayerEvent &event) {
            OnSpawnPlayer(event);
        }
    );
}

void PlayerSpawnSystem::Update(float dt)
{
}

void PlayerSpawnSystem::OnSpawnPlayer(const SpawnPlayerEvent& event)
{
    ecs::Entity player = EntityFactory::SpawnPlayer(m_window, m_coordinator);
    m_eventBus.Emit<PlayerSpawnedEvent>({player});
}
