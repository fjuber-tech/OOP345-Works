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
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <string>
#include "character.h"

namespace seneca {

    // The Guild class manages a list of Character pointers using aggregation.
    class Guild {
        std::string m_name{};     // Name of the guild
        Character** m_members{};  // Dynamic array of Character pointers (not owned)
        size_t m_count{};         // Number of members

        // Finds index of a character by name, or -1 if not found
        int findIndex(const std::string& name) const;

        // Deallocates the character pointer array (not the characters)
        void cleanup();

    public:
        // Default constructor
        Guild();

        // Constructor with a name
        Guild(const char* name);

        // Rule of 5
        Guild(const Guild& other);
        Guild& operator=(const Guild& other);
        Guild(Guild&& other) noexcept;
        Guild& operator=(Guild&& other) noexcept;
        ~Guild();

        // Adds a member to the guild and boosts their health by 300
        void addMember(Character* c);

        // Removes a member from the guild and reduces their health by 300
        void removeMember(const std::string& name);

        // Returns the character pointer at index or nullptr if invalid
        Character* operator[](size_t idx) const;

        // Displays guild members or "No guild." if empty
        void showMembers() const;
    };

}

#endif

