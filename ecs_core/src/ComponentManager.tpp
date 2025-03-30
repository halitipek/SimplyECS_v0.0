/**
 * @file ComponentManager.tpp
 * @brief Template implementation of ComponentManager methods.
 */
#pragma once

#include <memory>

namespace ecs {

        template<typename T>
        void ComponentArray<T>::InsertData(const Entity entity, const T& component)
        {
            m_components.Insert(entity, component);
        }

        template<typename T>
        void ComponentArray<T>::RemoveData(const Entity entity)
        {
            m_components.Erase(entity);
        }

        template<typename T>
        T& ComponentArray<T>::GetData(const Entity entity)
        {
            return m_components.GetValue(entity);
        }

        template<typename T>
        bool ComponentArray<T>::HasData(const Entity entity)
        {
            return m_components.Contains(entity);
        }

        template<typename T>
        void ComponentArray<T>::EntityDestroyed(const Entity entity)
        {
            m_components.Erase(entity);
        };

        // Component Manager
        template<typename T>
        void ComponentManager::RegisterComponentType()
        {
            Debug::Assert(m_nextComponentTypeID <= MaxComponents,
                "ComponentManager::RegisterComponentType - Exceeded MAX_COMPONENTS limit: %zu",
                MaxComponents);

            const char* typeName = typeid(T).name();
            Debug::Assert(!m_componentTypes.contains(typeName),
                "ComponentManager::RegisterComponentType - Registering component type more than once: %s",
                typeName);

            // Assign a unique ID to this component type and create its storage
            m_componentTypes[typeName] = m_nextComponentTypeID;
            m_componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
            ++m_nextComponentTypeID;
        }

        template<typename T>
        ComponentTypeID ComponentManager::GetComponentTypeID()
        {
            const char* typeName = typeid(T).name();
            Debug::Assert(m_componentTypes.contains(typeName),
                "ComponentManager::GetComponentTypeID - Component type not registered: %s",
                typeName);

            return m_componentTypes[typeName];
        }

        template<typename T>
        void ComponentManager::AddComponent(Entity entity, const T& component)
        {
            auto componentArray = GetComponentArray<T>();
            Debug::Assert(!componentArray->HasData(entity),
                "ComponentManager::AddComponent - Component already exists: Type=%s, Entity=%u",
                typeid(T).name(), entity);

            componentArray->InsertData(entity, component);
        }

        template<typename T>
        void ComponentManager::RemoveComponent(Entity entity)
        {
            auto componentArray = GetComponentArray<T>();
            Debug::Assert(componentArray->HasData(entity),
                "ComponentManager::RemoveComponent - Component does not exist: Type=%s, Entity=%u",
                typeid(T).name(), entity);

            componentArray->RemoveData(entity);
        }

        template<typename T>
        T& ComponentManager::GetComponent(Entity entity)
        {
            auto componentArray = GetComponentArray<T>();
            Debug::Assert(componentArray->HasData(entity),
                "ComponentManager::GetComponent - Component does not exist: Type=%s, Entity=%u",
                typeid(T).name(), entity);

            return componentArray->GetData(entity);
        }

        template<typename T>
        bool ComponentManager::HasComponent(Entity entity)
        {
            auto componentArray = GetComponentArray<T>();

            return componentArray->HasData(entity);
        }

        template<typename T>
        std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
        {
            const char* typeName = typeid(T).name();
            Debug::Assert(m_componentTypes.contains(typeName),
                "ComponentManager::GetComponentArray - Component type not registered: %s",
                typeName);

            return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
        }

} // namespace ecs