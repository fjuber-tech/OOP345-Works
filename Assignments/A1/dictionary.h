/*
////////////////////////////////////////////////////////////////////////
Assignment 1
Full Name	: Fairooz Juber
Student ID# : 102907243
Email		: fjuber@myseneca.ca
Date		: 2025 - 05 - 31
Section		: NEE

Authenticity Declaration :
I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my assignments. This submitted piece of work
has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////////////
*/

#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>
#include <iostream>

namespace seneca {

    // Represents the part of speech for a word
    enum class PartOfSpeech {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };

    // Represents a single word entry with its definition and part of speech
    struct Word {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos{ PartOfSpeech::Unknown };
    };

    // Dictionary class that loads and manages words from a CSV file
    class Dictionary {
        Word* m_words{ nullptr };  // Dynamically allocated array of words
        size_t m_count{ 0 };       // Number of words stored

        void copyFrom(const Dictionary& other);
        void moveFrom(Dictionary&& other) noexcept;
        void clear();
        PartOfSpeech parsePOS(const std::string& token) const;

    public:
        Dictionary();                             // Default constructor
        Dictionary(const char* filename);         // Loads from CSV file
        ~Dictionary();                            // Destructor

        Dictionary(const Dictionary& other);              // Copy constructor
        Dictionary& operator=(const Dictionary& other);   // Copy assignment

        Dictionary(Dictionary&& other) noexcept;          // Move constructor
        Dictionary& operator=(Dictionary&& other) noexcept; // Move assignment

        void searchWord(const char* word) const;  // Search for a word in the dictionary
    };

    std::string to_string(PartOfSpeech pos);  // Converts enum to string (for output)
}

#endif // SENECA_DICTIONARY_H
