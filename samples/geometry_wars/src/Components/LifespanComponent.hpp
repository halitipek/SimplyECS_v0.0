/**
* @file LifespanComponent.hpp
 * @brief Component for entities with a limited lifetime.
 *
 * The LifespanComponent tracks how long an entity should exist
 * before being automatically destroyed.
 */
#ifndef LIFESPANCOMPONENT_HPP
#define LIFESPANCOMPONENT_HPP

struct LifespanComponent
{
    float total;      // Total lifetime in seconds
    float remaining;  // Remaining lifetime in seconds

    LifespanComponent(float total = 100.f, float remaining = 100.f)
    : total(total)
    , remaining(remaining)
    {
    }
};

#endif //LIFESPANCOMPONENT_HPP