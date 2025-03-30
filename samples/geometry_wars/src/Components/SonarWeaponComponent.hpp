/**
 * @file SonarWeaponComponent.hpp
 * @brief Component for entities with sonar wave capability.
 *
 * The SonarWeaponComponent defines properties for entities that can
 * emit sound waves, including wave size, power, and cooldown.
 */
#ifndef SONARWEAPONCOMPONENT_HPP
#define SONARWEAPONCOMPONENT_HPP

struct SonarWeaponComponent
{
    float interval;   // Time between sonar activations
    float timer;      // Current cooldown timer
    float power;      // Force applied to enemies hit by the wave
    float minRadius;  // Starting radius of the wave
    float maxRadius;  // Maximum radius the wave reaches
    float lifeSpan;   // How long the wave exists

    SonarWeaponComponent(const float interval = 10.f, const float timer = 10.f, const float power = 600.f,
        const float minRadius = 48.f, const float maxRadius = 240.f, const float lifeSpan = 100.f)
    : interval(interval)
    , timer(timer)
    , power(power)
    , minRadius(minRadius)
    , maxRadius(maxRadius)
    , lifeSpan(lifeSpan)
    {
    };
};

#endif //SONARWEAPONCOMPONENT_HPP