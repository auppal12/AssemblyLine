//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 09 Nov, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include "Utilities.h"

namespace sdds {
	class Station {
		int m_id{};
		std::string m_itemName{};
		std::string m_description{};
		size_t m_serialNumber{};
		size_t m_quantity{};

		static size_t m_widthField;
		static unsigned int id_generator;
	public:
		Station() = default;
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !SDDS_STATION_H