/**
* @file HealthComponent.hpp
 * @brief Component for entities with health/hit points.
 *
 * Tracks an entity's maximum and current health, which can be
 * decreased by damage and potentially increased by healing.
 */
#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

struct HealthComponent
{
    int max;        // Maximum health value
    int remaining;  // Current health value

    HealthComponent(int max = 0, int remaining = 0)
    : max(max)
    , remaining(remaining)
    {
    }
};

#endif //HEALTHCOMPONENT_HPP