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

#include "book.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace seneca {

    // Default constructor
    Book::Book() : MediaItem("", "", 0), m_author(""), m_country(""), m_price(0) {}

    // Parameterized constructor
    Book::Book(const std::string& title, const std::string& summary, unsigned short year,
        const std::string& author, const std::string& country, double price)
        : MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {}

    // Displays the book information
    void Book::display(std::ostream& out) const {
        if (g_settings.m_tableView) {
            // Display as a table row
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << m_country << " | ";
            out << std::setw(4) << getYear() << " | ";
            out << std::left;

            if (g_settings.m_maxSummaryWidth > -1) {
                if (static_cast<short>(getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << getSummary();
                else
                    out << getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << getSummary();
            out << std::endl;
        }
        else {
            size_t pos = 0;
            out << getTitle() << " [" << getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << std::setw(getTitle().size() + 7) << std::setfill('-') << "" << '\n';

            while (pos < getSummary().size()) {
                out << "    " << getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    // Creates a dynamically allocated Book object from a CSV-formatted string
    Book* Book::createItem(const std::string& strBook) {
        // Ignore empty lines or comments
        if (strBook.empty() || strBook[0] == '#') {
            throw "Not a valid book.";
        }

        std::stringstream stream(strBook);
        std::string author, title, country, strPrice, strYear, summary;

        // Parse CSV tokens
        if (!std::getline(stream, author, ',') || !std::getline(stream, title, ',') ||
            !std::getline(stream, country, ',') || !std::getline(stream, strPrice, ',') ||
            !std::getline(stream, strYear, ',') || !std::getline(stream, summary)) {
            throw "Not a valid book.";
        }

        // Trim whitespace from tokens
        MediaItem::trim(author);
        MediaItem::trim(title);
        MediaItem::trim(country);
        MediaItem::trim(summary);

        // Convert strings to appropriate types
        double price = std::stod(strPrice);
        unsigned short year = static_cast<unsigned short>(std::stoi(strYear));

        // Construct and return new Book
        return new Book(title, summary, year, author, country, price);
    }

}

