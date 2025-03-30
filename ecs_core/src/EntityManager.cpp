/**
* @file EntityManager.cpp
 * @brief Implementation of the EntityManager class.
 */
#include <ecs/EntityManager.hpp>
#include <ecs/Types.hpp>
#include "ecs/Debug.hpp"

namespace ecs {
    EntityManager::EntityManager()
    {
        // Initialize entity IDs pool (0 to MAX_ENTITIES-1)
        for (Entity e = 0; e < MaxEntities; ++e)
        {
            m_availableEntities.push(e);
        }
    }

    Entity EntityManager::CreateEntity()
    {
        Debug::Assert(!m_availableEntities.empty(),
            "EntityManager::CreateEntity - Maximum number of entities exceeded: %zu",
            MaxEntities);

        const Entity id = m_availableEntities.front();
        m_availableEntities.pop();
        m_livingEntities.Insert(id);

        return id;
    }

    void EntityManager::DestroyEntity(const Entity entity)
    {
        Debug::Assert(m_livingEntities.Contains(entity),
            "EntityManager::DestroyEntity - Entity is not alive: %u",
            entity);

        // Remove from living entities, reset signature, and recycle ID
        m_livingEntities.Erase(entity);
        m_signatures[entity].reset();
        m_availableEntities.push(entity);
    }

    const EntityVec& EntityManager::GetLivingEntities() const
    {
        return m_livingEntities.GetDataVector();
    }

    bool EntityManager::IsAlive(const Entity entity) const
    {
        Debug::Assert(entity < MaxEntities,
            "EntityManager::IsAlive - Entity is not valid: %u",
            entity);

        return m_livingEntities.Contains(entity);
    }

    void EntityManager::SetSignature(const Entity entity, const Signature signature)
    {
        Debug::Assert(entity < MaxEntities,
            "EntityManager::SetSignature - Entity is not valid: %u",
            entity);

        m_signatures[entity] = signature;
    }

    Signature EntityManager::GetSignature(const Entity entity) const
    {
        Debug::Assert(entity < MaxEntities,
            "EntityManager::SetSignature - Entity is not valid: %u",
            entity);

        return m_signatures[entity];
    }

} // namespace ecs