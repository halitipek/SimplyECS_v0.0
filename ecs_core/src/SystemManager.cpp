/**
* @file SystemManager.cpp
 * @brief Implementation of the SystemManager class.
 */
#include <ecs/SystemManager.hpp>

namespace ecs {
    void SystemManager::EntitySignatureChanged(const Entity entity, const Signature entitySig)
    {
        for (auto const& [typeName, system] : m_systems)
        {
            auto const& systemSig = m_signatures.at(typeName); // Assumes typeName exists in m_signatures (should be guaranteed by registration)
            if ((entitySig & systemSig) == systemSig)
            {
                system->AddEntity(entity);
            }
            else
            {
                system->RemoveEntity(entity);
            }
        }
    }

} // namespace ecs