/**
 * @file SystemManager.hpp
 * @brief Manages all ECS systems and their entity signatures.
 *
 * The SystemManager is responsible for registering systems, tracking which
 * components each system is interested in, and updating systems when entity
 * signatures change.
 */
#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include "Types.hpp"
#include "DenseMap.hpp"
#include "System.hpp"
#include "Debug.hpp"

namespace ecs {

    class SystemManager
    {
    public:
        SystemManager() = default;
        ~SystemManager() = default;

        /**
         * @brief Registers a new system.
         * @tparam T The system type to register.
         * @tparam Args Constructor argument types for the system.
         * @param args Constructor arguments for the system.
         * @return Shared pointer to the registered system.
         */
        template<typename T, typename... Args>
        std::shared_ptr<T> RegisterSystem(Args&&... args);

        /**
         * @brief Sets which components a system is interested in.
         * @tparam T The system type.
         * @param signature The component signature for the system.
         */
        template<typename T>
        void SetSystemSignature(Signature signature);

        /**
         * @brief Gets a reference to a system.
         * @tparam T The system type to get.
         * @return Shared pointer to the system.
         */
        template<typename T>
        std::shared_ptr<T> GetSystem();

        /**
         * @brief Updates systems when an entity's signature changes.
         *
         * This method is called when components are added to or removed from an entity.
         * It updates which systems should process the entity based on its new signature.
         *
         * @param entity The entity whose signature changed.
         * @param entitySignature The entity's new signature.
         */
        void EntitySignatureChanged(Entity entity, Signature entitySignature);

    private:
        std::unordered_map<const char*, std::shared_ptr<System>> m_systems;    // Maps from type name to system
        std::unordered_map<const char*, Signature>     m_signatures;  // Maps from type name to signature
    };

} // namespace ecs
#include "../src/SystemManager.tpp"

#endif //SYSTEMMANAGER_HPP