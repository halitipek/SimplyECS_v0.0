/**
* @file ScoreComponent.hpp
 * @brief Component that tracks player score.
 *
 * The ScoreComponent stores the current score value,
 * which increases as the player defeats enemies.
 */
#ifndef SCORECOMPONENT_HPP
#define SCORECOMPONENT_HPP

struct ScoreComponent
{
    int value;  // Current score value

    ScoreComponent(int value = 0)
    : value(value)
    {
    }
};

#endif //SCORECOMPONENT_HPP