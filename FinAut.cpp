
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
	FiniteAutomaton::FiniteAutomaton(std::string infile) {

		std::fstream fin{ infile };

		filename = infile;

		// Read number of states
		fin >> nStates;


		// Read the initial state
		fin >> initState;


		// Read number of final states
		int nFinalStates;
		fin >> nFinalStates;

		// Extracting the newline character from 'fin'
		fin.ignore();


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
			for (unsigned int i = 0; i < finalStates.size(); ++i) {
				lineSs >> finalStates[i];
			}
		}


		// Read number of transitions
		int nTransitions;
		fin >> nTransitions;

		// Extracting the newline character from 'fin'
		fin.ignore();


		transitions = std::vector<Transition>(nTransitions);

		// Read transitions
		for (unsigned int i = 0; i < transitions.size(); ++i) {
			std::getline(fin, line);
			std::stringstream lineSs(line);

			lineSs >> transitions[i].prevState;
			lineSs >> transitions[i].symbol;
			lineSs >> transitions[i].nextState;
		}

	} // of constructor FiniteAutomaton

//------------------------------------------------------------------------

	// Check if a word will be accepted from 'this' automaton
	// Inputs:
	//		std::string word: the given word
	// Outputs:
	//		bool true: 'word' was accepted
	//		bool false: 'word' was NOT accepted
	//
	bool FiniteAutomaton::check_word(std::string word) {

		// Initialize the two vectors that will be holding the current
		// and the future states respectivelly
		std::vector<int> currStates{ initState };
		std::vector<int> nextStates;

		// For every symbol in the given 'word'
		for (char symbol : word) {

			// First check if a dead end was reached
			if (!currStates.size()) return false;

			// Then for every state check
			for (int i = 0; i < currStates.size(); ++i)

				// If any transition
				for (const Transition& transition : transitions)

					// Has the same starting state with the current one
					if (currStates[i] == transition.prevState) {

						// And check if the symbol is the same as the current symbol
						if (symbol == transition.symbol)
							nextStates.push_back(transition.nextState);

						// Or there is an e-transition and we need to push_back
						// the new states into the 'currStates' vector
						if (transition.symbol == eTrans)
							currStates.push_back(transition.nextState);

					}

			// Insert the new states into the 'currStates' vector
			currStates.clear();
			currStates = nextStates;
			nextStates.clear();

		}

		// Check if any of the current states is a final one
		for (int state : currStates)
			for (int finalState : finalStates)
				if (state == finalState) return true;
		return false;

	} // of function FiniteAutomaton::check_word

//------------------------------------------------------------------------

} // of namespace Automata

//------------------------------------------------------------------------
