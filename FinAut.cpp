
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

		if (!fin) throw Errors(0, Errors::ErrorType::fileDoesNotExist);

		filename = infile;

		// Read number of states
		fin >> nStates;
		if (fin.bad() || nStates < 1) 
			throw Errors(1, Errors::ErrorType::nStatesError);


		// Read the initial state
		fin >> initState;
		if (fin.bad() || initState < 1 || initState > nStates)
			throw Errors(2, Errors::ErrorType::initStateError);


		// Read number of final states
		int nFinalStates;
		fin >> nFinalStates;
		if (fin.bad() || nFinalStates < 0 || nFinalStates > nStates)
			throw Errors(3, Errors::ErrorType::nFinalStatesError);

		// Extracting the newline character from 'fin'
		fin.ignore();


		finalStates = std::vector<int>(nFinalStates);

		// Read the line with the final states
		std::string line;
		std::getline(fin, line);

		// and replace ',' with ' ' for easier parsing
		int count = 1;
		for (char& ch : line) {
			if (!nFinalStates) throw Errors::ErrorType::providedFinalStatesError;
			if (ch == ',') {
				ch = ' ';
				++count;
			}
		}

		// Check if the number of final states provided agrees with nFinalStates 
		if (count != nFinalStates)
			throw Errors(4, Errors::ErrorType::providedFinalStatesError);

		// Read final states
		{
			std::stringstream lineSs(line);
			for (unsigned int i = 0; i < finalStates.size(); ++i) {
				lineSs >> finalStates[i];
				if (lineSs.bad() || finalStates[i] < 1 || finalStates[i] > nStates)
					throw Errors(4, Errors::ErrorType::finalStatesError);
			}
		}


		// Read number of transitions
		int nTransitions;
		fin >> nTransitions;
		if (fin.bad() || nTransitions < 0)
			Errors(5, Errors::ErrorType::nTransitionsError);

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
			if (lineSs.bad() ||
				transitions[i].prevState < 0 || transitions[i].prevState > nStates ||
				transitions[i].nextState < 0 || transitions[i].nextState > nStates)
				throw Errors(6 + i, Errors::ErrorType::transitionsError);
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
	bool FiniteAutomaton::check_word(std::string word) const{

		if (!finalStates.size()) return false;

		// Initialize the two vectors that will be holding the current
		// and the future states respectivelly
		std::vector<int> currStates{ initState };
		std::vector<int> nextStates;

		// For every symbol in the given 'word'
		for (char symbol : word) {

			// First check if a dead end has been reached
			if (!currStates.size()) return false;

			// Then for every state check
			for (unsigned int i = 0; i < currStates.size(); ++i)

				// If any transition
				for (const Transition& transition : transitions)

					// Has the same starting state with the current one
					if (currStates[i] == transition.prevState) {

						// And check if the symbol is the same as the current symbol
						if (symbol == transition.symbol)
							nextStates.push_back(transition.nextState);

						// Or there is an e-transition and we need to push_back
						// the new states into the 'currStates' vector
						if (transition.symbol == Transition::eTrans)
							currStates.push_back(transition.nextState);

					}

			// Insert the new states into the 'currStates' vector
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
