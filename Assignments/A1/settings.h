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

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <string>

namespace seneca {

    struct Settings {
        bool m_show_all{ false };                // Show all definitions (default: false)
        bool m_verbose{ false };                 // Show part-of-speech (default: false)
        std::string m_time_units{ "nanoseconds" }; // Time units for durations
    };

    extern Settings g_settings;

}

#endif // SENECA_SETTINGS_H
