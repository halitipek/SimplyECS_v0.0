/**
* @file SoundWaveComponent.hpp
 * @brief Component for sound wave entities.
 *
 * The SoundWaveComponent defines properties of active sound waves,
 * including their size, power, and the entity that created them.
 */
#ifndef SOUNDWAVECOMPONENT_HPP
#define SOUNDWAVECOMPONENT_HPP

struct SoundWaveComponent
{
    float power;         // Force applied to enemies hit by the wave
    float minRadius;     // Starting radius of the wave
    float maxRadius;     // Maximum radius the wave reaches

    SoundWaveComponent(const float power = 240.f, const float minRadius = 64, const float maxRadius = 256)
    : power(power)
    , minRadius(minRadius)
    , maxRadius(maxRadius)
    {
    };
};
#endif //SOUNDWAVECOMPONENT_HPP