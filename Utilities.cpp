//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 09 Nov, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <stdexcept>
#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter = ',';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token;
		size_t pos = str.find(m_delimiter, next_pos);

		if (pos == next_pos) {
			more = false;
			throw std::string("Delimiter found at", next_pos);
		}
		else if (pos == std::string::npos) {
			token = str.substr(next_pos);
			more = false;
		}
		else {
			token = str.substr(next_pos, pos - next_pos);
			more = true;
		}

		next_pos = pos + 1;

		token.erase(0, token.find_first_not_of(' ')); // leading spaces
		token.erase(token.find_last_not_of(' ') + 1); // trailing spaces

		if (token.length() > m_widthField) {
			m_widthField = token.length();
		}

		return token;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}