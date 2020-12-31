
//------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

//------------------------------------------------------------------------

#include "Transition.h"
#include "AutErr.h"
//#include "State.h"

//------------------------------------------------------------------------

#define STATICCASTAUTOMATON static_cast<std::vector<Automata::FiniteAutomaton, std::allocator<Automata::FiniteAutomaton>>::size_type>

//------------------------------------------------------------------------

typedef int state;
typedef char symbol;

//------------------------------------------------------------------------

namespace Automata {

//------------------------------------------------------------------------

	// An implementation of deterministic or non-deterministic
	// finite automata
	//
	class FiniteAutomaton {

	public:
		// Define an automaton by reading its states and transitions
		FiniteAutomaton(std::string infile);

		// Check if a word will be accepted by 'this' automaton
		bool check_word(std::string word) const;

		// Check if a word will be accepted by 'this' automaton more efficiently
		bool check_word_efficiently(std::string word) const;
		
		// Get the name of the input file for 'this' automaton
		operator std::string() const { return filename; }

	private:

		std::string filename;

		int nStates;
		int initState;

		std::vector<state> finalStates;
		std::unordered_set<state> finalStatesSet;

		std::vector<Transition> transitions;
		std::unordered_set<symbol> symbols;
		std::unordered_map<state, std::unordered_map<symbol, std::vector<state>>> outgoingTrans;

	}; // of class FiniteAutomaton

//------------------------------------------------------------------------

	// Check if an automaton is already defined
	// by checking the name of the input file
	bool operator==(std::string filename, FiniteAutomaton automaton);

//------------------------------------------------------------------------

} // of namespace Automata

//------------------------------------------------------------------------
