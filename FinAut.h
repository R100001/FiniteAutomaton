
//------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

//------------------------------------------------------------------------

namespace Automata {

//------------------------------------------------------------------------

	// An implementation of a deterministic or non-deterministic
	// finite automaton
	//
	class FiniteAutomaton {

	public:
		// Define an automaton reading its states and transitions
		FiniteAutomaton(std::fstream fin);

	private:

		static const char eTrans = '@';

		struct transition {

			// This constructor should never be used
			// It exists to avoid build error
			// C2512: no appropriate default constructor available
			transition()
				:prevState{ 0 }, symbol{ eTrans }, nextState{ 0 }{}

			// Create a transition from one state to the next
			transition(int prev, char sym, int next)
				:prevState{ prev }, symbol{ sym }, nextState{ next }{}

			int prevState;
			int nextState;
			char symbol;

		}; // of struct transition

		int nStates;
		int initState;
		std::vector<int> finalStates;
		std::vector<transition> transitions;

		int currState;

	}; // of class FiniteAutomaton

//------------------------------------------------------------------------

} // of namespace Automata