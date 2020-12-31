
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

		//------------------------------------------------------------------------------------------
		// READING FILE
		//------------------------------------------------------------------------------------------

		// Open a fstrean with 'infile'
		std::fstream fin{ infile };

		if (!fin) throw Errors(infile, 0, Errors::ErrorType::fileDoesNotExist);

		filename = infile;


		// Read number of states
		fin >> nStates;
		if (fin.bad() || nStates < 1) 
			throw Errors(infile, 1, Errors::ErrorType::nStatesError);


		// Read the initial state
		fin >> initState;
		if (fin.bad() || initState < 1 || initState > nStates)
			throw Errors(infile, 2, Errors::ErrorType::initStateError);
		--initState;


		// Read number of final states
		int nFinalStates;
		fin >> nFinalStates;
		if (fin.bad() || nFinalStates < 0 || nFinalStates > nStates)
			throw Errors(infile, 3, Errors::ErrorType::nFinalStatesError);

		// Extracting the newline character from 'fin'
		fin.ignore();

		finalStates = std::vector<int>(nFinalStates);

		// Read the line with the final states...
		std::string line;
		std::getline(fin, line);

		// ...and replace ',' with ' ' for easier parsing
		int count = 0;
		for (char& ch : line) {
			if (!count) ++count;
			if (!nFinalStates) throw Errors(infile, 4, Errors::ErrorType::providedFinalStatesError);
			if (ch == ',') {
				ch = ' ';
				++count;
			}
		}

		// Check if the number of final states provided agrees with nFinalStates 
		if (count != nFinalStates)
			throw Errors(infile, 4, Errors::ErrorType::providedFinalStatesError);

		// Read final states
		{
			std::stringstream lineSs(line);
			for (unsigned int i = 0; i < finalStates.size(); ++i) {
				lineSs >> finalStates[i];
				if (lineSs.bad() || finalStates[i] < 1 || finalStates[i] > nStates)
					throw Errors(infile, 4, Errors::ErrorType::finalStatesError);
				--finalStates[i];
				finalStatesSet.insert(finalStates[i]);
			}
		}


		// Read number of transitions
		int nTransitions;
		fin >> nTransitions;
		if (fin.bad() || nTransitions < 0)
			throw Errors(infile, 5, Errors::ErrorType::nTransitionsError);

		// Extracting the newline character from 'fin'
		fin.ignore();


		// Read transitions
		transitions = std::vector<Transition>(nTransitions);

		for (unsigned int i = 0; i < transitions.size(); ++i) {
			fin >> transitions[i];
			if (fin.bad() ||
				transitions[i].prevState < 1 || transitions[i].prevState > nStates ||
				transitions[i].nextState < 1 || transitions[i].nextState > nStates)
				throw Errors(infile, 6 + i, Errors::ErrorType::transitionsError);
			--transitions[i].nextState;
			--transitions[i].prevState;

			symbols.insert(transitions[i].symbol);
			outgoingTrans[transitions[i].prevState][transitions[i].symbol].push_back(transitions[i].nextState);
		}

		// Close the file stream
		fin.close();

		//------------------------------------------------------------------------------------------
		// DONE READING FILE
		//------------------------------------------------------------------------------------------
		/*

		// WE CAN DO THAT MORE EFFICIENTLY
		
		// Set states
		std::vector<State> states(nStates);
		for (int i = 0; i < transitions.size(); ++i) {

			if (transitions[i].nextState == transitions[i].prevState) {
				states[transitions[i].nextState].add_loop_trans(i);
				continue;
			}

			states[transitions[i].nextState].add_incoming_trans(i);
			states[transitions[i].prevState].add_outgoing_trans(i);
		}

		// Set the initial state
		states[initState].set_initial();

		// Set the final states
		for (int finalState : finalStates) states[finalState].set_final();


		// Remove dead ends and unreachable states

		// If a state will be removed we need to search again to remove
		// states that will be dead ends or unreachables after the removal
		bool searchAgain = true;
		while (searchAgain) {

			searchAgain = false;

			// For every state
			for (int i = 0; i < states.size(); ++i) {

				// If it is the initial one
				if (states[i].is_initial()) {

					// And there are not outgoing transitions
					if (!states[i].get_outgoing_trans().size()) {

						// For every transition
						for (int j = transitions.size() - 1; j >= 0; --j) {

							// If it not a loop transition from the initial state
							if (!(states[transitions[j].nextState].is_initial() &&
								transitions[j].nextState == transitions[j].prevState))

								// Erase it
								transitions.erase(transitions.begin() + j);
						}

						// Erase all the other states
						states.erase(states.begin(), states.begin() + i);
						states.erase(states.begin() + i + 1, states.end());
						break;
					}
					continue;
				}

				// If it is a final one
				if (states[i].is_final()) {

					// And there are no incoming transitions
					if (!states[i].get_incoming_trans().size()) {

						// Erase every outgoing transition from the 'states[i]' state
						for (int trans : states[i].get_outgoing_trans())
							transitions.erase(transitions.begin() + trans);

						// Remove all the outgoing transitions from state 'i' to 'state'
						for (int state : states[i].get_outgoing_trans())
							states[state].remove_incoming_trans(transitions[i].prevState);

						// Erase it
						states.erase(states.begin() + i);

						// We need to search again in case new dead ends or unreachable states appeared
						searchAgain = true;
					}
					continue;
				}

				// If it is a middle state and there are no outgoing transitions or no incoming ones
				// the state is not necessary for the automaton
				if (!states[i].get_incoming_trans().size() || !states[i].get_outgoing_trans().size()) {

					// If there are no incoming transitions
					if (!states[i].get_incoming_trans().size()) {

						// Erase every outgoing transition from the 'states[i]' state
						for (int trans : states[i].get_outgoing_trans())
							transitions.erase(transitions.begin() + trans);

						// Remove all the outgoing transitions from 'states[i]' to 'state'
						for (int state : states[i].get_outgoing_trans()) {
							std::cout << "From state: " << state << '\n';
							states[state].remove_incoming_trans(transitions[i].prevState);
						}
					}

					// If there are no outgoing trans
					if (!states[i].get_outgoing_trans().size()) {

						// Erase every incoming transition from the 'states[i]' state
						for (int trans : states[i].get_incoming_trans())
							transitions.erase(transitions.begin() + trans);

						// Remove all the incoming transitions from state 'i' to 'state'
						for (int state : states[i].get_incoming_trans()) {
							std::cout << "From state: " << state << '\n';
							states[state].remove_outgoing_trans(transitions[i].nextState);
						}
					}

					// So we can erase it
					states.erase(states.begin() + i);

					// We need to search again in case new dead ends or unreachable states appeared
					searchAgain = true;
				}

			}
		}




		/* THE MORE EFFICIENT WAY

		std::vector<int> checkStates(nStates);
		for (int i = 0; i < nStates; ++i)
			checkStates[i] = i;

		// For every state that needs checking
		for (int state : checkStates) {

			// If it is the initial one
			if (states[state].is_initial()) {

				// And there are not outgoing transitions
				if (!states[state].get_outgoing_trans().size()) {

					// TO DO: remove all the other transitions

					// Erase all the other states
					states.erase(states.begin(), states.begin() + state - 1);
					states.erase(states.begin() + state, states.end());
					break;
				}
				continue;
			}
		}

		*/
	} // of constructor FiniteAutomaton

