/*
////////////////////////////////////////////////////////////////////////
Assignment 3
Full Name	: Fairooz Juber
Student ID# : 102907243
Email		: fjuber@myseneca.ca
Date		: 2025 - 07 - 12
Section		: NEE

Authenticity Declaration :
I declare that this submission is the result of my own work and I only copied the code
that my professor provided to complete my assignments. This submitted piece of work
has not been shared with any other student or 3rd party content provider.
/////////////////////////////////////////////////////////////////////////
*/

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca {

    struct Settings {
        short m_maxSummaryWidth{ 80 };  // Max width of summary output
        bool m_tableView{ false };      // Whether to use table format
    };

    extern Settings g_settings;  // Global settings variable

};

#endif
