/**
* @file WeaponComponent.hpp
 * @brief Component that defines which weapons an entity has.
 *
 * The WeaponComponent specifies what types of weapons an entity
 * has access to (gun, sonar, etc.).
 */
#ifndef WEAPONCOMPONENT_HPP
#define WEAPONCOMPONENT_HPP

struct WeaponComponent
{
    bool gun;    // Whether the entity has a gun
    bool sonar;  // Whether the entity has a sonar weapon

    WeaponComponent(const bool gun = false, const bool sonar = false)
    : gun(gun)
    , sonar(sonar)
    {
    };
};
#endif //WEAPONCOMPONENT_HPP