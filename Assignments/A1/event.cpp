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
