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

#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include <string>
#include <chrono>
#include "event.h"

namespace seneca {

    class TimeMonitor {
        std::string m_name{};  // Name of the current event
        std::chrono::high_resolution_clock::time_point m_start;  // Start time of the event

    public:
        void startEvent(const char* name);   // Starts timing an event
        Event stopEvent();                   // Stops and returns an Event with duration
    };

}

#endif // SENECA_TIMEMONITOR_H

