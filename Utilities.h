//Name = Amitoj Singh Uppal
//ID   = 105186225
//Email= auppal12@myseneca.ca
//Date = 09 Nov, 2023
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <string>

namespace sdds {
	class Utilities {
		size_t m_widthField = 1;	//Instance Variable
		static char m_delimiter;	//class variable

	public:
		Utilities() = default;
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		//class functions
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};

}
#endif // !SDDS_UTILITIES_H