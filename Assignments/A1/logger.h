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

#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include "event.h"

namespace seneca {

    class Logger {
        Event* m_events{ nullptr };
        size_t m_count{ 0 };
        size_t m_capacity{ 0 };

        void resize();  // Resizes array when needed

    public:
        Logger();                     // Default constructor
        ~Logger();                    // Destructor

        // Disable copy operations
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        // Move operations
        Logger(Logger&& other) noexcept;
        Logger& operator=(Logger&& other) noexcept;

        void addEvent(const Event& event);

        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);
    };

}

#endif // SENECA_LOGGER_H

