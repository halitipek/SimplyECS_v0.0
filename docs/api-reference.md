# SimplyECS API Reference

This document provides a detailed reference for all the public classes and methods in the SimplyECS framework.

## Table of Contents

- [Core Types](#core-types)
- [Coordinator](#coordinator)
- [EntityManager](#entitymanager)
- [ComponentManager](#componentmanager)
- [SystemManager](#systemmanager)
- [System](#system)
- [EventBus](#eventbus)
- [DenseMap](#densemap)
- [Debug Utilities](#debug-utilities)

## Core Types

### Entity

```cpp
namespace ecs {
    using Entity = std::uint32_t;
    
    constexpr Entity NullEntity = std::numeric_limits<std::uint32_t>::max();
    
    constexpr std::size_t MaxEntities = 5000;
}
```

An entity is represented as a 32-bit unsigned integer, providing a simple and efficient identifier.

Special values:
- `NullEntity`: Represents an invalid or non-existent entity
- `MaxEntities`: The maximum number of entities that can exist simultaneously (default: 5000)

### ComponentTypeID

```cpp
namespace ecs {
    using ComponentTypeID = std::size_t;
    
    constexpr std::size_t MaxComponents = 32;
}
```

A component type ID is a unique identifier for each component type, used for signatures.

Special values:
- `MaxComponents`: The maximum number of different component types allowed (default: 32)

### Signature

```cpp
namespace ecs {
    using Signature = std::bitset<MaxComponents>;
}
```

A signature is a bitset that represents which components an entity has or which components a system operates on.

## Coordinator

The main interface for the ECS framework, managing entities, components, and systems.

### `void Init()`

Initializes all managers. Must be called before using any other methods.

### `Entity CreateEntity()`

Creates a new entity.

**Returns**: The newly created entity ID.

### `void DestroyEntity(Entity entity)`

Marks an entity for destruction. Actual destruction happens on `DestroyQueuedEntities()` call.

**Parameters**:
- `entity`: The entity to destroy.

### `const EntityVec& GetLivingEntities()`

Gets all currently active entities.

**Returns**: Vector of all living entity IDs.

### `bool IsEntityAlive(Entity entity) const`

Checks if an entity is currently active.

**Parameters**:
- `entity`: The entity to check.

**Returns**: True if the entity is alive, false otherwise.

### `Signature GetSignature(Entity entity)`

Gets the component signature for an entity.

**Parameters**:
- `entity`: The entity to query.

**Returns**: The entity's component signature.

### `void DestroyQueuedEntities()`

Processes all entities queued for destruction.

### `void DestroyAllEntities()`

Destroys all currently active entities.

### `template<typename T> void RegisterComponent()`

Registers a component type with the ECS system.

**Template Parameters**:
- `T`: The component type to register.

### `template<typename T> void AddComponent(Entity entity, const T& component)`

Adds a component to an entity.

**Template Parameters**:
- `T`: The component type to add.

**Parameters**:
- `entity`: The entity to add the component to.
- `component`: The component instance to add.

### `template<typename T> void RemoveComponent(Entity entity)`

Removes a component from an entity.

**Template Parameters**:
- `T`: The component type to remove.

**Parameters**:
- `entity`: The entity to remove the component from.

### `template<typename T> T& GetComponent(Entity entity)`

Gets a component from an entity.

**Template Parameters**:
- `T`: The component type to get.

**Parameters**:
- `entity`: The entity to get the component from.

**Returns**: Reference to the component.

### `template<typename T> ComponentTypeID GetComponentTypeID()`

Gets the type ID for a component type.

**Template Parameters**:
- `T`: The component type.

**Returns**: The component type ID.

### `template<typename T> bool HasComponent(Entity entity)`

Checks if an entity has a component.

**Template Parameters**:
- `T`: The component type to check for.

**Parameters**:
- `entity`: The entity to check.

**Returns**: True if the entity has the component, false otherwise.

### `template<typename T, typename ... Args> std::shared_ptr<T> RegisterSystem(Args&&... args)`

Registers a system with the ECS framework.

**Template Parameters**:
- `T`: The system type to register.
- `Args`: Constructor argument types for the system.

**Parameters**:
- `args`: Constructor arguments for the system.

**Returns**: Shared pointer to the registered system.

### `template<typename T> void SetSystemSignature(Signature signature)`

Sets which components a system is interested in.

**Template Parameters**:
- `T`: The system type.

**Parameters**:
- `signature`: The component signature for the system.

### `template<typename T> std::shared_ptr<T> GetSystem() const`

Gets a reference to a system.

**Template Parameters**:
- `T`: The system type to get.

**Returns**: Shared pointer to the system.

## EntityManager

Responsible for creating, destroying, and tracking entities.

### `Entity CreateEntity()`

Creates a new entity.

**Returns**: The created entity ID.

### `void DestroyEntity(Entity entity)`

Destroys an entity, recycling its ID.

**Parameters**:
- `entity`: The entity to destroy.

### `const EntityVec& GetLivingEntities() const`

Get all currently active entities.

**Returns**: Vector containing all living entity IDs.

### `bool IsAlive(Entity entity) const`

Checks if an entity is currently active.

**Parameters**:
- `entity`: The entity to check.

**Returns**: True if the entity is alive, false otherwise.

### `void SetSignature(Entity entity, Signature signature)`

Sets the component signature for an entity.

**Parameters**:
- `entity`: The entity to modify.
- `signature`: The new signature.

### `Signature GetSignature(Entity entity) const`

Gets the component signature for an entity.

**Parameters**:
- `entity`: The entity to query.

**Returns**: The entity's component signature.

## ComponentManager

Manages component storage and entity-component relationships.

### `template<typename T> void RegisterComponentType()`

Registers a new component type.

**Template Parameters**:
- `T`: The component type to register.

### `template<typename T> ComponentTypeID GetComponentTypeID()`

Gets the type ID for a registered component type.

**Template Parameters**:
- `T`: The component type.

**Returns**: The component type ID.

### `template<typename T> void AddComponent(Entity entity, const T &component)`

Adds a component to an entity.

**Template Parameters**:
- `T`: The component type to add.

**Parameters**:
- `entity`: The entity to add the component to.
- `component`: The component instance to add.

### `template<typename T> void RemoveComponent(Entity entity)`

Removes a component from an entity.

**Template Parameters**:
- `T`: The component type to remove.

**Parameters**:
- `entity`: The entity to remove the component from.

### `template<typename T> T &GetComponent(Entity entity)`

Gets a component from an entity.

**Template Parameters**:
- `T`: The component type to get.

**Parameters**:
- `entity`: The entity to get the component from.

**Returns**: Reference to the component.

### `template<typename T> bool HasComponent(Entity entity)`

Checks if an entity has a component.

**Template Parameters**:
- `T`: The component type to check for.

**Parameters**:
- `entity`: The entity to check.

**Returns**: True if the entity has the component, false otherwise.

### `void EntityDestroyed(Entity entity)`

Handles entity destruction across all component arrays.

**Parameters**:
- `entity`: The entity being destroyed.

## SystemManager

Manages all ECS systems and their entity signatures.

### `template<typename T, typename... Args> std::shared_ptr<T> RegisterSystem(Args&&... args)`

Registers a new system.

**Template Parameters**:
- `T`: The system type to register.
- `Args`: Constructor argument types for the system.

**Parameters**:
- `args`: Constructor arguments for the system.

**Returns**: Shared pointer to the registered system.

### `template<typename T> void SetSystemSignature(Signature signature)`

Sets which components a system is interested in.

**Template Parameters**:
- `T`: The system type.

**Parameters**:
- `signature`: The component signature for the system.

### `template<typename T> std::shared_ptr<T> GetSystem()`

Gets a reference to a system.

**Template Parameters**:
- `T`: The system type to get.

**Returns**: Shared pointer to the system.

### `void EntitySignatureChanged(Entity entity, Signature entitySignature)`

Updates systems when an entity's signature changes.

**Parameters**:
- `entity`: The entity whose signature changed.
- `entitySignature`: The entity's new signature.

## System

// The System base class provides common functionality for all systems.

### Methods

```cpp
virtual void Update(float dt) {}
```
Update method called each frame to process entities.
- **Parameters**:
    - `dt`: Delta time since the last frame.

```cpp
bool HasEntity(Entity entity);
```
Checks if this system contains a specific entity.
- **Parameters**:
    - `entity`: The entity to check for.
- **Returns**: True if the system contains the entity, false otherwise.

```cpp
void AddEntity(Entity entity);
```
Adds an entity to this system.
- **Parameters**:
    - `entity`: The entity to add.

```cpp
void RemoveEntity(Entity entity);
```
Removes an entity from this system.
- **Parameters**:
    - `entity`: The entity to remove.

### Protected Members

```cpp
DenseMap<Entity> m_entities;
```
Set of entities this system operates on.

## EventBus

Allows systems to communicate without direct dependencies through a publish-subscribe pattern.

### `template<typename EventType> ListenerID AddListener(std::function<void(const EventType&)> listener)`

Adds a listener for a specific event type.

**Template Parameters**:
- `EventType`: The event type to listen for.

**Parameters**:
- `listener`: The callback function to invoke when event occurs.

**Returns**: Unique ID for the listener (used for removal).

### `template<typename EventType> void RemoveListener(ListenerID listenerID)`

Removes a listener for a specific event type.

**Template Parameters**:
- `EventType`: The event type the listener was registered for.

**Parameters**:
- `listenerID`: The ID of the listener to remove.

### `template<typename EventType> void Emit(const EventType &event, bool fast = false)`

Emits an event to all registered listeners.

**Template Parameters**:
- `EventType`: The type of event to emit.

**Parameters**:
- `event`: The event data to send.
- `fast`: If true, processes the event immediately; otherwise queues it.

### `void ProcessEvents()`

Processes all queued events.

### `void UnsubscribeAll()`

Removes all event listeners.

## DenseMap

A cache-friendly associative container optimized for fast iteration.

### `void Insert(const Key& key)`

Inserts a key using the key as its value.

**Parameters**:
- `key`: The key to insert.

### `void Insert(const Key& key, const Value& value)`

Inserts a key-value pair or updates if the key already exists.

**Parameters**:
- `key`: The key to insert or update.
- `value`: The value to associate with the key.

### `void Update(const Key& key, const Value& value)`

Updates the value for an existing key.

**Parameters**:
- `key`: The key to update.
- `value`: The new value.

### `void Erase(const Key& key)`

Removes a key-value pair.

**Parameters**:
- `key`: The key to remove.

### `bool Contains(const Key& key) const`

Checks if a key exists in the map.

**Parameters**:
- `key`: The key to check.

**Returns**: True if the key exists, false otherwise.

### `const Value& GetValue(const Key& key) const`

Gets the value associated with a key (const version).

**Parameters**:
- `key`: The key to look up.

**Returns**: Const reference to the value.

### `Value& GetValue(const Key& key)`

Gets the value associated with a key.

**Parameters**:
- `key`: The key to look up.

**Returns**: Reference to the value.

### `const std::vector<Value>& GetDataVector() const`

Gets the underlying data vector (const version).

**Returns**: Const reference to the data vector.

### `std::vector<Value>& GetDataVector()`

Gets the underlying data vector.

**Returns**: Reference to the data vector.

### `bool IsEmpty() const`

Checks if the map is empty.

**Returns**: True if empty, false otherwise.

### `std::size_t Size() const`

Gets the number of elements in the map.

**Returns**: Size of the map.

### `void Clear()`

Clears all elements from the map.

### `Iterator begin()`

Returns an iterator to the beginning of the map.

### `Iterator end()`

Returns an iterator to the end of the map.

## Debug Utilities

The Debug namespace provides utilities for error detection and reporting.

### `template<typename... Args> inline void Assert(bool condition, const char* format, Args... args)`

Checks a condition and displays detailed error message if it fails.

**Template Parameters**:
- `Args`: Parameter types for the format string.

**Parameters**:
- `condition`: The condition to verify (true means success).
- `format`: Printf-style format string.
- `args`: Parameters to be passed to the format string.

## Usage Example

Here's a complete example that demonstrates how to use the SimplyECS API:

```cpp
#include <ecs/Coordinator.hpp>
#include <iostream>

// Define components
struct Position {
    float x, y;
};

struct Velocity {
    float x, y;
};

// Define a system
class MovementSystem : public ecs::System {
public:
    MovementSystem(ecs::Coordinator& coordinator) : m_coordinator(coordinator) {}

    void Update(float dt) override {
        for (auto entity : m_entities.GetDataVector()) {
            auto& position = m_coordinator.GetComponent<Position>(entity);
            const auto& velocity = m_coordinator.GetComponent<Velocity>(entity);

            position.x += velocity.x * dt;
            position.y += velocity.y * dt;

            std::cout << "Entity " << entity << " position: (" 
                      << position.x << ", " << position.y << ")\n";
        }
    }

private:
    ecs::Coordinator& m_coordinator;
};

int main() {
    // Initialize the coordinator
    ecs::Coordinator coordinator;
    coordinator.Init();

    // Register components
    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();

    // Register system
    auto movementSystem = coordinator.RegisterSystem<MovementSystem>(coordinator);

    // Set system signature
    ecs::Signature signature;
    signature.set(coordinator.GetComponentTypeID<Position>());
    signature.set(coordinator.GetComponentTypeID<Velocity>());
    coordinator.SetSystemSignature<MovementSystem>(signature);

    // Create entities
    auto entity1 = coordinator.CreateEntity();
    coordinator.AddComponent(entity1, Position{0.0f, 0.0f});
    coordinator.AddComponent(entity1, Velocity{1.0f, 2.0f});

    auto entity2 = coordinator.CreateEntity();
    coordinator.AddComponent(entity2, Position{10.0f, 10.0f});
    coordinator.AddComponent(entity2, Velocity{-1.0f, 0.5f});

    // Main loop
    float dt = 0.016f;  // ~60 FPS
    for (int i = 0; i < 5; ++i) {
        std::cout << "Frame " << i << "\n";
        movementSystem->Update(dt);
        std::cout << "\n";
    }

    // Clean up entities when done
    coordinator.DestroyQueuedEntities();

    return 0;
}
```

This example demonstrates:
1. Creating and initializing the coordinator
2. Registering components
3. Creating and registering a system
4. Setting a system signature
5. Creating entities and adding components
6. Updating the system
7. Cleaning up entities