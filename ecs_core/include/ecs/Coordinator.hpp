/**
 * @file Coordinator.hpp
 * @brief Central coordination class for the ECS framework.
 *
 * The Coordinator serves as the main interface for the ECS system, managing entities,
 * components, and systems, and coordinating their interactions.
 */
#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include <memory>
#include <vector>
#include "Types.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "Debug.hpp"

namespace ecs {

    class Coordinator
    {
    public:
        /**
         * @brief Initializes all managers.
         * Must be called before using any other methods.
         */
        void Init();

        /**
         * @brief Creates a new entity.
         * @return The newly created entity ID.
         */
        Entity CreateEntity();

        /**
         * @brief Marks an entity for destruction.
         * Actual destruction happens on DestroyQueuedEntities call.
         * @param entity The entity to destroy.
         */
        void DestroyEntity(Entity entity);

        /**
         * @brief Gets all currently active entities.
         * @return Vector of all living entity IDs.
         */
        const EntityVec& GetLivingEntities();

        /**
         * @brief Checks if an entity is currently active.
         * @param entity The entity to check.
         * @return True if the entity is alive, false otherwise.
         */
        bool IsEntityAlive(Entity entity) const;

        /**
         * @brief Gets the component signature for an entity.
         * @param entity The entity to query.
         * @return The entity's component signature.
         */
        Signature GetSignature(Entity entity);

        /**
         * @brief Processes all entities queued for destruction.
         */
        void DestroyQueuedEntities();

        /**
         * @brief Destroys all currently active entities.
         */
        void DestroyAllEntities();

        /**
         * @brief Registers a component type with the ECS system.
         * @tparam T The component type to register.
         */
        template<typename T>
        void RegisterComponent();

        /**
         * @brief Adds a component to an entity.
         * @tparam T The component type to add.
         * @param entity The entity to add the component to.
         * @param component The component instance to add.
         */
        template<typename T>
        void AddComponent(Entity entity, const T& component);

        /**
         * @brief Removes a component from an entity.
         * @tparam T The component type to remove.
         * @param entity The entity to remove the component from.
         */
        template<typename T>
        void RemoveComponent(Entity entity);

        /**
         * @brief Gets a component from an entity.
         * @tparam T The component type to get.
         * @param entity The entity to get the component from.
         * @return Reference to the component.
         */
        template<typename T>
        T& GetComponent(Entity entity);

        /**
         * @brief Gets the type ID for a component type.
         * @tparam T The component type.
         * @return The component type ID.
         */
        template<typename T>
        ComponentTypeID GetComponentTypeID();

        /**
         * @brief Checks if an entity has a component.
         * @tparam T The component type to check for.
         * @param entity The entity to check.
         * @return True if the entity has the component, false otherwise.
         */
        template<typename T>
        bool HasComponent(Entity entity);

        /**
         * @brief Registers a system with the ECS framework.
         * @tparam T The system type to register.
         * @tparam Args Constructor argument types for the system.
         * @param args Constructor arguments for the system.
         * @return Shared pointer to the registered system.
         */
        template<typename T, typename ... Args>
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
        std::shared_ptr<T> GetSystem() const;

    private:
        std::unique_ptr<EntityManager>    m_entityManager;     // Manages entity lifecycle
        std::unique_ptr<ComponentManager> m_componentManager;  // Manages component storage
        std::unique_ptr<SystemManager>    m_systemManager;     // Manages systems
        std::vector<Entity>               m_entitiesToDestroy; // Queue of entities to be destroyed
    };

} // namespace ecs
#include "../src/Coordinator.tpp"

#endif //COORDINATOR_HPP