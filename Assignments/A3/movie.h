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

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include "mediaItem.h"

namespace seneca {

    class Movie : public MediaItem {
    public:
        // Default constructor
        Movie();

        // Parameterized constructor
        Movie(const std::string& title, const std::string& summary, unsigned short year);

        // Displays the movie's information
        void display(std::ostream& out = std::cout) const override;

        // Creates a Movie object from a CSV-formatted string
        static Movie* createItem(const std::string& strMovie);
    };

}

#endif


