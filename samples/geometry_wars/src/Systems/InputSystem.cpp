/**
* @file InputSystem.cpp
 * @brief Implementation of the InputSystem.
 */
#include "InputSystem.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Core/Math/Vec2.hpp"

#include "Components/VelocityComponent.hpp"
#include "Events/FireBulletEvent.hpp"
#include "Events/SonarAttackEvent.hpp"

InputSystem::InputSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus)
: m_window(window)
, m_coordinator(coordinator)
, m_eventBus(eventBus)
{
}

void InputSystem::Update(float dt)
{
    for (auto [e, _] : m_entities)
    {
        {
            auto& vel = m_coordinator.GetComponent<VelocityComponent>(e);
            Vec2<float> newVel;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { newVel.y += -vel.speed; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { newVel.y +=  vel.speed; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { newVel.x += -vel.speed; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { newVel.x +=  vel.speed; }

            newVel.Normalize();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                newVel *= 2;

            vel.vec.x = newVel.x * vel.speed;
            vel.vec.y = newVel.y * vel.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            m_eventBus.Emit<SonarAttackEvent>(SonarAttackEvent(e));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            auto [mx, my] = sf::Mouse::getPosition(m_window);
            m_eventBus.Emit<FireBulletEvent>(FireBulletEvent(e, static_cast<float>(mx), static_cast<float>(my)));
        }
    }
}
