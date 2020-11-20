
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
		FiniteAutomaton(std::string infile);

		// Check if a word will be accepted by 'this' automaton
		bool check_word(std::string word);
		
		// Get the name of the input file for 'this' automaton
		operator std::string() { return filename; }

	private:

		struct Transition {

			// This constructor should never be used
			// It exists to avoid build error
			// C2512: no appropriate default constructor available
			Transition()
				:prevState{ 0 }, symbol{ eTrans }, nextState{ 0 }{}

			// Create a transition from one state to the next
			Transition(int prev, char sym, int next)
				:prevState{ prev }, symbol{ sym }, nextState{ next }{}

			int prevState;
			int nextState;
			char symbol;

		}; // of struct transition


		std::string filename;

		static const char eTrans = '@';

		int nStates;
		int initState;
		std::vector<int> finalStates;
		std::vector<Transition> transitions;

	}; // of class FiniteAutomaton

//------------------------------------------------------------------------

} // of namespace Automata