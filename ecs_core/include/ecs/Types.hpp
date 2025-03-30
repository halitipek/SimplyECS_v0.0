/**
* @file Types.hpp
 * @brief Core type definitions for the ECS framework.
 *
 * Defines fundamental types used throughout the ECS system including Entity IDs,
 * Component type IDs, and system signatures.
 */
#ifndef TYPES_HPP
#define TYPES_HPP

#include <bitset>
#include <cstdint>
#include <cstddef>
#include <limits>

namespace ecs
{
    using ComponentTypeID = std::size_t;  // Unique identifier for component types
    using ListenerID = std::size_t;       // Unique identifier for event listeners
    using Entity = std::uint32_t;         // Entity identifier type

    // Special entity value representing an invalid or null entity
    constexpr Entity NullEntity = std::numeric_limits<std::uint32_t>::max();

    // Maximum number of entities that can exist simultaneously
    constexpr std::size_t MaxEntities = 5000;

    // Maximum number of different component types
    constexpr std::size_t MaxComponents = 32;

    // Bitset representing which components an entity has
    using Signature = std::bitset<MaxComponents>;
}

#endif //TYPES_HPP