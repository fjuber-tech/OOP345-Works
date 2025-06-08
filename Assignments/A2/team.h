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
#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <string>
#include "character.h"

namespace seneca {

    // The Team class manages a dynamic array of Character pointers using composition.
    class Team {
        std::string m_name{};     // Name of the team
        Character** m_members{};  // Dynamic array of Character pointers
        size_t m_count{};         // Number of members in the team

        // Helper: Returns the index of the member with a matching name or -1 if not found
        int findIndex(const std::string& name) const;

        // Helper: Deletes all characters and deallocates the member array
        void cleanup();

    public:
        // Default constructor
        Team();

        // Constructor with team name
        Team(const char* name);

        // Rule of 5:
        // Copy constructor
        Team(const Team& other);

        // Copy assignment operator
        Team& operator=(const Team& other);

        // Move constructor
        Team(Team&& other) noexcept;

        // Move assignment operator
        Team& operator=(Team&& other) noexcept;

        // Destructor
        ~Team();

        // Adds a character to the team if not already present
        void addMember(const Character* c);

        // Removes a character from the team by name
        void removeMember(const std::string& name);

        // Returns a pointer to the character at the given index, or nullptr if out of bounds
        Character* operator[](size_t idx) const;

        // Displays the team name and all members, or prints "No team." if empty
        void showMembers() const;
    };

}

#endif 

