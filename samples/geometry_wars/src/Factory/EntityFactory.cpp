/**
 * @file EntityFactory.cpp
 * @brief Implementation of the EntityFactory.
 */
#include "EntityFactory.hpp"

#include <random>
#include <cmath>
#include <numbers>

#include "Managers/ConfigManager.hpp"
#include "Core/Math/Vec2.hpp"

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


namespace EntityFactory
{
    ecs::Entity SpawnPlayer(sf::RenderWindow& window, ecs::Coordinator& coordinator)
    {
        const ecs::Entity e = coordinator.CreateEntity();

        const auto& pConfig   = gConfig.GetGameConfig().player;
        const auto& sConfig   = gConfig.GetGameConfig().sonar;
        const auto& gunConfig = gConfig.GetGameConfig().bullet;

        const float posX = static_cast<float>(window.getSize().x) / 2.f;
        const float posY = static_cast<float>(window.getSize().y) / 2.f;

        coordinator.AddComponent<PlayerComponent>(e, {}); // Tag as player
        coordinator.AddComponent<TagComponent>(e, {EntityType::PLAYER}); // Add specific type tag
        coordinator.AddComponent<InputComponent>(e, {}); // Mark for input handling
        coordinator.AddComponent<TransformComponent>(e, {Vec2<float>(posX, posY), 0.f, 1.f, pConfig.rot});
        coordinator.AddComponent<VelocityComponent>(e, {Vec2<float>(0.f, 0.f), pConfig.speed});
        coordinator.AddComponent<CollisionComponent>(e, {pConfig.collisionRadius});
        coordinator.AddComponent<HealthComponent>(e, {pConfig.pointCount, pConfig.pointCount}); // Initial health = point count
        coordinator.AddComponent<ScoreComponent>(e, {0}); // Initial score
        coordinator.AddComponent<WeaponComponent>(e, {true, true}); // Enable gun and sonar
        coordinator.AddComponent<GunComponent>(e, {gunConfig.interval, gunConfig.interval, gunConfig.shapeRadius, gunConfig.speed, gunConfig.lifeSpan});
        coordinator.AddComponent<SonarWeaponComponent>(e, { sConfig.interval, sConfig.timer, sConfig.power, sConfig.minRadius, sConfig.maxRadius, sConfig.lifeSpan });

        ShapeComponent shape;
        shape.shapeType         = ShapeType::Circle;
        shape.points            = pConfig.pointCount;
        shape.radius            = pConfig.shapeRadius;
        shape.fillColor         = pConfig.fillColor;
        shape.outlineColor      = pConfig.outlineColor;
        shape.outlineThickness  = pConfig.outlineThickness;
        shape.originX           = pConfig.shapeRadius;
        shape.originY           = pConfig.shapeRadius;
        coordinator.AddComponent<ShapeComponent>(e, shape);

        GlowComponent glow(shape);
        glow.radius += 1.f;
        glow.originX = glow.radius;
        glow.originY = glow.radius;
        coordinator.AddComponent<GlowComponent>(e, glow);

        LightAuraComponent aura;
        coordinator.AddComponent<LightAuraComponent>(e, aura);

        return e;
    }
    ecs::Entity SpawnEnemy(sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::Entity player, bool isAdvanced)
    {
        const ecs::Entity e = coordinator.CreateEntity();

        const auto& eConfig      = gConfig.GetGameConfig().enemy;
        const float windowWidth  = static_cast<float>(window.getSize().x);
        const float windowHeight = static_cast<float>(window.getSize().y);

        std::random_device rd; // Obtain a random number from hardware
        std::mt19937 gen(rd()); // Seed the generator
        std::uniform_real_distribution<float> pxDist(eConfig.collisionRadius, windowWidth - eConfig.collisionRadius);
        std::uniform_real_distribution<float> pyDist(eConfig.collisionRadius, windowHeight - eConfig.collisionRadius);
        std::uniform_real_distribution<float> speedDist(eConfig.speedMin, eConfig.speedMax);
        std::uniform_real_distribution<float> rotDist(eConfig.rotMin, eConfig.rotMax);
        std::uniform_int_distribution<int> angleDist(0, 359); // Degrees
        std::discrete_distribution<int> vertexDist(eConfig.pointProbabilities.begin(), eConfig.pointProbabilities.end());

        const float speed         = speedDist(gen);
        const float rot           = rotDist(gen);
        const int initialAngleDeg = angleDist(gen);
        const int pointCount      = isAdvanced ? eConfig.pointCountMax
                                           : vertexDist(gen) + eConfig.pointCountMin; // + min because distribution gives index 0, 1, 2, 3

        const auto& playerPos = coordinator.GetComponent<TransformComponent>(player).position;
        float spawnX, spawnY;
        int attempts = 0;
        do {
            spawnX = pxDist(gen);
            spawnY = pyDist(gen);
            ++attempts;
            if (attempts > 50)
                break; // Stop trying after too many attempts
        }
        while (playerPos.DistanceSquared({spawnX, spawnY}) < (eConfig.spawnDistanceToPlayer * eConfig.spawnDistanceToPlayer));

        const float initialAngleRad = static_cast<float>(initialAngleDeg) * (std::numbers::pi_v<float> / 180.f);
        const float velX = std::cos(initialAngleRad) * speed;
        const float velY = std::sin(initialAngleRad) * speed;

        coordinator.AddComponent<EnemyComponent>(e, {}); // Tag as enemy
        coordinator.AddComponent<TagComponent>(e, {EntityType::ENEMY});
        coordinator.AddComponent<TransformComponent>(e, {Vec2<float>(spawnX, spawnY), 0.f, 1.f, rot});
        coordinator.AddComponent<VelocityComponent>(e, {Vec2<float>(velX, velY), speed});
        coordinator.AddComponent<CollisionComponent>(e, {eConfig.collisionRadius});
        coordinator.AddComponent<HealthComponent>(e, {pointCount, pointCount}); // Health = point count

        ShapeComponent shape;
        shape.shapeType         = ShapeType::Circle;
        shape.points            = pointCount;
        shape.radius            = eConfig.shapeRadius;
        shape.fillColor         = eConfig.fillColor;
        int colorIndex          = std::clamp(pointCount - eConfig.pointCountMin,
            0, static_cast<int>(eConfig.outlineColor.size() - 1));
        shape.outlineColor      = eConfig.outlineColor[colorIndex];
        shape.outlineThickness  = eConfig.outlineThickness;
        shape.originX           = eConfig.shapeRadius;
        shape.originY           = eConfig.shapeRadius;
        coordinator.AddComponent<ShapeComponent>(e, shape);

        if (isAdvanced || pointCount == eConfig.pointCountMax)
        {
            const float evadeThreshold = eConfig.advancedEnemy.at("evadeThreshold");
            const float evadeSpeedMult = eConfig.advancedEnemy.at("evadeSpeedMultiplier");
            AdvancedEnemyComponent adv(evadeThreshold, speed * evadeSpeedMult, speed);
            coordinator.AddComponent<AdvancedEnemyComponent>(e, adv);
        }

        return e;
    }
    ecs::Entity SpawnBullet(ecs::Coordinator& coordinator, const ecs::Entity parent, const float targetX, const float targetY)
    {
        const ecs::Entity e = coordinator.CreateEntity();

        const auto& parentPos = coordinator.GetComponent<TransformComponent>(parent).position;
        const auto& parentGun = coordinator.GetComponent<GunComponent>(parent);
        const auto& bConfig   = gConfig.GetGameConfig().bullet;

        Vec2<float> velocityDir = { targetX - parentPos.x, targetY - parentPos.y };
        velocityDir.Normalize();
        velocityDir *= parentGun.speed;

        coordinator.AddComponent<BulletComponent>(e, {}); // Tag as bullet
        coordinator.AddComponent<TagComponent>(e, {EntityType::BULLET});
        coordinator.AddComponent<TransformComponent>(e, {parentPos}); // Initial position = parent's position
        coordinator.AddComponent<VelocityComponent>(e, {velocityDir, parentGun.speed});
        coordinator.AddComponent<CollisionComponent>(e, {parentGun.radius + bConfig.outlineThickness});
        coordinator.AddComponent<LifespanComponent>(e, {parentGun.lifeSpan, parentGun.lifeSpan});

        ShapeComponent shape;
        shape.shapeType         = ShapeType::Circle;
        shape.points            = bConfig.pointCount;
        shape.radius            = parentGun.radius;
        shape.fillColor         = bConfig.fillColor;
        shape.outlineColor      = bConfig.outlineColor;
        shape.outlineThickness  = bConfig.outlineThickness;
        shape.originX           = parentGun.radius;
        shape.originY           = parentGun.radius;
        coordinator.AddComponent<ShapeComponent>(e, shape);

        return e;
    }
    ecs::Entity SpawnSoundWave(ecs::Coordinator& coordinator, const ecs::Entity parent)
    {
        const ecs::Entity e = coordinator.CreateEntity();

        const auto& parentPos   = coordinator.GetComponent<TransformComponent>(parent).position;
        const auto& parentSonar = coordinator.GetComponent<SonarWeaponComponent>(parent);
        const auto& sConfig     = gConfig.GetGameConfig().sonar;

        coordinator.AddComponent<TransformComponent>(e, {parentPos}); // Initial position = parent
        coordinator.AddComponent<LifespanComponent>(e, {parentSonar.lifeSpan, parentSonar.lifeSpan});
        coordinator.AddComponent<TagComponent>(e, {EntityType::SOUNDWAVE});
        coordinator.AddComponent<CollisionComponent>(e, {parentSonar.minRadius});  // Initial collision radius = min radius. Lifespan system will expand this.
        coordinator.AddComponent<SoundWaveComponent>(e, { parentSonar.power, parentSonar.minRadius, parentSonar.maxRadius });

        ShapeComponent shape;
        shape.shapeType                     = ShapeType::Vertex;
        shape.vertexShapeData.color         = sConfig.color;
        shape.vertexShapeData.radius        = parentSonar.minRadius;
        shape.vertexShapeData.segments      = sConfig.segments;
        coordinator.AddComponent<ShapeComponent>(e, shape);

        return e;
    }
    ecs::Entity SpawnParticle(ecs::Coordinator& coordinator, ecs::Entity parent, float angleDegrees, int previousHP)
    {
        const ecs::Entity e = coordinator.CreateEntity();

        const auto& parentPos = coordinator.GetComponent<TransformComponent>(parent).position;
        const auto& partConfig = gConfig.GetGameConfig().particle;
        const auto& eConfig = gConfig.GetGameConfig().enemy;

        const float angleRad = angleDegrees * (std::numbers::pi_v<float> / 180.f);
        const float velX = std::cos(angleRad) * partConfig.speed;
        const float velY = std::sin(angleRad) * partConfig.speed;

        coordinator.AddComponent<ParticleComponent>(e, {}); // Tag as particle
        coordinator.AddComponent<TagComponent>(e, {EntityType::PARTICLE});
        coordinator.AddComponent<TransformComponent>(e, {parentPos, 0.f, 1.f, partConfig.rot});
        coordinator.AddComponent<VelocityComponent>(e, {Vec2<float>(velX, velY), partConfig.speed});
        coordinator.AddComponent<LifespanComponent>(e, {partConfig.lifeSpan, partConfig.lifeSpan});

        ShapeComponent shape;
        shape.shapeType         = ShapeType::Circle;
        shape.points            = std::max(3, previousHP);
        shape.radius            = partConfig.shapeRadius;
        shape.fillColor         = partConfig.fillColor;
        int colorIndex          = std::clamp(previousHP - eConfig.pointCountMin,
            0, static_cast<int>(eConfig.outlineColor.size() - 1));
        shape.outlineColor      = eConfig.outlineColor[colorIndex];
        shape.outlineThickness  = partConfig.outlineThickness;
        shape.originX           = partConfig.shapeRadius;
        shape.originY           = partConfig.shapeRadius;
        coordinator.AddComponent<ShapeComponent>(e, shape);

        return e;
    }

} // namespace EntityFactory