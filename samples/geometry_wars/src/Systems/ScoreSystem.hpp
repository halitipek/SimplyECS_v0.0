/**
 * @file ScoreSystem.hpp
 * @brief System that tracks and updates the player's score.
 *
 * The ScoreSystem listens for score events and updates the player's
 * score component accordingly.
 */
#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include <ecs/System.hpp>

#include "Events/ScoredEvent.hpp"

class ScoreSystem final : public ecs::System
{
public:
    /**
     * @brief Constructs the score system.
     * @param coordinator The ECS coordinator.
     * @param eventBus The event bus for score events.
     */
    ScoreSystem(ecs::Coordinator& coordinator, ecs::EventBus& eventBus);

    /**
     * @brief Updates the system.
     * @param dt Delta time since last update.
     */
    void Update(float dt) override;

private:
    ecs::Coordinator& m_coordinator;  // Reference to the ECS coordinator
    ecs::EventBus&    m_eventBus;     // Reference to the event bus

    /**
     * @brief Event handler for score events.
     */
    void OnScored(const ScoredEvent& event);
};

#endif //SCORESYSTEM_HPP