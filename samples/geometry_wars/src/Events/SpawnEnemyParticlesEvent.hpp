/**
 * @file SpawnEnemyParticlesEvent.hpp
 * @brief Event emitted for spawn enemy particles request.
 */
#ifndef SPAWNENEMYPARTICLESEVENT_HPP
#define SPAWNENEMYPARTICLESEVENT_HPP
#include <ecs/Types.hpp>

struct SpawnEnemyParticlesEvent
{
    ecs::Entity entity;
    int count;

    SpawnEnemyParticlesEvent() = default;
    SpawnEnemyParticlesEvent(const ecs::Entity entity, const int count)
    : entity(entity)
    , count(count)
    {
    };
};

#endif //SPAWNENEMYPARTICLESEVENT_HPP
