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

#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <string>
#include <chrono>
#include <iostream>

namespace seneca {

    class Event {
        std::string m_name{};
        std::chrono::nanoseconds m_duration{};

    public:
        Event() = default;

        Event(const char* name, const std::chrono::nanoseconds& duration)
            : m_name(name), m_duration(duration) {}

        friend std::ostream& operator<<(std::ostream& os, const Event& event);
    };

}

#endif // SENECA_EVENT_H
