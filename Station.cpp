//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 09 Nov, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include <iomanip>
#include "Station.h"

namespace sdds{

	size_t Station::m_widthField = 0;
	unsigned int Station::id_generator = 0;

	Station::Station(const std::string& str)
	{
		Utilities util;
		size_t next_pos = 0;
		bool flag = true;

		m_id = ++id_generator;
		m_itemName = util.extractToken(str, next_pos, flag);
		m_serialNumber = std::stoul(util.extractToken(str, next_pos, flag));
		m_quantity = std::stoul(util.extractToken(str, next_pos, flag));
	
		m_description = util.extractToken(str, next_pos, flag);
		m_description.erase(0, m_description.find_first_not_of(" ")); 
		m_description.erase(m_description.find_last_not_of(" ") + 1); 


		if (m_itemName.length() > m_widthField) {
			m_widthField = m_itemName.length();
		}
	}

	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return m_quantity;
	}

	void Station::updateQuantity()
	{
		if (m_quantity > 0)
			--m_quantity;
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << std::right << std::setw(3) << std::setfill('0') << m_id
			<< " | " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName
			<< " | " << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | ";

		if (full) {
			os << std::setfill(' ') << std::right << std::setw(4) << m_quantity <<  " | " << m_description;
		}

		os << std::endl;
	}
	
}