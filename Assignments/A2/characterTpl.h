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
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
#include "character.h"

namespace seneca {

    // T is the type used for storing health
    template <typename T>
    class CharacterTpl : public Character {
        int m_healthMax{};  // Max health
        T m_health;         // Current health of type T

    public:
        // Custom constructor
        CharacterTpl(const char* name, int healthMax)
            : Character(name), m_healthMax(healthMax) {
            m_health = healthMax;  
        }

        // Applies damage to the character
        void takeDamage(int dmg) override {
            m_health -= dmg;

            if (static_cast<int>(m_health) < 0) {
                m_health = 0;
            }

            if (!isAlive()) {
                std::cout << "    " << getName() << " has been defeated!" << std::endl;
            }
            else {
                std::cout << "    " << getName() << " took " << dmg
                    << " damage, " << static_cast<int>(m_health)
                    << " health remaining." << std::endl;

            }
        }

        // Gets current health
        int getHealth() const override {
            return static_cast<int>(m_health);
        }

        // Gets maximum health
        int getHealthMax() const override {
            return m_healthMax;
        }

        // Sets current health
        void setHealth(int health) override {
            m_health = health;
        }

        // Sets max health and resets current health to match
        void setHealthMax(int health) override {
            m_healthMax = health;
            m_health = health;
        }
    };

}

#endif

