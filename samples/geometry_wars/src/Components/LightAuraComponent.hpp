/**
* @file LightAuraComponent.hpp
 * @brief Component for entities with a glowing visual effect.
 *
 * The LightAuraComponent adds a colored aura around entities
 * that can pulse and change color for visual appeal.
 */
#ifndef LIGHTAURACOMPONENT_HPP
#define LIGHTAURACOMPONENT_HPP

#include <SFML/Graphics/Color.hpp>

struct LightAuraComponent
{
    int segments = 60;                          // Number of segments in the aura
    float radius = 56;                          // Radius of the aura
    sf::Color color = sf::Color(255, 255, 255, 45);  // Color with transparency
    float hue = 0.f;                            // Current color hue (0-360)
    float interval = .03f;                      // Time between color changes
    float timer = 0.f;                          // Current timer value
};

#endif //LIGHTAURACOMPONENT_HPP