/**
 * @file AdvancedEnemyComponent.hpp
 * @brief Component for enemies with advanced AI behavior.
 *
 * Provides configuration for enemies that can evade bullets and
 * exhibit more sophisticated chase behavior.
 */
#ifndef ADVANCEDENEMYCOMPONENT_HPP
#define ADVANCEDENEMYCOMPONENT_HPP

struct AdvancedEnemyComponent
{
    float evadeThreshold;  // Distance at which enemy considers bullet evasion
    float evadeSpeed;      // Movement speed when evading
    float chaseSpeed;      // Movement speed when chasing the player

    AdvancedEnemyComponent(float evadeThreshold = 0.f, float evadeSpeed = 0.f, float chaseSpeed = 0.f)
    : evadeThreshold(evadeThreshold)
    , evadeSpeed(evadeSpeed)
    , chaseSpeed(chaseSpeed)
    {
    };
};

#endif //ADVANCEDENEMYCOMPONENT_HPP