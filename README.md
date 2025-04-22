# SimplyECS - A Simple and Efficient Entity Component System

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

SimplyECS is a lightweight, high-performance Entity Component System (ECS) written in modern C++20. It provides a flexible and efficient framework for building complex game and simulation architectures.

![Geometry Wars Demo](docs/images/geometry_wars_demo.png)

## Features

- **Modern C++ Design**: Built with C++20 features for clean, efficient code
- **Lightweight**: Minimal overhead and dependencies
- **High Performance**: Optimized for cache-friendly data structures and fast iteration
- **Flexibility**: Easy to extend and adapt to your specific needs
- **Documented**: Comprehensive documentation and examples included

## Getting Started

### Prerequisites

- CMake 3.14 or higher
- C++20 compatible compiler

### Building from Source

```bash
# Clone the repository
git clone https://github.com/halitipek/SimplyECS_v0.0.git
cd SimplyECS

# Create a build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .
```

By default, all dependencies will be automatically downloaded and built (using CMake's FetchContent).

### Options

You can configure the build with the following CMake options:

- `SIMPLYECS_BUILD_SAMPLES=OFF` - Disable building the sample projects
- `SIMPLYECS_FETCH_DEPENDENCIES=OFF` - Disable automatic downloading of dependencies

### Running the Example

After building, you can run the Geometry Wars example:

```bash
cd bin  # Navigate to the output directory
./geometry_wars
```

## Usage Example

Here's a simple example of how to use the ECS framework:

```cpp
#include <ecs/Coordinator.hpp>
#include <iostream>

// Define some components
struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

// Define a system
class MovementSystem : public ecs::System {
public:
    void Update(float dt) {
        for (auto entity : m_entities) {
            auto& position = coordinator.GetComponent<Position>(entity);
            const auto& velocity = coordinator.GetComponent<Velocity>(entity);
            
            position.x += velocity.dx * dt;
            position.y += velocity.dy * dt;
        }
    }

    ecs::Coordinator& coordinator;
};

int main() {
    // Create the coordinator
    ecs::Coordinator coordinator;
    coordinator.Init();
    
    // Register components
    coordinator.RegisterComponent<Position>();
    coordinator.RegisterComponent<Velocity>();
    
    // Register system
    auto movementSystem = coordinator.RegisterSystem<MovementSystem>();
    movementSystem->coordinator = coordinator;
    
    // Set system signature
    ecs::Signature signature;
    signature.set(coordinator.GetComponentTypeID<Position>());
    signature.set(coordinator.GetComponentTypeID<Velocity>());
    coordinator.SetSystemSignature<MovementSystem>(signature);
    
    // Create an entity
    auto entity = coordinator.CreateEntity();
    coordinator.AddComponent(entity, Position{0.0f, 0.0f});
    coordinator.AddComponent(entity, Velocity{1.0f, 2.0f});
    
    // Main loop
    float dt = 0.016f;  // ~60 FPS
    for (int i = 0; i < 10; ++i) {
        movementSystem->Update(dt);
        
        // Print position
        const auto& position = coordinator.GetComponent<Position>(entity);
        std::cout << "Entity position: (" << position.x << ", " << position.y << ")\n";
    }
    
    return 0;
}
```

## Architecture

SimplyECS follows the classic Entity Component System architecture:

- **Entities** are simple IDs that reference a collection of components
- **Components** are pure data structures that hold specific attributes
- **Systems** contain the logic that operates on entities with specific component signatures

For more details about the design and implementation, see the [architecture guide](docs/architecture.md).

## Sample Project: Geometry Wars

Included with SimplyECS is a sample implementation of a Geometry Wars-like game. This example demonstrates how to use the ECS framework to build a complete game with:

- Player movement and shooting
- Enemy AI and pathfinding
- Collision detection and resolution
- Particle effects
- Game states and UI

## Documentation

Comprehensive documentation is available in the [docs](docs/) directory:

- [Getting Started Guide](docs/getting-started.md)
- [Core Concepts](docs/core-concepts.md)
- [API Reference](docs/api-reference.md)
- [Architecture Overview](docs/architecture.md)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by [EnTT](https://github.com/skypjack/entt) and various other ECS implementations.
- Sample game assets are free assets.
