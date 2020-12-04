
//------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------

#include <fstream>
#include <sstream>
#include <iostream>

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

		friend std::fstream& operator>>(std::fstream& fin, Automata::Transition& transition) {
			std::string line;

			std::getline(fin, line);
			std::stringstream lineSs(line);

			lineSs >> transition.prevState;
			lineSs >> transition.symbol;
			lineSs >> transition.nextState;

			if (lineSs.bad()) fin.setstate(fin.badbit);

			return fin;
		}

	}; // of struct transition

//------------------------------------------------------------------------

} // of namespace Automatas

//------------------------------------------------------------------------
