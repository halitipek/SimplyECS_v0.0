/**
* @file ComponentManager.cpp
 * @brief Implementation of the ComponentManager class.
 */
#include <ecs/ComponentManager.hpp>

namespace ecs {
    ComponentManager::ComponentManager()
    : m_nextComponentTypeID(0) // Initialize the first component ID to 0
    {
    }

    void ComponentManager::EntityDestroyed(const Entity entity)
    {
        for (auto const& [typeName, componentArray] : m_componentArrays)
        {
            if(componentArray->HasData(entity))
            {
                componentArray->EntityDestroyed(entity);
            }
        }
    }

} // namespace ecs