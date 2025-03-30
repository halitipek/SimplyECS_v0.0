/**
 * @file Coordinator.tpp
 * @brief Template implementation of Coordinator methods.
 */
#pragma once

#include <memory>
#include <utility>

namespace ecs
{
    template<typename T>
    void Coordinator::RegisterComponent()
    {
        m_componentManager->RegisterComponentType<T>();
    }

    template<typename T>
    void Coordinator::AddComponent(const Entity entity, const T& component)
    {
        Debug::Assert(m_entityManager->IsAlive(entity),
            "Coordinator::AddComponent - Entity does not alive: Type = %s, Entity = %u",
            typeid(T).name(), entity);

        // Add the component to the entity
        m_componentManager->AddComponent<T>(entity, component);

        // Update the entity's signature
        auto signature = m_entityManager->GetSignature(entity);
        signature.set(m_componentManager->GetComponentTypeID<T>(), true);
        m_entityManager->SetSignature(entity, signature);

        // Notify systems about the signature change
        m_systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void Coordinator::RemoveComponent(const Entity entity)
    {
        Debug::Assert(m_entityManager->IsAlive(entity),
            "Coordinator::RemoveComponent - Entity does not alive: Type = %s, Entity = %u",
            typeid(T).name(), entity);

        // Remove the component from the entity
        m_componentManager->RemoveComponent<T>(entity);

        // Update the entity's signature
        auto signature = m_entityManager->GetSignature(entity);
        signature.set(m_componentManager->GetComponentTypeID<T>(), false);
        m_entityManager->SetSignature(entity, signature);

        // Notify systems about the signature change
        m_systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& Coordinator::GetComponent(const Entity entity)
    {
        Debug::Assert(m_entityManager->IsAlive(entity),
            "Coordinator::GetComponent - Entity does not alive: Type = %s, Entity = %u",
            typeid(T).name(), entity);

        return m_componentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentTypeID Coordinator::GetComponentTypeID()
    {
        return m_componentManager->GetComponentTypeID<T>();
    }

    template<typename T>
    bool Coordinator::HasComponent(const Entity entity)
    {
        Debug::Assert(m_entityManager->IsAlive(entity),
            "Coordinator::HasComponent - Entity does not alive: Type = %s, Entity = %u",
            typeid(T).name(), entity);

        return m_componentManager->HasComponent<T>(entity);
    }

    template<typename T, typename ... Args>
    std::shared_ptr<T> Coordinator::RegisterSystem(Args&&... args)
    {
        return m_systemManager->RegisterSystem<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    void Coordinator::SetSystemSignature(const Signature signature)
    {
        m_systemManager->SetSystemSignature<T>(signature);
    }

    template<typename T>
    std::shared_ptr<T> Coordinator::GetSystem() const
    {
        return m_systemManager->GetSystem<T>();
    }

} // namespace ecs