/**
* @file GunComponent.hpp
 * @brief Component that provides bullet-firing capability.
 *
 * The GunComponent defines properties for entities that can
 * fire projectiles, including firing rate, bullet size, and speed.
 */
#ifndef GUNCOMPONENT_HPP
#define GUNCOMPONENT_HPP

struct GunComponent
{
    float interval;   // Time between shots
    float timer;      // Current cooldown timer
    float radius;     // Radius of bullets fired
    float speed;      // Speed of bullets fired
    float lifeSpan;   // How long bullets exist before disappearing

    GunComponent(const float interval = 1.f, const float timer = 1.f, const float radius = 10.f
        , const float speed = 800.f, const float lifeSpan = 1.6f)
    : interval(interval)
    , timer(timer)
    , radius(radius)
    , speed(speed)
    , lifeSpan(lifeSpan)
    {
    };
};
#endif //GUNCOMPONENT_HPP