# Core Concepts of SimplyECS

This document explains the fundamental concepts and components of the SimplyECS framework.

## The Entity Component System Pattern

The Entity Component System (ECS) is an architectural pattern that follows the principle of composition over inheritance. It separates the data (components) from the behavior (systems) and uses entities as simple identifiers to link components together.

### Key Benefits of ECS

- **Improved Cache Locality**: Components of the same type are stored contiguously in memory
- **Flexibility**: Easy to add/remove capabilities to entities at runtime
- **Data-Oriented Design**: Focuses on how data is arranged and processed
- **Parallelization**: Systems can often be parallelized easily since they operate on specific groups of components

## Core Classes in SimplyECS

### Entity

In SimplyECS, an entity is simply a 32-bit integer ID. Entities don't store any data or behavior themselves; they merely serve as identifiers to link related components together.

```cpp
using Entity = std::uint32_t;
```

The `EntityManager` class handles entity creation, destruction, and tracking:

```cpp
ecs::Entity entity = coordinator.CreateEntity();
coordinator.DestroyEntity(entity);
bool isAlive = coordinator.IsEntityAlive(entity);
```

### Component

Components are plain data structures that store attributes for entities. They should be focused on a specific aspect of an entity, such as position, health, or appearance.

Example component definitions:

```cpp
struct TransformComponent {
    float x, y;
    float rotation;
    float scale;
};

struct HealthComponent {
    int current;
    int maximum;
};
```

The `ComponentManager` class handles component registration, assignment, and retrieval:

```cpp
// Register a component type
coordinator.RegisterComponent<TransformComponent>();

// Add component to entity
coordinator.AddComponent(entity, TransformComponent{0.0f, 0.0f, 0.0f, 1.0f});

// Retrieve component
auto& transform = coordinator.GetComponent<TransformComponent>(entity);
transform.x += 10.0f;

// Check if entity has component
bool hasTransform = coordinator.HasComponent<TransformComponent>(entity);

// Remove component
coordinator.RemoveComponent<TransformComponent>(entity);
```

### System

Systems contain the logic that operates on entities with specific components. Each system is responsible for a specific aspect of the game or application, such as movement, rendering, or collision detection.

Systems in SimplyECS inherit from the `System` base class:

```cpp
class MovementSystem : public ecs::System {
public:
    MovementSystem(ecs::Coordinator& coordinator) 
    : m_coordinator(coordinator) {}

    void Update(float dt) override {
        for (auto entity : m_entities.GetDataVector()) {
            auto& transform = m_coordinator.GetComponent<TransformComponent>(entity);
            auto& velocity = m_coordinator.GetComponent<VelocityComponent>(entity);
            
            transform.x += velocity.x * dt;
            transform.y += velocity.y * dt;
        }
    }

private:
    ecs::Coordinator& m_coordinator;
};
```

The `SystemManager` class handles system registration and updates:

```cpp
// Register a system
auto movementSystem = coordinator.RegisterSystem<MovementSystem>(coordinator);

// Define which components the system needs
ecs::Signature signature;
signature.set(coordinator.GetComponentTypeID<TransformComponent>());
signature.set(coordinator.GetComponentTypeID<VelocityComponent>());
coordinator.SetSystemSignature<MovementSystem>(signature);

// Update the system
movementSystem->Update(deltaTime);
```

### Signature

A signature is a bitset that defines which components an entity has or which components a system operates on. It's used for efficiently matching entities to systems.

```cpp
using Signature = std::bitset<MaxComponents>;
```

### Coordinator

The coordinator is the central hub that manages entities, components, and systems. It provides a simplified interface to interact with the entire ECS framework.

```cpp
// Initialize the coordinator
ecs::Coordinator coordinator;
coordinator.Init();

// Register components
coordinator.RegisterComponent<Position>();
coordinator.RegisterComponent<Velocity>();

// Create entity and add components
auto entity = coordinator.CreateEntity();
coordinator.AddComponent(entity, Position{0.0f, 0.0f});
coordinator.AddComponent(entity, Velocity{1.0f, 0.0f});

// Create system and set its signature
auto physicsSystem = coordinator.RegisterSystem<PhysicsSystem>();
ecs::Signature signature;
signature.set(coordinator.GetComponentTypeID<Position>());
signature.set(coordinator.GetComponentTypeID<Velocity>());
coordinator.SetSystemSignature<PhysicsSystem>(signature);

// Update system
physicsSystem->Update(deltaTime);

// Clean up entities queued for destruction
coordinator.DestroyQueuedEntities();
```

## Advanced Features

### Dense Map

The `DenseMap` is a specialized container used for efficient component storage. It provides fast insertion, deletion, and iteration while maintaining cache-friendly memory layout.

```cpp
DenseMap<Entity, TransformComponent> transformComponents;
transformComponents.Insert(entity, component);
auto& component = components.GetValue(entity);
components.Erase(entity);
```

### Event Bus

The `EventBus` provides a publish-subscribe mechanism for communication between systems without direct dependencies.

```cpp
// Define event type
struct CollisionEvent {
    Entity entity1;
    Entity entity2;
};

// Add listener
eventBus.AddListener<CollisionEvent>([](const CollisionEvent& event) {
    // Handle collision
});

// Emit event
eventBus.Emit<CollisionEvent>({entity1, entity2});

// Process queued events
eventBus.ProcessEvents();
```

### Debug Utilities

SimplyECS includes debug utilities for error detection and reporting:

```cpp
Debug::Assert(condition, "Error message with %s formatting", "string");
```

## Lifecycle Management

### Entity Lifecycle

1. **Creation**: Entities are created via the coordinator and assigned a unique ID
2. **Component Assignment**: Components are added to entities to define their attributes
3. **System Processing**: Systems operate on entities with specific component signatures
4. **Destruction**: Entities are marked for destruction and later removed along with their components

### Component Lifecycle

1. **Registration**: Component types are registered with the system
2. **Assignment**: Components are created and attached to entities
3. **Access**: Systems read and modify component data
4. **Removal**: Components can be removed from entities

## Performance Considerations

- **Component Size**: Keep components small and focused
- **Component Access Patterns**: Organize systems to access components in a cache-friendly manner
- **Event Usage**: Use events for infrequent communication, not for high-frequency updates
- **Entity Count**: Be mindful of the maximum entity count (default is 5000, can be adjusted)