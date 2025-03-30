/**
* @file Coordinator.cpp
 * @brief Implementation of the Coordinator class.
 */
#include <ecs/Coordinator.hpp>
#include <memory>

namespace ecs {
    void Coordinator::Init()
    {
        m_entityManager    = std::make_unique<EntityManager>();
        m_componentManager = std::make_unique<ComponentManager>();
        m_systemManager    = std::make_unique<SystemManager>();
    }

    Entity Coordinator::CreateEntity()
    {
        Debug::Assert(!!m_entityManager,
            "Coordinator::CreateEntity - EntityManager not initialized. Call Init() first");

        return m_entityManager->CreateEntity();
    }

    void Coordinator::DestroyEntity(const Entity entity)
    {
        Debug::Assert(!!m_entityManager,
            "Coordinator::DestroyEntity - EntityManager not initialized. Call Init() first");

        m_entitiesToDestroy.push_back(entity);
    }

    const EntityVec& Coordinator::GetLivingEntities()
    {
        Debug::Assert(!!m_entityManager,
            "Coordinator::GetLivingEntities - EntityManager not initialized");

        return m_entityManager->GetLivingEntities();
    }

    bool Coordinator::IsEntityAlive(const Entity entity) const
    {
        Debug::Assert(!!m_entityManager,
            "Coordinator::IsEntityAlive - EntityManager not initialized.");

        return m_entityManager->IsAlive(entity);
    }

    Signature Coordinator::GetSignature(const Entity entity)
    {
        Debug::Assert(!!m_entityManager,
            "Coordinator::GetSignature - EntityManager not initialized.");

        return m_entityManager->GetSignature(entity);
    }

    void Coordinator::DestroyQueuedEntities()
    {
        Debug::Assert(m_entityManager && m_componentManager && m_systemManager,
            "Coordinator::DestroyQueuedEntities - Managers not initialized.");

        if(m_entitiesToDestroy.empty())
        {
            return;
        }

        for (const auto e : m_entitiesToDestroy)
        {
            if (!m_entityManager->IsAlive(e))
            {
                continue;
            }

            m_entityManager->DestroyEntity(e);
            m_componentManager->EntityDestroyed(e);
            m_systemManager->EntitySignatureChanged(e, Signature());
        }

        m_entitiesToDestroy.clear();
    }

    void Coordinator::DestroyAllEntities()
    {
        Debug::Assert(m_entityManager && m_componentManager && m_systemManager,
            "Coordinator::DestroyQueuedEntities - Managers not initialized.");

        m_entitiesToDestroy.clear();

        auto livingEntitiesCopy = m_entityManager->GetLivingEntities();

        for (auto const e : livingEntitiesCopy)
        {
            m_entityManager->DestroyEntity(e);
            m_componentManager->EntityDestroyed(e);
            m_systemManager->EntitySignatureChanged(e, Signature());
        }
    }

} // namespace ecs