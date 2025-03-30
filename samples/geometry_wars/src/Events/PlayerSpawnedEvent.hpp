/**
 * @file PlayerSpawnedEvent.hpp
 * @brief Event emitted when the player entity spawned.
 */
#ifndef PLAYERSPAWNEDEVENT_HPP
#define PLAYERSPAWNEDEVENT_HPP

#include <ecs/Types.hpp>

struct PlayerSpawnedEvent
{
    ecs::Entity entity;   // The player entity that cretated

    PlayerSpawnedEvent() = default;
    PlayerSpawnedEvent(const ecs::Entity entity) : entity(entity) {};
};

#endif //PLAYERSPAWNEDEVENT_HPP
