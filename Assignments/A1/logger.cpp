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

#include "logger.h"
#include <iostream>

using namespace std;

namespace seneca {

    // Default constructor: initializes an empty logger
    Logger::Logger() = default;

    // Destructor: deallocates the dynamic array of events
    Logger::~Logger() {
        delete[] m_events;
    }

    // Move constructor: transfers ownership of dynamic resources
    Logger::Logger(Logger&& other) noexcept {
        m_events = other.m_events;
        m_count = other.m_count;
        m_capacity = other.m_capacity;

        // Reset source
        other.m_events = nullptr;
        other.m_count = 0;
        other.m_capacity = 0;
    }

    // Move assignment operator: handles self-assignment and moves resources
    Logger& Logger::operator=(Logger&& other) noexcept {
        if (this != &other) {
            delete[] m_events;

            m_events = other.m_events;
            m_count = other.m_count;
            m_capacity = other.m_capacity;

            // Reset source
            other.m_events = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    // Resizes the dynamic array to hold more events
    void Logger::resize() {
        size_t newCapacity = (m_capacity == 0) ? 4 : m_capacity * 2;
        Event* newArray = new Event[newCapacity];

        // Copy existing events to new array
        for (size_t i = 0; i < m_count; ++i) {
            newArray[i] = m_events[i];
        }

        // Clean up old array and update members
        delete[] m_events;
        m_events = newArray;
        m_capacity = newCapacity;
    }

    // Adds a copy of the event to the logger
    void Logger::addEvent(const Event& event) {
        if (m_count == m_capacity) {
            resize();  // Expand capacity if full
        }
        m_events[m_count++] = event;
    }

    // Friend helper: inserts all events into the output stream line by line
    ostream& operator<<(ostream& os, const Logger& logger) {
        for (size_t i = 0; i < logger.m_count; ++i) {
            os << logger.m_events[i] << endl;
        }
        return os;
    }

}