//------------------------------------------------------------------------

	// Check if a word will be accepted from 'this' automaton
	// Inputs:
	//		std::string word: the given word
	// Outputs:
	//		bool true: 'word' was accepted
	//		bool false: 'word' was NOT accepted
	//
	bool FiniteAutomaton::check_word(std::string word) const {

		if (!finalStatesSet.size()) return false;

		if (finalStatesSet.contains(initState) && word.empty()) return true;

		// Initialize the two vectors that will be holding the current
		// and the future states respectively
		std::vector<state> currStates{ initState };
		std::vector<state> nextStates;

		// Follow all the e-transitions and add the new states to the 'currStates' vector
		for (unsigned int i = 0; i < currStates.size(); ++i)
			for (const Transition& transition : transitions)
				if (currStates[i] == transition.prevState && transition.symbol == Transition::eTrans)
					if (std::find(currStates.begin(), currStates.end(), transition.nextState) == currStates.end())
						currStates.push_back(transition.nextState);

		// For every symbol in the given 'word'
		for (unsigned int s = 0; s < word.size(); ++s) {

			// Check if the symbol is part of the language
			if (!symbols.contains(word[s])) return false;

			// Check if a dead end has been reached
			if (!currStates.size()) return false;

			// For every state check
			for (unsigned int i = 0; i < currStates.size(); ++i)

				// If any transition
				for (const Transition& transition : transitions)

					// Has the same starting state with the current one
					if (currStates[i] == transition.prevState) {

						// Check if the symbol is the same as the current symbol...
						if (word[s] == transition.symbol)

							// Check if the 'transition.nextState' is already in the 'nextStates' vector
							if (std::find(nextStates.begin(), nextStates.end(), transition.nextState) == nextStates.end())
								nextStates.push_back(transition.nextState);


						// ...or there is an e-transition and we need to push_back
						// the new states into the 'currStates' vector
						if (transition.symbol == Transition::eTrans)

							// Check if the 'transition.nextState' is already in the 'currStates' vector
							if (std::find(currStates.begin(), currStates.end(), transition.nextState) == currStates.end())
								currStates.push_back(transition.nextState);
					}

			// Insert the new states into the 'currStates' vector
			currStates = nextStates;
			nextStates.clear();
		}

		// Follow all the e-transitions and add the new states to the 'currStates' vector
		for (unsigned int i = 0; i < currStates.size(); ++i)
			for (const Transition& transition : transitions)
				if (currStates[i] == transition.prevState && transition.symbol == Transition::eTrans)
					if (std::find(currStates.begin(), currStates.end(), transition.nextState) == currStates.end())
						currStates.push_back(transition.nextState);

		// Check if any of the current states is a final one
		for (state currState : currStates)
			if(finalStatesSet.contains(currState)) return true;
		return false;

	} // of function FiniteAutomaton::check_word

