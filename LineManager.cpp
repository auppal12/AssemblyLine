#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;
namespace sdds {

    LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {

		Utilities utils{};

		ifstream input(file);
		string str{};
		if (input) {
			while (!input.eof()) {
				size_t next_pos = 0;
				bool more = true;

				getline(input, str);
				string first = utils.extractToken(str, next_pos, more);
				string last{};

				if (more)
					last = utils.extractToken(str, next_pos, more);
				else
					last = "";

				auto cur_station = find_if(stations.begin(), stations.end(), [&first](Workstation* w_station) {
					return w_station->getItemName() == first; });

				if (!last.empty()) {
					auto next_station = std::find_if(stations.begin(), stations.end(), [&last](Workstation* w_station) {
						return w_station->getItemName() == last; });

					if (cur_station != stations.end() && next_station != stations.end()) {
						(*cur_station)->setNextStation(*next_station);
						m_activeLine.push_back(*cur_station);
					}
					else
						throw "Cannot find";
				}
				else {
					if (cur_station != stations.end())
						m_activeLine.push_back(*cur_station);
				}
			}

			auto first_station = find_if(m_activeLine.begin(), m_activeLine.end(), [this](const Workstation* w_station) {
				return count_if(m_activeLine.begin(), m_activeLine.end(), [w_station](const Workstation* o_station) {
					if (o_station->getNextStation())
						return w_station->getItemName() == o_station->getNextStation()->getItemName();
					else
						return false;
				}) == 0;
			});

			if (first_station != m_activeLine.end())
				m_firstStation = *first_station;

			m_cntCustomerOrder = g_pending.size();
		}

		else
			throw "can not open the file";
	}

	void LineManager::reorderStations() {
		vector<Workstation*> new_ws{};
		Workstation* ws = m_firstStation;

		while (ws != nullptr)
		{
			new_ws.push_back(ws);
			ws = ws->getNextStation();
		}
		m_activeLine = new_ws;
	}

	bool LineManager::run(ostream& os) {
		static size_t iterationCount = 0;
		os << "Line Manager Iteration: " << ++iterationCount << endl;

		if (!g_pending.empty()) {
			(*m_firstStation) += move(g_pending.front());
			g_pending.pop_front();
		}

		for (auto& station : m_activeLine)
			station->fill(os);

		for (auto& station : m_activeLine)
			station->attemptToMoveOrder();

		return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
	}

	void LineManager::display(ostream& os) const
	{
		for (auto& station : m_activeLine)
			station->display(os);
	}
}