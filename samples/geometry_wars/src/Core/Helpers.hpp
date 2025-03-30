/**
* @file Helpers.hpp
 * @brief Utility functions for common tasks.
 *
 * The Helpers namespace provides utility functions used across
 * the game, such as color conversion and manipulation.
 */
#ifndef HELPERS_HPP
#define HELPERS_HPP
#include <SFML/Graphics/Color.hpp>

namespace Helpers
{
    /**
     * @brief Converts a color from HSV to RGB color space.
     * @param H Hue value (0-360).
     * @param S Saturation value (0.0-1.0).
     * @param V Value/brightness (0.0-1.0).
     * @param alpha Alpha/transparency value (0-255).
     * @return The converted RGB color.
     */
    sf::Color HSVtoRGB(float H, float S, float V, sf::Uint8 alpha = 255);

} // namespace Helpers

#endif //HELPERS_HPP