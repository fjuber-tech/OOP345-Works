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
#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h" 

namespace seneca {

    // Archer class template using SuperHealth and a single weapon
    template <typename Weapon_t>
    class Archer : public CharacterTpl<SuperHealth> {
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon; // weapon stored, but not used in attack calculation

    public:
        // Constructor
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<SuperHealth>(name, healthMax),
            m_baseDefense(baseDefense),
            m_baseAttack(baseAttack),
            m_weapon(weapon) {}

        // Returns base attack multiplied by 1.3 (weapon is ignored)
        int getAttackAmnt() const override {
            return static_cast<int>(1.3 * m_baseAttack);
        }

        // Returns base defense multiplied by 1.2
        int getDefenseAmnt() const override {
            return static_cast<int>(1.2 * m_baseDefense);
        }

        // Clones this object dynamically
        Character* clone() const override {
            return new Archer(*this);
        }

        // Attacks an enemy by calculating and applying damage
        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            int damage = getAttackAmnt();

            std::cout << "    Archer deals " << damage << " ranged damage!" << std::endl;

            enemy->takeDamage(damage);
        }

        // Receives damage from an attacker, reduced by defense value
        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

            dmg -= getDefenseAmnt();
            if (dmg < 0) dmg = 0;

            CharacterTpl<SuperHealth>::takeDamage(dmg);
        }
    };

}

#endif 

