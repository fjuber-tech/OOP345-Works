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
#include "team.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace seneca {

    // Default constructor 
    Team::Team() : m_members(nullptr), m_count(0) {}

    // Constructor with team name
    Team::Team(const char* name) : m_name(name), m_members(nullptr), m_count(0) {}

    // Copy constructor 
    Team::Team(const Team& other) : m_members(nullptr), m_count(0) {
        *this = other;
    }

    // Copy assignment operator 
    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            cleanup();
            m_name = other.m_name;
            m_count = other.m_count;
            m_members = new Character * [m_count];
            for (size_t i = 0; i < m_count; ++i) {
                m_members[i] = other.m_members[i]->clone();
            }
        }
        return *this;
    }

    // Move constructor
    Team::Team(Team&& other) noexcept
        : m_name(move(other.m_name)), m_members(other.m_members), m_count(other.m_count) {
        other.m_members = nullptr;
        other.m_count = 0;
    }

    // Move assignment operator
    Team& Team::operator=(Team&& other) noexcept {
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
    Team::~Team() {
        cleanup();
    }

    // Helper: Deletes all characters and the dynamic array
    void Team::cleanup() {
        for (size_t i = 0; i < m_count; ++i) {
            delete m_members[i];
        }
        delete[] m_members;
        m_members = nullptr;
        m_count = 0;
    }

    // Helper: Returns index of a character by name or -1 if not found
    int Team::findIndex(const string& name) const {
        for (size_t i = 0; i < m_count; ++i) {
            if (m_members[i]->getName() == name) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // Adds a deep copy of the character to the team if it's not already present
    void Team::addMember(const Character* c) {
        if (findIndex(c->getName()) != -1) return; // skip duplicate

        Character** newList = new Character * [m_count + 1];
        for (size_t i = 0; i < m_count; ++i) {
            newList[i] = m_members[i];
        }
        newList[m_count] = c->clone(); // deep copy of character

        delete[] m_members;
        m_members = newList;
        ++m_count;
    }

    // Removes a character from the team by name
    void Team::removeMember(const string& name) {
        int index = findIndex(name);
        if (index == -1) return;

        delete m_members[index]; // delete character
        for (size_t i = index; i < m_count - 1; ++i) {
            m_members[i] = m_members[i + 1];
        }

        --m_count;

        if (m_count == 0) {
            delete[] m_members;
            m_members = nullptr;
        }
        else {
            Character** newList = new Character * [m_count];
            for (size_t i = 0; i < m_count; ++i) {
                newList[i] = m_members[i];
            }
            delete[] m_members;
            m_members = newList;
        }
    }

    // Returns character pointer at a given index, or nullptr if out of bounds
    Character* Team::operator[](size_t idx) const {
        return (idx < m_count) ? m_members[idx] : nullptr;
    }

    // Displays the team name and all members (or "No team." if empty)
    void Team::showMembers() const {
        if (m_count == 0) {
            cout << "No team." << endl;
        }
        else {
            cout << "[Team] " << m_name << endl;
            for (size_t i = 0; i < m_count; ++i) {
                cout << "    " << i + 1 << ": " << *m_members[i] << endl;
            }
        }
    }

}
