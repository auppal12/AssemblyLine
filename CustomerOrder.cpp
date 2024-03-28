#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include "CustomerOrder.h"

namespace sdds {
	size_t CustomerOrder::m_widthField{};
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities util;
		size_t next_pos = 0;
		bool flag = true;

		m_name = util.extractToken(str, next_pos, flag);
		m_product = util.extractToken(str, next_pos, flag);
		m_cntItem = std::count(str.begin(), str.end(), util.getDelimiter()) - 1;

		m_lstItem = new Item* [m_cntItem];
		for (size_t i = 0; i < m_cntItem; ++i) {
			m_lstItem[i] = new Item(util.extractToken(str, next_pos, flag));
		}

		if (m_widthField < util.getFieldWidth()) {
			m_widthField = util.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& other)
	{
		throw std::string("ERROR: Not allowed");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
	{
		*this = std::move(other);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		if (this != &other) {
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;

			m_name = other.m_name;
			m_product = other.m_product;
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;
			m_widthField = other.m_widthField;

			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
			other.m_name = "\0";
			other.m_product = "\0";
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}

		delete[] m_lstItem;
		m_lstItem = nullptr;

	}

	bool CustomerOrder::isOrderFilled() const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool flag = false;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_isFilled == flag && m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << std::setw(11) << std::right << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					flag = true;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; ++i) {
			os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}
			os << std::endl;
		}
	}
}