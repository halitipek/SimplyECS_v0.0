/**
 * @file EntityManager.hpp
 * @brief Manages entity creation, destruction and tracking.
 *
 * The EntityManager is responsible for creating and recycling entity IDs,
 * tracking which entities are currently active, and storing entity signatures
 * which define what components each entity has.
 */
#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <queue>
#include <array>
#include <vector>
#include "DenseMap.hpp"
#include "Types.hpp"

namespace ecs {
    using EntityVec = std::vector<Entity>;

    class EntityManager
    {
    public:
        EntityManager();

        /**
         * @brief Creates a new entity.
         * @return The created entity ID.
         */
        Entity CreateEntity();

        /**
         * @brief Destroys an entity, recycling its ID.
         * @param entity The entity to destroy.
         */
        void DestroyEntity(Entity entity);

        /**
         * @brief Get all currently active entities.
         * @return Vector containing all living entity IDs.
         */
        const EntityVec& GetLivingEntities() const;

        /**
         * @brief Checks if an entity is currently active.
         * @param entity The entity to check.
         * @return True if the entity is alive, false otherwise.
         */
        bool IsAlive(Entity entity) const;

        /**
         * @brief Sets the component signature for an entity.
         * @param entity The entity to modify.
         * @param signature The new signature.
         */
        void SetSignature(Entity entity, Signature signature);

        /**
         * @brief Gets the component signature for an entity.
         * @param entity The entity to query.
         * @return The entity's component signature.
         */
        Signature GetSignature(Entity entity) const;

    private:
        std::queue<Entity>                  m_availableEntities;  // Recycled entity IDs ready for reuse
        DenseMap<Entity>                    m_livingEntities;     // Currently active entities
        std::array<Signature, MaxEntities>  m_signatures;         // Component signatures for each entity
    };

} // namespace ecs

#endif //ENTITYMANAGER_HPP