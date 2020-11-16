
//------------------------------------------------------------------------

#include "FinAut.h"

//------------------------------------------------------------------------

namespace Automata {

//------------------------------------------------------------------------

	// Define an automaton reading its states and transitions
	// Inputs:
	//		std::fstream fin: A filestream with a definition for an automaton
	// Outputs:
	//
	FiniteAutomaton::FiniteAutomaton(std::fstream fin) {

		// Read number of states
		fin >> nStates;


		// Read the initial state
		fin >> initState;


		// Read number of final states
		int nFinalStates;
		fin >> nFinalStates;

		finalStates = std::vector<int>(nFinalStates);

		// Read the line with the final states
		std::string line;
		std::getline(fin, line);

		// and replace ',' with ' ' for easier parsing
		for (char& ch : line)
			if (ch == ',')
				ch = ' ';

		// Read final states
		{
			std::stringstream lineSs(line);
			for (unsigned int i = 0; i < finalStates.size(); ++i)
				lineSs >> finalStates[i];
		}


		// Read number of transitions
		int nTransitions;
		fin >> nTransitions;

		transitions = std::vector<transition>(nTransitions);

		// Read transitions
		for (unsigned int i = 0; i < transitions.size(); ++i) {
			std::getline(fin, line);
			std::stringstream lineSs(line);

			lineSs >> transitions[i].prevState;
			lineSs >> transitions[i].symbol;
			lineSs >> transitions[i].nextState;
		}

		currState = initState;
		
	} // of constructor FiniteAutomaton

//------------------------------------------------------------------------

} // of namespace Automata