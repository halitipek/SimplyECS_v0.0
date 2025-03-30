/**
* @file HealthChangeComponent.hpp
 * @brief Component for pending health modifications.
 *
 * The HealthChangeComponent represents a pending change to an entity's
 * health, which will be processed by the HealthSystem.
 */
#ifndef HEALTHCHANGECOMPONENT_HPP
#define HEALTHCHANGECOMPONENT_HPP

struct HealthChangeComponent
{
    int amount = 0;  // Amount to change health by (negative for damage, positive for healing)
};

#endif //HEALTHCHANGECOMPONENT_HPP