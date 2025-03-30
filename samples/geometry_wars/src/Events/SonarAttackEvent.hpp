/**
* @file SonarAttackEvent.hpp
 * @brief Event emitted when a sonar weapon is activated.
 *
 * Used to request creation of a sound wave emanating from an entity.
 */
#ifndef SONARATTACKEVENT_HPP
#define SONARATTACKEVENT_HPP

struct SonarAttackEvent
{
    ecs::Entity entity;  // Entity that activated the sonar

    SonarAttackEvent() = default;
    SonarAttackEvent(const ecs::Entity entity)
    : entity(entity)
    {
    }
};

#endif //SONARATTACKEVENT_HPP