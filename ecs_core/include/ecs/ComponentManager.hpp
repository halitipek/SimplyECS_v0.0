/**
 * @file ComponentManager.hpp
 * @brief Manages component storage and entity-component relationships.
 *
 * The ComponentManager provides a type-safe interface for adding, removing, and
 * accessing components attached to entities. It maintains a separate array for
 * each component type.
 */
#ifndef COMPONENTMANAGER_HPP
#define COMPONENTMANAGER_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include "Types.hpp"
#include "DenseMap.hpp"
#include "Debug.hpp"

namespace ecs
{
    /**
     * @brief Base interface for component storage.
     *
     * Provides a common interface for different component type arrays
     * to handle entity destruction.
     */
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;

        /**
         * @brief Checks if an entity has this component.
         * @param entity The entity to check.
         * @return True if the entity has the component, false otherwise.
         */
        virtual bool HasData(Entity entity) = 0;

        /**
         * @brief Handles entity destruction by removing components.
         * @param entity The entity being destroyed.
         */
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    /**
     * @brief Type-specific storage for components.
     * @tparam T The component type this array stores.
     */
    template<typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        /**
         * @brief Adds or updates a component for an entity.
         * @param entity The entity to associate the component with.
         * @param component The component instance to store.
         */
        void InsertData(Entity entity, const T &component);

        /**
         * @brief Removes a component from an entity.
         * @param entity The entity to remove the component from.
         */
        void RemoveData(Entity entity);

        /**
         * @brief Gets a component for an entity.
         * @param entity The entity to get the component for.
         * @return Reference to the component.
         */
        T &GetData(Entity entity);

        /**
         * @brief Checks if an entity has this component.
         * @param entity The entity to check.
         * @return True if the entity has the component, false otherwise.
         */
        bool HasData(Entity entity) override;

        /**
         * @brief Handles entity destruction.
         * @param entity The entity being destroyed.
         */
        void EntityDestroyed(Entity entity) override;

    private:
        DenseMap<Entity, T> m_components; // Stores entity-component mappings
    };

    /**
     * @brief Manages all component arrays and component type registration.
     */
    class ComponentManager
    {
    public:
        ComponentManager();

        ~ComponentManager() = default;

        /**
         * @brief Handles entity destruction across all component arrays.
         * @param entity The entity being destroyed.
         */
        void EntityDestroyed(Entity entity);

        /**
         * @brief Registers a new component type.
         * @tparam T The component type to register.
         */
        template<typename T>
        void RegisterComponentType();

        /**
         * @brief Gets the type ID for a registered component type.
         * @tparam T The component type.
         * @return The component type ID.
         */
        template<typename T>
        ComponentTypeID GetComponentTypeID();

        /**
         * @brief Adds a component to an entity.
         * @tparam T The component type to add.
         * @param entity The entity to add the component to.
         * @param component The component instance to add.
         */
        template<typename T>
        void AddComponent(Entity entity, const T &component);

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
        T &GetComponent(Entity entity);

        /**
         * @brief Checks if an entity has a component.
         * @tparam T The component type to check for.
         * @param entity The entity to check.
         * @return True if the entity has the component, false otherwise.
         */
        template<typename T>
        bool HasComponent(Entity entity);

    private:
        /**
         * @brief Gets a component array for a specific component type.
         * @tparam T The component type.
         * @return Shared pointer to the component array.
         */
        template<typename T>
        std::shared_ptr<ComponentArray<T> > GetComponentArray();

        std::unordered_map<std::string, ComponentTypeID> m_componentTypes; // Maps from type name to type ID
        std::unordered_map<std::string, std::shared_ptr<IComponentArray> > m_componentArrays;
        // Maps from type name to component array
        ComponentTypeID m_nextComponentTypeID; // Next available component type ID
    };
} // namespace ecs
#include "../src/ComponentManager.tpp"

#endif //COMPONENTMANAGER_HPP
