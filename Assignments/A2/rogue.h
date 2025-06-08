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
#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "weapons.h" 

namespace seneca {

    // Rogue class template with flexible health and two special abilities
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense{};
        int m_baseAttack{};
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        Dagger m_weapon; // always uses a dagger

    public:
        // Constructors
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax),
            m_baseDefense(baseDefense),
            m_baseAttack(baseAttack),
            m_weapon{} {}

        // Returns total attack power using the formula: baseAttack + 2 * dagger damage
        int getAttackAmnt() const override {
            return static_cast<int>(m_baseAttack + 2 * static_cast<double>(m_weapon));
        }

        // Returns base defense
        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        // Dynamically creates a deep copy of this Rogue object
        Character* clone() const override {
            return new Rogue(*this);
        }

        // Attacks an enemy character with enhancements from both abilities
        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            // Use both abilities on self
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);

            // Get base attack amount
            int damage = getAttackAmnt();

            // Modify damage using both abilities
            m_firstAbility.transformDamageDealt(damage);
            m_secondAbility.transformDamageDealt(damage);

            std::cout << "    Rogue deals " << damage << " melee damage!" << std::endl;

            // Deal damage to the enemy
            enemy->takeDamage(damage);
        }

        // Takes incoming damage after applying defense and ability-based reductions
        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Rogue has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

            // Reduce damage by base defense
            dmg -= m_baseDefense;
            if (dmg < 0) dmg = 0;

            // Further reduce using abilities
            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);

            // Apply final damage
            CharacterTpl<T>::takeDamage(dmg);
        }
    };

}

#endif

