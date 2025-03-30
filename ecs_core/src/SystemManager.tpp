/**
* @file SystemManager.tpp
 * @brief Template implementation of SystemManager methods.
 */
#pragma once

#include <cassert>
#include <memory>
#include <utility>

namespace ecs {

    template<typename T, typename... Args>
    std::shared_ptr<T> SystemManager::RegisterSystem(Args&&... args)
    {
        const char* typeName = typeid(T).name();
        Debug::Assert(!m_systems.contains(typeName),
            "SystemManager::RegisterSystem - Registering system type more than once: %s",
            typeName);

        // Create and store the system
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        m_systems.insert({typeName, system});

        return system;
    }

    template<typename T>
    void SystemManager::SetSystemSignature(const Signature signature)
    {
        const char* typeName = typeid(T).name();
        Debug::Assert(m_systems.contains(typeName),
            "SystemManager::GetSystem - System type not registered: %s",
            typeName);

        // Store what component types the system is interested in
        m_signatures[typeName] = signature;
    }

    template<typename T>
    std::shared_ptr<T> SystemManager::GetSystem()
    {
        const char* typeName = typeid(T).name();
        Debug::Assert(m_systems.contains(typeName),
            "SystemManager::GetSystem - System type not registered: %s",
            typeName);

        return std::static_pointer_cast<T>(m_systems.at(typeName));
    }

} // namespace ecs