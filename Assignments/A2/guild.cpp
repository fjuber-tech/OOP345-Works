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
#include "guild.h"
#include <iostream>

using namespace std;

namespace seneca {

    // Default constructor
    Guild::Guild() : m_members(nullptr), m_count(0) {}

    // Constructor with name
    Guild::Guild(const char* name) : m_name(name), m_members(nullptr), m_count(0) {}

    // Copy constructor
    Guild::Guild(const Guild& other) : m_members(nullptr), m_count(0) {
        *this = other;
    }

    // Copy assignment operator
    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            cleanup();
            m_name = other.m_name;
            m_count = other.m_count;
            m_members = new Character * [m_count];
            for (size_t i = 0; i < m_count; ++i) {
                m_members[i] = other.m_members[i];
            }
        }
        return *this;
    }

    // Move constructor
    Guild::Guild(Guild&& other) noexcept
        : m_name(move(other.m_name)), m_members(other.m_members), m_count(other.m_count) {
        other.m_members = nullptr;
        other.m_count = 0;
    }

    // Move assignment operator
    Guild& Guild::operator=(Guild&& other) noexcept {
        if (this != &other) {
            cleanup();
            m_name = move(other.m_name);
            m_members = other.m_members;
            m_count = other.m_count;
            other.m_members = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

    // Destructor
    Guild::~Guild() {
        cleanup();
    }

    // Deallocates array (not characters)
    void Guild::cleanup() {
        delete[] m_members;
        m_members = nullptr;
        m_count = 0;
    }

    // Finds index of a character by name
    int Guild::findIndex(const string& name) const {
        for (size_t i = 0; i < m_count; ++i) {
            if (m_members[i]->getName() == name) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // Adds a character to the guild if not already present
    void Guild::addMember(Character* c) {
        if (findIndex(c->getName()) != -1) return; // Already in guild

        // Always increase max health by 300 (even if dead)
        c->setHealthMax(c->getHealthMax() + 300);

        // Resize and add to array
        Character** newList = new Character * [m_count + 1];
        for (size_t i = 0; i < m_count; ++i) {
            newList[i] = m_members[i];
        }
        newList[m_count] = c;

        delete[] m_members;
        m_members = newList;
        ++m_count;
    }

    // Removes a character by name and reduces their health
    void Guild::removeMember(const std::string& name) {
        int idx = findIndex(name);
        if (idx == -1) return; // Not found

        Character* toRemove = m_members[idx];

        // Always decrease max health by 300, regardless of alive status
        toRemove->setHealthMax(toRemove->getHealthMax() - 300);

        // Resize array
        Character** newList = new Character * [m_count - 1];
        for (size_t i = 0, j = 0; i < m_count; ++i) {
            if (static_cast<int>(i) != idx) {
                newList[j++] = m_members[i];
            }
        }

        delete[] m_members;
        m_members = newList;
        --m_count;
    }

    // Returns character pointer at index or nullptr if invalid
    Character* Guild::operator[](size_t idx) const {
        return (idx < m_count) ? m_members[idx] : nullptr;
    }

    // Displays all members or "No guild."
    void Guild::showMembers() const {
        if (m_count == 0 && m_name.empty()) {
            std::cout << "No guild." << std::endl;
        }
        else {
            std::cout << "[Guild] " << m_name << std::endl;
            for (size_t i = 0; i < m_count; ++i) {
                std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
            }
        }
    }



}
