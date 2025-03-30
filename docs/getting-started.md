# Getting Started with SimplyECS

This guide will walk you through the process of setting up and using the SimplyECS framework in your own projects.

## Installation

### Using CMake (Recommended)

The easiest way to use SimplyECS is to include it in your CMake project:

1. Add the repository as a submodule (or copy the code directly):

```bash
git submodule add https://github.com/halitipek/SimplyECS.git extern/SimplyECS
```

2. Add the following to your CMakeLists.txt:

```cmake
# Add SimplyECS
add_subdirectory(extern/SimplyECS)

# Link against it
target_link_libraries(your_target PRIVATE ecs_core)
```

### Manual Integration

If you're not using CMake, you can manually include the headers and source files in your project:

1. Copy the `ecs_core/include` and `ecs_core/src` directories into your project
2. Add the include directory to your include path
3. Compile the source files along with your project

## Basic Concepts

Before diving into code, it's important to understand the core concepts of an Entity Component System:

### Entity

An entity is just an ID that represents an object in your game or application. It doesn't contain any data or behavior on its own.

### Component

Components are plain data structures that store specific attributes or state. For example, a Position component might store x and y coordinates.

### System

Systems contain the logic that operates on entities with specific components. For example, a Movement system might update the positions of all entities that have both Position and Velocity components.

### Coordinator

The coordinator is the central hub that manages entities, components, and systems. It handles creation and destruction of entities, assignment of components, and updates to systems.

## Creating Your First ECS Application

Let's walk through creating a simple application using SimplyECS:

### Step 1: Include the necessary headers

```cpp
#include <ecs/Coordinator.hpp>
#include <ecs/System.hpp>
#include <ecs/Types.hpp>
#include <vector>
#include <iostream>
```

### Step 2: Define some components

```cpp
struct Position {
    float x = 0.0f;
    float y = 0.0f;
};

struct Velocity {
    float x = 0.0f;
    float y = 0.0f;
};

struct Gravity {
    float force = 9.81f;
};
```

### Step 3: Create a system

```cpp
class PhysicsSystem : public ecs::System {
public:
    PhysicsSystem(ecs::Coordinator& coordinator) : m_coordinator(coordinator) {}

    void Update(float dt) override {
        for (auto& entity : m_entities.GetDataVector()) {
            auto& position = m_coordinator.GetComponent<Position>(entity);
            auto& velocity = m_coordinator.GetComponent<Velocity>(entity);
            
            if (m_coordinator.HasComponent<Gravity>(entity)) {
                auto& gravity = m_coordinator.GetComponent<Gravity>(entity);
                velocity.y += gravity.force * dt;
            }
            
            position.x += velocity.x * dt;
            position.y += velocity.y * dt;
        }
    }

private:
    ecs::Coordinator& m_coordinator;
};
```

### Step 4: Set up the ECS framework

```cpp
int main() {
    // Initialize the coordinator
    ecs::Coordinator coordinator;
    coordinator.Init();
    
    // Register components
    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    coordinator.RegisterComponent<Gravity>();
    
    // Register the physics system
    auto physicsSystem = coordinator.RegisterSystem<PhysicsSystem>(coordinator);
    
    // Set the system signature
    ecs::Signature signature;
    signature.set(coordinator.GetComponentTypeID<Position>());
    signature.set(coordinator.GetComponentTypeID<Velocity>());
    coordinator.SetSystemSignature<PhysicsSystem>(signature);
    
    // Create some entities
    std::vector<ecs::Entity> entities;
    
    // Entity with position and velocity (will move at constant velocity)
    auto e1 = coordinator.CreateEntity();
    coordinator.AddComponent(e1, Position{0.0f, 0.0f});
    coordinator.AddComponent(e1, Velocity{1.0f, 0.0f});
    entities.push_back(e1);
    
    // Entity with position, velocity, and gravity (will accelerate downward)
    auto e2 = coordinator.CreateEntity();
    coordinator.AddComponent(e2, Position{0.0f, 0.0f});
    coordinator.AddComponent(e2, Velocity{1.0f, 0.0f});
    coordinator.AddComponent(e2, Gravity{9.81f});
    entities.push_back(e2);
    
    // Main loop
    float dt = 0.016f;  // ~60 FPS
    for (int i = 0; i < 100; ++i) {
        physicsSystem->Update(dt);
        
        if (i % 10 == 0) {  // Only print every 10 frames
            std::cout << "Frame " << i << ":\n";
            for (size_t j = 0; j < entities.size(); ++j) {
                const auto& position = coordinator.GetComponent<Position>(entities[j]);
                std::cout << "  Entity " << j << ": (" << position.x << ", " << position.y << ")\n";
            }
        }
    }
    
    return 0;
}
```

## Next Steps

Now that you've created a basic ECS application, you can explore more advanced features of SimplyECS:

- Learn how to use the [EventBus](core-concepts.md#event-bus) for communication between systems
- Understand how to leverage the [DenseMap](core-concepts.md#dense-map) for efficient component storage
- Check out the [Geometry Wars sample](../samples/geometry_wars) for a complete game example

For a more detailed explanation of the core concepts, see the [Core Concepts](core-concepts.md) documentation.