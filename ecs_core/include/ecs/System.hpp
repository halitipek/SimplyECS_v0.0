/**
* @file System.hpp
 * @brief Base class for all ECS systems.
 *
 * Systems in ECS process entities that have specific component combinations.
 * This base class provides common functionality for all systems.
 */
#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Types.hpp"
#include "DenseMap.hpp"

namespace ecs {

    /**
     * @brief Base class for all ECS systems.
     *
     * Systems contain the logic to process entities with specific component combinations.
     * This base class manages the set of entities that match a system's requirements.
     */
    class System
    {
    protected:
        DenseMap<Entity> m_entities;  // Set of entities this system operates on

    public:
        virtual ~System() = default;

        /**
         * @brief Update method called each frame to process entities.
         * @param dt Delta time since the last frame.
         */
        virtual void Update(float dt) {} // Default empty implementation

        /**
         * @brief Checks if this system contains a specific entity.
         * @param entity The entity to check for.
         * @return True if the system contains the entity, false otherwise.
         */
        bool HasEntity(Entity entity);

        /**
         * @brief Adds an entity to this system.
         * @param entity The entity to add.
         */
        void AddEntity(Entity entity);

        /**
         * @brief Removes an entity from this system.
         * @param entity The entity to remove.
         */
        void RemoveEntity(Entity entity);
    };

} // namespace ecs

#endif //SYSTEM_HPP