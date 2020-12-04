
//------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

//------------------------------------------------------------------------

#include "Transition.h"
#include "AutErr.h"

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
		bool check_word(std::string word) const;

		// TO DO
		// Check if a word will be accepted by 'this' automaton more efficiently
		// bool check_word_efficiently(std::string word) const;
		
		// Get the name of the input file for 'this' automaton
		operator std::string() const { return filename; }

		// Check if an automaton is already defined
		bool operator==(std::string filename) const;

	private:

		std::string filename;

		int nStates;
		int initState;
		std::vector<int> finalStates;
		std::vector<Transition> transitions;

	}; // of class FiniteAutomaton

//------------------------------------------------------------------------

} // of namespace Automata

//------------------------------------------------------------------------
