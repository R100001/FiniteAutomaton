
//------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------

#include <fstream>
#include <sstream>
#include <ostream>

namespace Automata {

//------------------------------------------------------------------------

	struct Transition {

		// Default constructor
		// This constructor should never be used
		Transition()
			:prevState{ 0 }, symbol{ eTrans }, symbols{ "" }, nextState{ 0 }{}

		// Create a transition from one state to the next using a single symbol
		Transition(int prev, char sym, int next)
			:prevState{ prev }, symbol{ sym }, symbols{ "" }, nextState{ next }{}

		// Create a transition from one state to the next using multiple symbols
		Transition(int prev, std::string syms, int next)
			:prevState{ prev }, symbol{ eTrans }, symbols{ syms }, nextState{ next }{}

		int prevState;
		int nextState;
		char symbol;
		std::string symbols;

		static const char eTrans = '@';

	}; // of struct transition

//------------------------------------------------------------------------

	std::fstream& operator>>(std::fstream& fin, Automata::Transition& transition);

	std::ostream& operator<<(std::ostream& cout, Transition trans);

//------------------------------------------------------------------------

} // of namespace Automatas

//------------------------------------------------------------------------
