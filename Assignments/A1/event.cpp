#include "event.h"
#include "settings.h"
#include <iomanip>

using namespace std; 

namespace seneca {

    ostream& operator<<(ostream& os, const Event& event) {
        static int counter = 0;
        ++counter;

        int width = 11;
        string unit = g_settings.m_time_units;
        long long duration = event.m_duration.count();

        if (unit == "seconds") {
            duration /= 1'000'000'000;
            width = 2;
        }
        else if (unit == "milliseconds") {
            duration /= 1'000'000;
            width = 5;
        }
        else if (unit == "microseconds") {
            duration /= 1'000;
            width = 8;
        }

        os << setw(2) << counter << ": "
            << right << setw(40) << event.m_name << " -> "
            << right << setw(width) << duration << " " << unit;

        return os;
    }

}
