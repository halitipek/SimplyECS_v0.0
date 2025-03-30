/**
* @file PlayerDeadEvent.hpp
 * @brief Event emitted when the player entity dies.
 *
 * Used to signal game over condition and trigger appropriate responses.
 */
#ifndef PLAYERDEADEVENT_HPP
#define PLAYERDEADEVENT_HPP

#include <ecs/Types.hpp>

struct PlayerDeadEvent
{
    ecs::Entity entity;  // The player entity that died

    PlayerDeadEvent() = default;
    PlayerDeadEvent(const ecs::Entity entity) : entity(entity) {};
};

#endif //PLAYERDEADEVENT_HPP