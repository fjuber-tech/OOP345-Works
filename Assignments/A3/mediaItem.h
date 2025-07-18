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

#ifndef SENECA_MEDIAITEM_H
#define SENECA_MEDIAITEM_H

#include <string>
#include <iostream>

namespace seneca
{
	class MediaItem
	{
		std::string m_title{};
		std::string m_summary{};
		unsigned short m_year{};
	protected:
		static void trim(std::string& str)
		{
			size_t i = 0u;
			for (i = 0u; i < str.length() && str[i] == ' '; ++i);
			str = str.substr(i);

			for (i = str.length(); i > 0 && str[i - 1] == ' '; --i);
			str = str.substr(0, i);
		}
	public:
		MediaItem(const std::string& title, const std::string& summary, unsigned short year) :
			m_title{title}, m_summary{summary}, m_year{year} { }
		virtual ~MediaItem() = default;

		std::string getTitle() const { return m_title; }
		void setTitle(const std::string& title) { m_title = title; }
		std::string getSummary() const { return m_summary; }
		void setSummary(const std::string& summary) { m_summary = summary; }
		unsigned short getYear() const { return m_year; }
		//void setYear(unsigned short year) { m_year = year; }

		virtual void display(std::ostream& out = std::cout) const = 0;

		template<typename Functor_t>
		void fixSpelling(Functor_t& spellChecker)
		{
			spellChecker(m_title);
			spellChecker(m_summary);
		}
	};
	inline std::ostream& operator<<(std::ostream& out, const MediaItem& item)
	{
		item.display(out);
		return out;
	}
}

#endif
