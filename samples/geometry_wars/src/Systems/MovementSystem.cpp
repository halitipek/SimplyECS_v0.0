/**
* @file MovementSystem.cpp
 * @brief Implementation of the MovementSystem.
 */
#include "MovementSystem.hpp"

#include "Components/TransformComponent.hpp"
#include "Components/VelocityComponent.hpp"

MovementSystem::MovementSystem(ecs::Coordinator& coordinator)
: m_coordinator(coordinator)
{
}

void MovementSystem::Update(float dt)
{
    for (const auto [e, v] : m_entities)
    {
        auto& transform = m_coordinator.GetComponent<TransformComponent>(e);
        auto& vel       = m_coordinator.GetComponent<VelocityComponent>(e).vec;

        transform.position.x += vel.x * dt;
        transform.position.y += vel.y * dt;
        transform.rotation   += transform.angle * dt;
    }
}
