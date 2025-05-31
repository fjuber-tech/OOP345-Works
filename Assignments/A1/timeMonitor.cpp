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
