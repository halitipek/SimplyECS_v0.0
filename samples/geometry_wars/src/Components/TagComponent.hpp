/**
* @file TagComponent.hpp
 * @brief Component that categorizes entities by type.
 *
 * Provides a simple type identification system to determine
 * what role an entity plays in the game (player, enemy, etc.).
 */
#ifndef TAGCOMPONENT_HPP
#define TAGCOMPONENT_HPP

/**
 * @brief Types of entities in the game.
 */
enum class EntityType
{
    PLAYER,     // The player character
    ENEMY,      // Enemy entities
    BULLET,     // Projectile fired by the player
    PARTICLE,   // Visual effect particle
    SOUNDWAVE   // Sonar attack wave
};

struct TagComponent
{
    EntityType type;  // The entity's type classification

    TagComponent(EntityType type)
    :type(type)
    {
    }
};

#endif //TAGCOMPONENT_HPP