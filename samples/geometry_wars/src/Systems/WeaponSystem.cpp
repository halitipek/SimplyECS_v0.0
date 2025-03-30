/**
* @file WeaponSystem.cpp
 * @brief Implementation of the WeaponSystem.
 */
#include "WeaponSystem.hpp"

#include "Components/GunComponent.hpp"
#include "Components/SonarWeaponComponent.hpp"
#include "Components/WeaponComponent.hpp"
#include "Factory/EntityFactory.hpp"

WeaponSystem::WeaponSystem(ecs::Coordinator& coordinator, ecs::EventBus& eventBus)
: m_coordinator(coordinator)
, m_eventBus(eventBus)
{
    m_eventBus.AddListener<FireBulletEvent>(
        [this](const FireBulletEvent& event) {
            OnFireBullet(event);
        }
    );

    m_eventBus.AddListener<SonarAttackEvent>(
        [this](const SonarAttackEvent& event) {
            OnSonarAttack(event);
        }
    );
}

void WeaponSystem::Update(const float dt)
{
    for (auto [entity, _] : m_entities)
    {
        auto& weaponComp = m_coordinator.GetComponent<WeaponComponent>(entity);

        if (weaponComp.gun)
        {
            auto& gunComp = m_coordinator.GetComponent<GunComponent>(entity);
            gunComp.timer -= dt;
        }

        if (weaponComp.sonar)
        {
            auto& sonarComp = m_coordinator.GetComponent<SonarWeaponComponent>(entity);
            sonarComp.timer -= dt;
        }
    }
}

void WeaponSystem::OnFireBullet(const FireBulletEvent &event)
{
    auto& gunComp = m_coordinator.GetComponent<GunComponent>(event.entity);
    if (gunComp.timer > 0.f)
        return;

    EntityFactory::SpawnBullet(m_coordinator, event.entity, event.targetX, event.targetY);
    gunComp.timer = gunComp.interval;
}

void WeaponSystem::OnSonarAttack(const SonarAttackEvent &event)
{
    auto& sonarComp = m_coordinator.GetComponent<SonarWeaponComponent>(event.entity);
    if (sonarComp.timer > 0.f)
        return;

    EntityFactory::SpawnSoundWave(m_coordinator, event.entity);
    sonarComp.timer = sonarComp.interval;
}