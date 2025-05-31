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

