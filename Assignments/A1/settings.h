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
