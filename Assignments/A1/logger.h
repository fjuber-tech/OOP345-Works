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

