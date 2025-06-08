/*
////////////////////////////////////////////////////////////////////////
Assignment 2
Full Name	: Fairooz Juber
Student ID# : 102907243
Email		: fjuber@myseneca.ca
Date		: 2025 - 06 - 09
Section		: NEE

Authenticity Declaration :
I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my assignments. This submitted piece of work
has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////////////
*/
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"

namespace seneca {

    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseDefense{};   //basic defense
        int m_baseAttack{};    //basic attack power
        Ability_t m_ability{};  //special ability of the character
        Weapon_t m_weapon[2];  // Two weapons the character can use

    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense,
            Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax),
            m_baseDefense(baseDefense),
            m_baseAttack(baseAttack) {
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }

        int getAttackAmnt() const override {
            return static_cast<int>(
                m_baseAttack +
                static_cast<double>(m_weapon[0]) / 2 +
                static_cast<double>(m_weapon[1]) / 2
                );
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Barbarian(*this);
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            // Use special ability on self
            m_ability.useAbility(this);

            // Calculate base damage
            int damage = getAttackAmnt();

            // Enhance damage with special ability
            m_ability.transformDamageDealt(damage);

            std::cout << "    Barbarian deals " << damage << " melee damage!" << std::endl;

            // Apply damage to enemy
            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

            // Subtract defense from damage
            dmg -= m_baseDefense;
            if (dmg < 0) dmg = 0;

            // Let ability modify damage received
            m_ability.transformDamageReceived(dmg);

            // Call base class takeDamage
            CharacterTpl<T>::takeDamage(dmg);
        }
    };

}
#endif

