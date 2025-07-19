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

#include "tvShow.h"
#include "settings.h"
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <list>

namespace seneca {

    // Default constructor
    TvShow::TvShow() : MediaItem("", "", 0), m_id("") {}

    // Parameterized constructor
    TvShow::TvShow(const std::string& id, const std::string& title, const std::string& summary, unsigned short year)
        : MediaItem(title, summary, year), m_id(id) {}

    // Destructor
    TvShow::~TvShow() {}

    // Display TV show and its episodes
    void TvShow::display(std::ostream& out) const {
        if (g_settings.m_tableView) {
            // Table display
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << m_episodes.size() << " | ";
            out << std::setw(4) << getYear() << " | ";
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
            // Detailed display with episodes
            size_t pos = 0;
            out << getTitle() << " [" << getYear() << "]\n";
            out << std::setw(getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < getSummary().size()) {
                out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }

            for (auto& item : m_episodes) {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                out << (item.m_title != "" ? item.m_title : "Episode " + std::to_string(item.m_numberOverall)) << '\n';

                pos = 0;
                while (pos < item.m_summary.size()) {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }

            out << std::setw(getTitle().size() + 7) << std::setfill('-') << "" << std::setfill(' ') << '\n';
        }
    }

    // Parses a line and creates a TvShow object
    TvShow* TvShow::createItem(const std::string& strShow) {
        if (strShow.empty() || strShow[0] == '#') {
            throw "Not a valid show.";
        }

        std::stringstream ss(strShow);
        std::string id, title, strYear, summary;

        if (!std::getline(ss, id, ',') || !std::getline(ss, title, ',') ||
            !std::getline(ss, strYear, ',') || !std::getline(ss, summary)) {
            throw "Not a valid show.";
        }

        MediaItem::trim(id);
        MediaItem::trim(title);
        MediaItem::trim(strYear);
        MediaItem::trim(summary);

        // Validate year
        for (char c : strYear) {
            if (!isdigit(c)) {
                throw "Not a valid show.";
            }
        }
        unsigned short year = static_cast<unsigned short>(std::stoi(strYear));

        return new TvShow(id, title, summary, year);
    }

    // Computes the average length of episodes
    double TvShow::getEpisodeAverageLength() const {
        if (m_episodes.empty()) return 0.0;
        unsigned int totalLength = std::accumulate(m_episodes.begin(), m_episodes.end(), 0u,
            [](unsigned int sum, const TvEpisode& episode) {
                return sum + episode.m_length;
            });
        return static_cast<double>(totalLength) / m_episodes.size();
    }

    // Returns episode titles that are 60 minutes or longer
    std::list<std::string> TvShow::getLongEpisodes() const {
        std::list<std::string> longEpisode;

        std::for_each(m_episodes.begin(), m_episodes.end(),
            [&](const TvEpisode& episode) {
                if (episode.m_length >= 3600) {
                    longEpisode.push_back(episode.m_title);
                }
            });

        return longEpisode;
    }

    // Converts time format (hh:mm:ss or hh.mm.ss) into seconds
    unsigned int TvShow::calculateSeconds(std::string& strTime) {
        for (char& ch : strTime) {
            if (ch == ':' || ch == '.') {
                ch = ' ';
            }
        }

        std::stringstream ss(strTime);
        unsigned int hours = 0, minutes = 0, seconds = 0;
        ss >> hours >> minutes >> seconds;

        return hours * 3600 + minutes * 60 + seconds;
    }

}



