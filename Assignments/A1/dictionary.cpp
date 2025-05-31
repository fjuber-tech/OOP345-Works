#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

namespace seneca {

    // Default constructor: initializes an empty dictionary
    Dictionary::Dictionary() = default;

    // Loads dictionary data from a CSV file
    Dictionary::Dictionary(const char* filename) {
        ifstream file(filename);
        if (!file) {
            m_words = nullptr;
            m_count = 0;
            return;
        }

        // First pass: count lines to allocate exact memory
        size_t lines = 0;
        string temp;
        while (getline(file, temp)) {
            if (!temp.empty()) lines++;
        }

        m_words = new Word[lines];
        m_count = 0;

        // Rewind the file to actually load content
        file.clear();
        file.seekg(0);

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string word, pos, def;

            getline(iss, word, ',');
            getline(iss, pos, ',');
            getline(iss, def);

            if (!word.empty() && !def.empty()) {
                m_words[m_count].m_word = word;
                m_words[m_count].m_definition = def;
                m_words[m_count].m_pos = parsePOS(pos);
                ++m_count;
            }
        }
    }

    // Destructor: cleans up dynamic memory
    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    // Copy constructor
    Dictionary::Dictionary(const Dictionary& other) {
        copyFrom(other);
    }

    // Copy assignment
    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    // Move constructor
    Dictionary::Dictionary(Dictionary&& other) noexcept {
        moveFrom(std::move(other));
    }

    // Move assignment
    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            clear();
            moveFrom(std::move(other));
        }
        return *this;
    }

    // Helper: Copy data from another Dictionary
    void Dictionary::copyFrom(const Dictionary& other) {
        m_count = other.m_count;
        m_words = new Word[m_count];
        for (size_t i = 0; i < m_count; ++i) {
            m_words[i] = other.m_words[i];
        }
    }

    // Helper: Move data from another Dictionary
    void Dictionary::moveFrom(Dictionary&& other) noexcept {
        m_words = other.m_words;
        m_count = other.m_count;

        other.m_words = nullptr;
        other.m_count = 0;
    }

    // Helper: Clear allocated memory
    void Dictionary::clear() {
        delete[] m_words;
        m_words = nullptr;
        m_count = 0;
    }

    // Parses part-of-speech string into enum value
    PartOfSpeech Dictionary::parsePOS(const std::string& token) const {
        if (token == "n." || token == "n. pl.") return PartOfSpeech::Noun;
        if (token == "adv.") return PartOfSpeech::Adverb;
        if (token == "a.") return PartOfSpeech::Adjective;
        if (token == "v." || token == "v. i." || token == "v. t." || token == "v. t. & i.") return PartOfSpeech::Verb;
        if (token == "prep.") return PartOfSpeech::Preposition;
        if (token == "pron.") return PartOfSpeech::Pronoun;
        if (token == "conj.") return PartOfSpeech::Conjunction;
        if (token == "interj.") return PartOfSpeech::Interjection;
        return PartOfSpeech::Unknown;
    }

    // Searches for a word and prints its definitions
    void Dictionary::searchWord(const char* word) const {
        string query = word;
        bool found = false;
        size_t printed = 0;

        for (size_t i = 0; i < m_count; ++i) {
            if (m_words[i].m_word == query) {
                // First line prints the word, others are indented
                if (printed == 0) {
                    cout << m_words[i].m_word;
                }
                else {
                    cout << setw(query.length()) << " ";
                }

                // Show part of speech if enabled and known
                if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                    cout << " - (" << to_string(m_words[i].m_pos) << ") ";
                }
                else {
                    cout << " - ";
                }

                cout << m_words[i].m_definition << '\n';
                ++printed;

                // Stop early if only first definition is requested
                if (!g_settings.m_show_all)
                    return;

                found = true;
            }
        }

        // Word not found
        if (printed == 0) {
            cout << "Word '" << word << "' was not found in the dictionary." << endl;
        }
    }

    // Converts PartOfSpeech enum to lowercase string
    string to_string(PartOfSpeech pos) {
        switch (pos) {
        case PartOfSpeech::Noun: return "noun";
        case PartOfSpeech::Pronoun: return "pronoun";
        case PartOfSpeech::Adjective: return "adjective";
        case PartOfSpeech::Adverb: return "adverb";
        case PartOfSpeech::Verb: return "verb";
        case PartOfSpeech::Preposition: return "preposition";
        case PartOfSpeech::Conjunction: return "conjunction";
        case PartOfSpeech::Interjection: return "interjection";
        default: return "";
        }
    }

}
