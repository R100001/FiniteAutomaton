
//------------------------------------------------------------------------

#include "Transition.h"

//------------------------------------------------------------------------

namespace Automata {

//------------------------------------------------------------------------

	std::fstream& operator>>(std::fstream& fin, Automata::Transition& transition) {
		std::string line;

		std::getline(fin, line);
		std::stringstream lineSs(line);

		lineSs >> transition.prevState;
		lineSs >> transition.symbol;
		lineSs >> transition.nextState;

		if (lineSs.bad()) fin.setstate(fin.badbit);

		return fin;
	}

//------------------------------------------------------------------------

	std::ostream& operator<<(std::ostream& cout, Transition trans) {
		cout << std::to_string(trans.prevState) + trans.symbol + std::to_string(trans.nextState);
		return cout;
	}

//------------------------------------------------------------------------

} // of namespace Automata
