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


#include "timeMonitor.h"

using namespace std;
using namespace std::chrono;

namespace seneca {

    // Records the start time and stores the name of the event
    void TimeMonitor::startEvent(const char* name) {
        m_name = name;
        m_start = high_resolution_clock::now();
    }

    // Captures the end time, calculates duration, and returns an Event
    Event TimeMonitor::stopEvent() {
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - m_start);
        return Event(m_name.c_str(), duration);
    }

}
