/**
 * @file ScoreSystem.cpp
 * @brief Implementation of the ScoreSystem.
 */
#include "ScoreSystem.hpp"

#include "Components/PlayerComponent.hpp"
#include "Components/ScoreComponent.hpp"

ScoreSystem::ScoreSystem(ecs::Coordinator& coordinator, ecs::EventBus& eventBus)
: m_coordinator(coordinator)
, m_eventBus(eventBus)
{
    m_eventBus.AddListener<ScoredEvent>(
        [this](const ScoredEvent& event)
        {
            OnScored(event);
        }
    );
}

void ScoreSystem::OnScored(const ScoredEvent& event)
{
    for (auto [e, _] : m_entities)
    {
        if (m_coordinator.HasComponent<PlayerComponent>(e)
            && m_coordinator.HasComponent<ScoreComponent>(e))
        {
            auto& score = m_coordinator.GetComponent<ScoreComponent>(e);
            score.value += 10;
        }
    }
}


void ScoreSystem::Update(float dt)
{
}