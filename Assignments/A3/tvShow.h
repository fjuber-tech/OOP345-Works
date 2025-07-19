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

#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include <vector>
#include <list>
#include <string>
#include <sstream> 
#include <algorithm> 

namespace seneca {

    class TvShow;

    // Structure representing an individual episode
    struct TvEpisode {
        const TvShow* m_show{};               // Pointer to parent show
        unsigned short m_numberOverall{};     // Overall episode number
        unsigned short m_season{};            // Season number
        unsigned short m_numberInSeason{};    // Episode number in season
        std::string m_airDate{};              // Air date
        unsigned int m_length{};              // Duration in seconds
        std::string m_title{};                // Episode title
        std::string m_summary{};              // Episode summary
    };

    // Class representing a TV show
    class TvShow : public MediaItem {
    private:
        std::string m_id{};                   // Show ID
        std::vector<TvEpisode> m_episodes{};  // Episode list

        // Private constructors
        TvShow();
        TvShow(const std::string& id, const std::string& title, const std::string& summary, unsigned short year);

    public:
        ~TvShow();

        // Displays the show and episodes
        void display(std::ostream& out = std::cout) const override;

        // Builds a TvShow object from a CSV string
        static TvShow* createItem(const std::string& strShow);

        // Converts a time string (hh:mm:ss or hh.mm.ss) to seconds
        static unsigned int calculateSeconds(std::string& strTime);

        // Adds an episode to the show found in the collection
        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode) {
            std::string tempStrEpisode = strEpisode;
            MediaItem::trim(tempStrEpisode);
            if (tempStrEpisode.empty() || tempStrEpisode[0] == '#') {
                throw "Not a valid episode.";
            }

            TvEpisode episode;
            size_t idx = 0;

            // Extract show ID and find matching TvShow in the collection
            idx = tempStrEpisode.find(',');
            std::string strId = tempStrEpisode.substr(0, idx);
            MediaItem::trim(strId);
            TvShow* show = nullptr;
            for (size_t i = 0; i < col.size(); i++) {
                show = dynamic_cast<TvShow*>(col[i]);
                if (show && show->m_id == strId) {
                    episode.m_show = show;
                    break;
                }
            }

            if (!show) {
                throw std::runtime_error("Invalid show ID: " + strId);
            }

            // Parse episode details
            tempStrEpisode = tempStrEpisode.substr(idx + 1);

            idx = tempStrEpisode.find(',');
            std::string strEpisodeNumber = tempStrEpisode.substr(0, idx);
            MediaItem::trim(strEpisodeNumber);
            episode.m_numberOverall = std::stoi(strEpisodeNumber);
            tempStrEpisode = tempStrEpisode.substr(idx + 1);

            idx = tempStrEpisode.find(',');
            std::string strSeason = tempStrEpisode.substr(0, idx);
            MediaItem::trim(strSeason);
            episode.m_season = strSeason.empty() ? 1 : std::stoi(strSeason);
            tempStrEpisode = tempStrEpisode.substr(idx + 1);

            idx = tempStrEpisode.find(',');
            std::string strEpisodeInSeason = tempStrEpisode.substr(0, idx);
            MediaItem::trim(strEpisodeInSeason);
            episode.m_numberInSeason = std::stoi(strEpisodeInSeason);
            tempStrEpisode = tempStrEpisode.substr(idx + 1);

            idx = tempStrEpisode.find(',');
            std::string strAirDate = tempStrEpisode.substr(0, idx);
            MediaItem::trim(strAirDate);
            episode.m_airDate = strAirDate;
            tempStrEpisode = tempStrEpisode.substr(idx + 1);

            idx = tempStrEpisode.find(',');
            std::string strLength = tempStrEpisode.substr(0, idx);
            MediaItem::trim(strLength);
            episode.m_length = calculateSeconds(strLength);
            tempStrEpisode = tempStrEpisode.substr(idx + 1);

            idx = tempStrEpisode.find(',');
            std::string strTitle = tempStrEpisode.substr(0, idx);
            MediaItem::trim(strTitle);
            episode.m_title = strTitle;
            tempStrEpisode = tempStrEpisode.substr(idx + 1);

            MediaItem::trim(tempStrEpisode);
            episode.m_summary = tempStrEpisode;

            // Add to the show's episode list
            show->m_episodes.push_back(episode);
        }

        // Returns average length of all episodes
        double getEpisodeAverageLength() const;

        // Returns titles of episodes that are at least 60 minutes
        std::list<std::string> getLongEpisodes() const;
    };
}

#endif // SENECA_TVSHOW_H

