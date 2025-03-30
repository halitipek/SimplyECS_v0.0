/**
 * @file EntityFactory.hpp
 * @brief Factory for creating game entities with predefined component sets.
 *
 * The EntityFactory provides methods to create various game entities like players,
 * enemies, projectiles, and visual effects, configuring them with appropriate components.
 */
#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

#include <ecs/Coordinator.hpp>
#include <ecs/Types.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace EntityFactory
{
    /**
     * @brief Creates a player entity at the center of the window.
     * @param window The render window to determine spawn position.
     * @param coordinator The ECS coordinator.
     * @return The created entity ID.
     */
    ecs::Entity SpawnPlayer(sf::RenderWindow& window, ecs::Coordinator& coordinator);

    /**
     * @brief Creates an enemy entity with randomized properties.
     * @param window The render window to determine spawn bounds.
     * @param coordinator The ECS coordinator.
     * @param player The player entity, used to ensure spawn distance.
     * @param isAdvanced Whether to create an advanced enemy with evasive behavior.
     * @return The created entity ID.
     */
    ecs::Entity SpawnEnemy(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::Entity player, bool isAdvanced = false);

    /**
     * @brief Creates a bullet entity fired by a parent entity.
     * @param coordinator The ECS coordinator.
     * @param parent The entity that fired the bullet.
     * @param targetX X-coordinate of the target position.
     * @param targetY Y-coordinate of the target position.
     * @return The created entity ID.
     */
    ecs::Entity SpawnBullet(ecs::Coordinator& coordinator, ecs::Entity parent, float targetX, float targetY);

    /**
     * @brief Creates a sound wave entity emanating from a parent entity.
     * @param coordinator The ECS coordinator.
     * @param parent The entity that created the sound wave.
     * @return The created entity ID.
     */
    ecs::Entity SpawnSoundWave(ecs::Coordinator& coordinator, ecs::Entity parent);

    /**
     * @brief Creates a particle effect at the position of a parent entity.
     * @param coordinator The ECS coordinator.
     * @param parent The entity to spawn particles around.
     * @param angle The angle at which to emit the particle.
     * @param previousHP The previous health value, used for visual styling.
     * @return The created entity ID.
     */
    ecs::Entity SpawnParticle(ecs::Coordinator& coordinator, ecs::Entity parent, float angle, int previousHP);

} // namespace EntityFactory

#endif //ENTITYFACTORY_HPP