/*
////////////////////////////////////////////////////////////////////////
Assignment 3
Full Name	: Fairooz Juber
Student ID# : 102907243
Email		: fjuber@myseneca.ca
Date		: 2025 - 07 - 12
Section		: NEE

Authenticity Declaration :
I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my assignments. This submitted piece of work
has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////////////
*/

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <iostream>
#include <iomanip>

namespace seneca {

    // SpellChecker class performs replacement of bad words with correct ones
    class SpellChecker {
        static const size_t ARRAY_SIZE = 6;           // Fixed number of word pairs
        std::string m_badWords[ARRAY_SIZE];           // Misspelled words
        std::string m_goodWords[ARRAY_SIZE];          // Correct replacements
        size_t m_replaceCount[ARRAY_SIZE]{};          // Replacement counters

    public:
        // Loads bad-good word pairs from a file
        SpellChecker(const char* filename);

        // Replaces bad words in a given string and updates replacement stats
        void operator()(std::string& text);

        // Displays how many times each bad word was replaced
        void showStatistics(std::ostream& out) const;
    };

}

#endif

