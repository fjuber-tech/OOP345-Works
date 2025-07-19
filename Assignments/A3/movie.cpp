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

#include "movie.h"
#include "settings.h"
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>

namespace seneca {

    // Default constructor
    Movie::Movie() : MediaItem("", "", 0) {}

    // Constructor that initializes title, summary, and year
    Movie::Movie(const std::string& title, const std::string& summary, unsigned short year)
        : MediaItem(title, summary, year) {}

    // Displays movie info
    void Movie::display(std::ostream& out) const {
        if (g_settings.m_tableView) {
            // Table-formatted output
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << getYear() << " | ";
            out << std::left;

            if (g_settings.m_maxSummaryWidth > -1) {
                if (static_cast<short>(getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << getSummary();
                else
                    out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else {
                out << getSummary();
            }
            out << std::endl;
        }
        else {
            size_t pos = 0;
            out << getTitle() << " [" << getYear() << "]\n";
            out << std::setw(getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < getSummary().size()) {
                out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    // Parses a line from movies.csv and returns a Movie*
    Movie* Movie::createItem(const std::string& strMovie) {
        // Ignore empty lines and comments
        if (strMovie.empty() || strMovie[0] == '#') {
            throw "Not a valid movie.";
        }

        std::stringstream stream(strMovie);
        std::string title, strYear, summary;

        // Parse title
        if (!std::getline(stream, title, ',')) {
            throw "Not a valid movie.";
        }
        MediaItem::trim(title);

        // Parse year
        if (!std::getline(stream, strYear, ',')) {
            throw "Not a valid movie.";
        }
        MediaItem::trim(strYear);

        // Parse summary
        if (!std::getline(stream, summary)) {
            throw "Not a valid movie.";
        }
        MediaItem::trim(summary);

        // Validate and convert year
        unsigned short year = 0;
        for (char c : strYear) {
            if (!isdigit(c)) {
                throw "Not a valid movie.";
            }
        }
        year = static_cast<unsigned short>(std::stoi(strYear));

        // Return dynamically allocated Movie object
        return new Movie(title, summary, year);
    }

}


