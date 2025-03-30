# SimplyECS Architecture Guide

This document provides an in-depth look at the internal architecture of the SimplyECS framework. Understanding this architecture will help you use the framework more effectively and extend it as needed.

## High-Level Architecture

SimplyECS is built around five core components that work together to implement a full Entity Component System:

1. **Entity Manager**: Handles entity lifecycle (creation, tracking, destruction)
2. **Component Manager**: Manages component storage and entity-component relationships
3. **System Manager**: Manages systems and their entity signatures
4. **Event Bus**: Provides communication between systems
5. **Coordinator**: Coordinates the interaction between all managers

## Detailed Component Design

### Entity Manager

The Entity Manager is responsible for:

- Creating new entities (assigning unique IDs)
- Tracking which entities are currently active
- Managing entity destruction and ID recycling
- Storing entity signatures (which components each entity has)

Key implementation features:

- Entities are represented as 32-bit unsigned integers for efficiency
- Available entity IDs are stored in a queue for quick allocation and recycling
- Active entities are tracked using a DenseMap for efficient iteration
- Entity signatures are stored in a fixed-size array for quick lookup

### Component Manager

The Component Manager is responsible for:

- Registering component types
- Adding components to entities
- Removing components from entities
- Managing component storage and memory layout
- Retrieving components for entities

Key implementation features:

- Components are stored in type-specific arrays for cache efficiency
- The ComponentArray interface allows type-erasure for polymorphic storage
- Each component type gets a unique ID for signature matching
- DenseMap is used for efficient component storage and access

Component storage is organized by type rather than by entity, which is the key to the cache-friendly nature of ECS:

```
┌─────────────────────────┐
│ ComponentArray<Position>│
├─────────────────────────┤
│ Entity 1: {x: 0, y: 0}  │
│ Entity 2: {x: 5, y: 2}  │
│ Entity 4: {x: 3, y: 7}  │
└─────────────────────────┘

┌─────────────────────────┐
│ ComponentArray<Velocity>│
├─────────────────────────┤
│ Entity 1: {dx: 1, dy: 0}│
│ Entity 4: {dx: 0, dy: 1}│
└─────────────────────────┘
```

### System Manager

The System Manager is responsible for:

- Registering and managing systems
- Setting system signatures (which components a system needs)
- Notifying systems when entity signatures change
- Providing access to registered systems

Key implementation features:

- Systems inherit from a common base class for polymorphic storage
- System signatures define which entities a system operates on
- Systems are stored in a type map for easy retrieval
- Entity-system relationship updates happen when entity signatures change

### Event Bus

The Event Bus provides a way for systems to communicate without direct dependencies:

- Systems can subscribe to specific event types
- Any part of the code can emit events
- Events can be processed immediately or queued for later
- Event listeners are identified by unique IDs for removal

Key implementation features:

- Type-erased event storage using std::any
- Event listeners use templated callbacks for type safety
- Events can be processed immediately (fast mode) or queued
- Queued events are processed in a single batch to avoid cascade effects

### Coordinator

The Coordinator ties everything together and provides a simplified interface for the rest of the application:

- Initializes and manages all subsystems
- Provides high-level methods for entity and component operations
- Handles entity destruction queuing for safety
- Coordinates signature updates between component and system managers

### DenseMap

The DenseMap is a specialized container that provides:

- O(1) insertion, lookup, and removal
- Cache-friendly contiguous storage
- Efficient iteration over elements
- Minimal memory overhead

Implementation details:

- Uses a combination of a hash map and a vector
- The hash map maps keys to indices in the vector
- The vector stores the actual data contiguously
- Removals use the "swap and pop" technique for efficiency

## Memory Management

SimplyECS uses a combination of stack allocation, fixed-size arrays, and dynamic containers:

- Entity IDs and signatures use pre-allocated arrays for fixed-size storage
- Components are stored in type-specific DenseMap containers that grow as needed
- Systems are stored using shared pointers for lifecycle management
- Event queues use vectors for dynamic storage

## Data Flow

Here's how data flows through the system during typical operations:

1. **Entity Creation**:
    - Coordinator calls EntityManager to create a new entity
    - EntityManager assigns an ID and marks it as active
    - Returns the new entity ID

2. **Component Addition**:
    - Coordinator calls ComponentManager to add a component to an entity
    - ComponentManager stores the component in the appropriate ComponentArray
    - Coordinator updates the entity's signature
    - SystemManager is notified of the signature change
    - Systems update their entity lists based on the new signature

3. **System Update**:
    - Application calls Update on each system
    - System iterates through its matched entities
    - System retrieves components for each entity via the Coordinator
    - System performs its logic on the components
    - System may emit events through the EventBus

4. **Event Processing**:
    - EventBus processes queued events
    - Event listeners are called for each matching event
    - Systems react to events they're interested in

5. **Entity Destruction**:
    - Coordinator queues an entity for destruction
    - During DestroyQueuedEntities, each entity is:
        - Removed from the EntityManager
        - Components are removed by the ComponentManager
        - SystemManager removes the entity from all systems

## Extension Points

SimplyECS is designed to be extended in several ways:

- **New Component Types**: Simply define a new struct or class and register it
- **New Systems**: Inherit from the System base class to create custom logic
- **Custom Events**: Define new event structures for specific communication needs
- **Debug Hooks**: Override Debug functions for custom error handling
- **Custom Storage**: Implement custom component arrays for special storage needs

## Geometry Wars Sample Architecture

The Geometry Wars sample demonstrates how to build a complete game using SimplyECS:

- **Component Design**: Shows how to break down game objects into components
- **System Organization**: Demonstrates separation of concerns between systems
- **Event Communication**: Uses events for game state changes and collisions
- **State Management**: Implements a state machine for different game states
- **Resource Management**: Shows how to handle textures, fonts, and other resources

For more details on the Geometry Wars sample, see the [sample documentation](../samples/geometry_wars/README.md).

## Performance Considerations

For optimal performance with SimplyECS:

- Group related components together in systems for better cache utilization
- Use events for infrequent communication, not for high-frequency updates
- Avoid adding/removing components frequently during gameplay
- Consider component size when designing your data structures
- Profile your application to identify bottlenecks