//------------------------------------------------------------------------

	bool FiniteAutomaton::check_word_efficiently(std::string word) const {

		std::unordered_map<state, std::unordered_map<symbol, std::vector<state>>> outgTrans = outgoingTrans;
		
		if (!finalStates.size()) return false;

		if (finalStatesSet.contains(initState) && word.empty()) return true;

		std::vector<state> currStates{ initState };
		std::vector<state> nextStates;

		// Follow all the e-transitions and add the new states to the 'currStates' vector
		for (unsigned int i = 0; i < currStates.size(); ++i)
			for (state newState : outgTrans[currStates[i]][Transition::eTrans])
				if (std::find(currStates.begin(), currStates.end(), newState) == currStates.end())
					currStates.push_back(newState);

		
		// For every symbol in 'word'
		for (symbol currSymbol : word) {

			// If the current symbol is not part of the language
			if (!symbols.contains(currSymbol)) return false;

			// If a dead end was reached
			if (currStates.empty()) return false;

			// For every current state
			for (int i = 0; i < currStates.size(); ++i) {

				// Add to the 'nextStates' vector the states connected with 'currSymbol'
				for (state nextState : outgTrans[currStates[i]][currSymbol])
					if (std::find(nextStates.begin(), nextStates.end(), nextState) == nextStates.end())
							nextStates.push_back(nextState);

				// Add to the 'currStates' vector the states connected with e-Transition
				for (state newState : outgTrans[currStates[i]][Transition::eTrans])
					if (std::find(currStates.begin(), currStates.end(), newState) == currStates.end())
						currStates.push_back(newState);

			}
			// Insert the new states into the 'currStates' vector
			currStates = nextStates;
			nextStates.clear();
		}

		// Follow all the e-transitions and add the new states to the 'currStates' vector
		for (unsigned int i = 0; i < currStates.size(); ++i)
			for (state newState : outgTrans[currStates[i]][Transition::eTrans])
				if (std::find(currStates.begin(), currStates.end(), newState) == currStates.end())
					currStates.push_back(newState);

		// Check if any of the current states is a final one
		for (state currState : currStates)
			if (finalStatesSet.contains(currState)) return true;
		return false;
	}

//------------------------------------------------------------------------
	
	// Check if 'filename' is the same as 'this->filename'
	// Inputs:
	//		std::string filename: the input file to check
	// Outputs:
	//		bool true: The automaton in 'filename' is already defined
	//		bool false: The automaton in 'filename' is NOT already defined
	//
	bool operator==(std::string filename, FiniteAutomaton automaton) {

		std::string automatonName = automaton;

		for (char& ch : automatonName)
			if (ch == '\\' || ch == '/')
				ch = ' ';

		for (char& ch : filename)
			if (ch == '\\' || ch == '/')
				ch = ' ';

		return automatonName == filename;
	}

//------------------------------------------------------------------------

} // of namespace Automata

//------------------------------------------------------------------------
