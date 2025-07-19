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

#include "spellChecker.h"
#include <fstream>
#include <stdexcept>
#include <sstream>

namespace seneca {

    // Constructor reads the bad-good word pairs from file
    SpellChecker::SpellChecker(const char* filename) {
        for (size_t i = 0; i < ARRAY_SIZE; i++) {
            m_replaceCount[i] = 0; // Initialize replacement counters
        }

        std::ifstream file(filename);
        if (!file) {
            // Throw exception if file can't be opened
            throw "Could not open file: " + std::string(filename);
        }

        std::string line;
        for (size_t i = 0; i < ARRAY_SIZE && std::getline(file, line); i++) {
            if (!line.empty()) {
                std::stringstream ss(line);
                ss >> m_badWords[i] >> m_goodWords[i]; // Read each bad-good pair
            }
        }
    }

    // Replaces all instances of bad words in text with their correct form
    void SpellChecker::operator()(std::string& text) {
        for (size_t i = 0; i < ARRAY_SIZE; ++i) {
            size_t idx = 0;
            while ((idx = text.find(m_badWords[i], idx)) != std::string::npos) {
                text.replace(idx, m_badWords[i].length(), m_goodWords[i]);
                idx += m_goodWords[i].length();  // Move index forward
                m_replaceCount[i]++;             // Track how many times replaced
            }
        }
    }

    // Displays replacement statistics for each bad word
    void SpellChecker::showStatistics(std::ostream& out) const {
        out << "Spellchecker Statistics\n";
        for (size_t i = 0; i < ARRAY_SIZE; ++i) {
            out << std::left << std::setw(15) << m_badWords[i] << ": "
                << m_replaceCount[i] << " replacements" << std::endl;
        }
    }

}

