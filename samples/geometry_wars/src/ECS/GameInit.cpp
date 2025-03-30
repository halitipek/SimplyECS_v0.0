/**
 * @file GameInit.cpp
 * @brief Implementation of the GameInit.
 */
#include "ECS/GameInit.hpp"

#include <ecs/Types.hpp>
#include "Components/AdvancedEnemyComponent.hpp"
#include "Components/BulletComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/EnemyComponent.hpp"
#include "Components/GlowComponent.hpp"
#include "Components/GunComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/InputComponent.hpp"
#include "Components/LifespanComponent.hpp"
#include "Components/LightAuraComponent.hpp"
#include "Components/ParticleComponent.hpp"
#include "Components/PlayerComponent.hpp"
#include "Components/ScoreComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/SonarWeaponComponent.hpp"
#include "Components/SoundWaveComponent.hpp"
#include "Components/TagComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/VelocityComponent.hpp"
#include "Components/WeaponComponent.hpp"
#include "Components/HealthChangeComponent.hpp"

#include "Systems/AdvancedEnemySystem.hpp"
#include "Systems/BoundarySystem.hpp"
#include "Systems/CollisionResponseSystem.hpp"
#include "Systems/CollisionSystem.hpp"
#include "Systems/EnemySpawnSystem.hpp"
#include "Systems/HealthSystem.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/LifespanSystem.hpp"
#include "Systems/MovementSystem.hpp"
#include "Systems/ParticleSystem.hpp"
#include "Systems/PlayerSpawnSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/ScoreSystem.hpp"
#include "Systems/WeaponSystem.hpp"

namespace GameInit
{
    void RegisterAllComponents(ecs::Coordinator& coordinator)
    {
        coordinator.RegisterComponent<TransformComponent>();
        coordinator.RegisterComponent<VelocityComponent>();
        coordinator.RegisterComponent<ShapeComponent>();
        coordinator.RegisterComponent<CollisionComponent>();
        coordinator.RegisterComponent<InputComponent>();
        coordinator.RegisterComponent<PlayerComponent>();
        coordinator.RegisterComponent<EnemyComponent>();
        coordinator.RegisterComponent<BulletComponent>();
        coordinator.RegisterComponent<ParticleComponent>();
        coordinator.RegisterComponent<SoundWaveComponent>();
        coordinator.RegisterComponent<HealthComponent>();
        coordinator.RegisterComponent<ScoreComponent>();
        coordinator.RegisterComponent<LifespanComponent>();
        coordinator.RegisterComponent<GlowComponent>();
        coordinator.RegisterComponent<LightAuraComponent>();
        coordinator.RegisterComponent<WeaponComponent>();
        coordinator.RegisterComponent<GunComponent>();
        coordinator.RegisterComponent<SonarWeaponComponent>();
        coordinator.RegisterComponent<TagComponent>();
        coordinator.RegisterComponent<AdvancedEnemyComponent>();
        coordinator.RegisterComponent<HealthChangeComponent>();
    }
    void RegisterAllSystems(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus)
    {
        coordinator.RegisterSystem<InputSystem>(window, coordinator, eventBus);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<PlayerComponent>());
            sig.set(coordinator.GetComponentTypeID<InputComponent>());
            coordinator.SetSystemSignature<InputSystem>(sig);
        }

        coordinator.RegisterSystem<PlayerSpawnSystem>(window, coordinator, eventBus);
        {
            ecs::Signature sig;
            coordinator.SetSystemSignature<PlayerSpawnSystem>(sig);
        }

        coordinator.RegisterSystem<EnemySpawnSystem>(window, coordinator, eventBus);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<EnemyComponent>());
            coordinator.SetSystemSignature<EnemySpawnSystem>(sig);
        }

        coordinator.RegisterSystem<WeaponSystem>(coordinator, eventBus);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<WeaponComponent>());
            coordinator.SetSystemSignature<WeaponSystem>(sig);
        }

        coordinator.RegisterSystem<AdvancedEnemySystem>(window, coordinator, eventBus);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<EnemyComponent>());
            sig.set(coordinator.GetComponentTypeID<AdvancedEnemyComponent>());
            coordinator.SetSystemSignature<AdvancedEnemySystem>(sig);
        }

        coordinator.RegisterSystem<MovementSystem>(coordinator);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<TransformComponent>());
            sig.set(coordinator.GetComponentTypeID<VelocityComponent>());
            coordinator.SetSystemSignature<MovementSystem>(sig);
        }

        coordinator.RegisterSystem<CollisionSystem>(coordinator, eventBus);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<TransformComponent>());
            sig.set(coordinator.GetComponentTypeID<CollisionComponent>());
            sig.set(coordinator.GetComponentTypeID<ShapeComponent>());
            coordinator.SetSystemSignature<CollisionSystem>(sig);
        }

        coordinator.RegisterSystem<BoundarySystem>(window, coordinator);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<TransformComponent>());
            sig.set(coordinator.GetComponentTypeID<ShapeComponent>());
            sig.set(coordinator.GetComponentTypeID<VelocityComponent>());
            coordinator.SetSystemSignature<BoundarySystem>(sig);
        }

        coordinator.RegisterSystem<CollisionResponseSystem>(window, coordinator, eventBus);
        {
            ecs::Signature sig;
            coordinator.SetSystemSignature<CollisionResponseSystem>(sig);
        }

        coordinator.RegisterSystem<LifespanSystem>(coordinator);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<LifespanComponent>());
            sig.set(coordinator.GetComponentTypeID<ShapeComponent>());
            coordinator.SetSystemSignature<LifespanSystem>(sig);
        }

        coordinator.RegisterSystem<HealthSystem>(coordinator, eventBus);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<HealthComponent>());
            sig.set(coordinator.GetComponentTypeID<ShapeComponent>());
            sig.set(coordinator.GetComponentTypeID<HealthChangeComponent>());
            coordinator.SetSystemSignature<HealthSystem>(sig);
        }

        coordinator.RegisterSystem<ParticleSystem>(coordinator, eventBus);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<ParticleComponent>());
            sig.set(coordinator.GetComponentTypeID<ShapeComponent>());
            coordinator.SetSystemSignature<ParticleSystem>(sig);
        }

        coordinator.RegisterSystem<ScoreSystem>(coordinator, eventBus);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<PlayerComponent>());
            sig.set(coordinator.GetComponentTypeID<ScoreComponent>());
            coordinator.SetSystemSignature<ScoreSystem>(sig);
        }

        coordinator.RegisterSystem<RenderSystem>(window, coordinator);
        {
            ecs::Signature sig;
            sig.set(coordinator.GetComponentTypeID<TransformComponent>());
            sig.set(coordinator.GetComponentTypeID<ShapeComponent>());
            coordinator.SetSystemSignature<RenderSystem>(sig);
        }
    }

} // namespace GameInit