/**
 * @file Helpers.cpp
 * @brief Implementation of the Helpers.
 */
#include "Helpers.hpp"
#include <cmath>
#include <algorithm>

namespace Helpers
{
    sf::Color HSVtoRGB(float H, float S, float V, sf::Uint8 alpha)
    {
        H = std::fmod(H, 360.0f);
        if (H < 0) H += 360.0f;
        S = std::clamp(S, 0.0f, 1.0f);
        V = std::clamp(V, 0.0f, 1.0f);

        float C = V * S; // Chroma
        float X = C * (1.0f - std::fabs(std::fmod(H / 60.0f, 2.0f) - 1.0f));
        float m = V - C; // Amount to add to each component to match Value

        float r_prime, g_prime, b_prime; // RGB components in [0, C] range
        if(H >= 0 && H < 60)      { r_prime = C; g_prime = X; b_prime = 0; }
        else if(H >= 60 && H < 120){ r_prime = X; g_prime = C; b_prime = 0; }
        else if(H >= 120 && H < 180){ r_prime = 0; g_prime = C; b_prime = X; }
        else if(H >= 180 && H < 240){ r_prime = 0; g_prime = X; b_prime = C; }
        else if(H >= 240 && H < 300){ r_prime = X; g_prime = 0; b_prime = C; }
        else { r_prime = C; g_prime = 0; b_prime = X; } // H >= 300 && H < 360
        return {
            static_cast<sf::Uint8>((r_prime + m) * 255.0f),
            static_cast<sf::Uint8>((g_prime + m) * 255.0f),
            static_cast<sf::Uint8>((b_prime + m) * 255.0f),
            alpha
        };
    }

} // namespace Helpers