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

#include "collection.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

namespace seneca {

    // Constructor initializes name and observer
    Collection::Collection(const std::string& name) : m_name(name), m_observer(nullptr) {}

    // Destructor deletes all dynamically allocated MediaItems
    Collection::~Collection() {
        for (auto item : m_items) {
            delete item;
        }
    }

    // Returns collection name
    const std::string& Collection::name() const {
        return m_name;
    }

    // Returns number of items
    size_t Collection::size() const {
        return m_items.size();
    }

    // Registers observer callback function
    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
        m_observer = observer;
    }

    // Adds a new item to the collection (if title is unique)
    Collection& Collection::operator+=(MediaItem* item) {
        for (MediaItem* m_item : m_items) {
            if (m_item->getTitle() == item->getTitle()) {
                delete item; // Already exists, delete duplicate
                return *this;
            }
        }

        m_items.push_back(item);

        // Notify observer if registered
        if (m_observer) {
            m_observer(*this, *item);
        }

        return *this;
    }

    // Access item by index
    MediaItem* Collection::operator[](size_t idx) const {
        if (idx >= m_items.size()) {
            throw std::out_of_range("Bad index [" + std::to_string(idx) +
                "]. Collection has " + std::to_string(m_items.size()) + " items.");
        }
        return m_items[idx];
    }

    // Access item by title (returns nullptr if not found)
    MediaItem* Collection::operator[](const std::string& title) const {
        auto it = std::find_if(m_items.begin(), m_items.end(), [&title](const MediaItem* item) {
            return item->getTitle() == title;
            });
        return (it != m_items.end()) ? *it : nullptr;
    }

    // Removes surrounding quotes from a string
    void Collection::trimQuote(std::string& str) {
        if (!str.empty() && str.front() == '\"') {
            str.erase(0, 1);
        }
        if (!str.empty() && str.back() == '\"') {
            str.pop_back();
        }
    }

    // Removes quotes from titles and summaries of all media items
    void Collection::removeQuotes() {
        std::for_each(m_items.begin(), m_items.end(), [this](MediaItem* item) {
            std::string title = item->getTitle();
            trimQuote(title);
            item->setTitle(title);

            std::string summary = item->getSummary();
            trimQuote(summary);
            item->setSummary(summary);
            });
    }

    // Sorts the collection by a specified field
    void Collection::sort(const std::string& field) {
        auto comparator = [&](MediaItem* a, MediaItem* b) {
            if (field == "title") {
                return a->getTitle() < b->getTitle();
            }
            if (field == "summary") {
                return a->getSummary() < b->getSummary();
            }
            if (field == "year") {
                return a->getYear() < b->getYear();
            }
            return false;
            };

        std::sort(m_items.begin(), m_items.end(), comparator);
    }

    // Overloads << to output each media item in the collection
    std::ostream& operator<<(std::ostream& out, const Collection& collection) {
        for (size_t i = 0; i < collection.size(); i++) {
            collection[i]->display(out);
        }
        return out;
    }

}

