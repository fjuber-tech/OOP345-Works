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

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include "mediaItem.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <functional>

namespace seneca {

    // Class representing a collection of MediaItem pointers
    class Collection {
        std::string m_name;                           // Collection name
        std::vector<MediaItem*> m_items;              // Container of MediaItem pointers
        void (*m_observer)(const Collection&, const MediaItem&); // Observer callback

        // Helper to trim surrounding quotes
        void trimQuote(std::string& str);

    public:
        // Constructor
        Collection(const std::string& name);

        // Disable copy/move operations
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) noexcept = delete;
        Collection& operator=(Collection&&) = delete;

        // Destructor
        ~Collection();

        // Iterators
        auto begin() { return m_items.begin(); }
        auto end() { return m_items.end(); }
        auto begin() const { return m_items.begin(); }
        auto end() const { return m_items.end(); }

        // Accessors
        const std::string& name() const;
        size_t size() const;

        // Observer registration
        void setObserver(void (*observer)(const Collection&, const MediaItem&));

        // Add item if not already in the collection
        Collection& operator+=(MediaItem* item);

        // Access item by index (throws on out-of-range)
        MediaItem* operator[](size_t idx) const;

        // Access item by title (returns nullptr if not found)
        MediaItem* operator[](const std::string& title) const;

        // Remove quotes from titles and summaries
        void removeQuotes();

        // Sort items by a specified field (title, summary, or year)
        void sort(const std::string& field);
    };

    // Overload for outputting collection to ostream
    std::ostream& operator<<(std::ostream& out, const Collection& collection);

}

#endif

