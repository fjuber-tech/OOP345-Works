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

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include "mediaItem.h"
#include "settings.h"

namespace seneca {

    class Book : public MediaItem {
        std::string m_author;   // Book's author
        std::string m_country;  // Country of publication
        double m_price;         // Price of the book

        // Private constructors
        Book();
        Book(const std::string& title, const std::string& summary, unsigned short year,
            const std::string& author, const std::string& country, double price);
    public:
        // Overrides display from MediaItem
        void display(std::ostream& out) const override;

        // Creates a Book object from a CSV string
        static Book* createItem(const std::string& strBook);
    };

}

#endif


