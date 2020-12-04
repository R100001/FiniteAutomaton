
//------------------------------------------------------------------------

#include <iostream>

//------------------------------------------------------------------------

#include "FinAut.h"
#include "AutErr.h"

//------------------------------------------------------------------------

// Define a new automaton from an input file and expand the vector 'automata'
// Inputs:
//		std::vector<Automata::FiniteAutomaton>& automata: A vector containing all the defined automata
// Outputs:
//
void define_new_automaton(std::vector<Automata::FiniteAutomaton>& automata) {

	// Get input filename
	std::cout << "Filename: ";
	std::string infile;
	std::cin >> infile;
	std::cout << '\n';

	// Push the new automaton to the vector
	try {
		automata.push_back(Automata::FiniteAutomaton{ infile });
	}
	catch (Automata::Errors e) {
		std::cerr << e.what() << "\n\n";
	}

}

//------------------------------------------------------------------------

// Check words in an already defined automaton
// Inputs:
//		const std::vector<Automata::FiniteAutomaton>& automata: Defined automata
// Outputs:
//
void use_an_automaton(const std::vector<Automata::FiniteAutomaton>& automata) {

	// Check if any automaton is defined
	if (!automata.size()) {
		std::cout << "There is no automaton to use. You need to define one!\n\n";
		return;
	}

	// Show appropriate message
	std::cout << "Choose an automaton to use (1-" << automata.size() << "):\n";
	for (unsigned int i = 0; i < automata.size(); ++i)
		std::cout << i + 1 << ": " << (std::string)automata[i] << '\n';
	std::cout << '\n';

	// Get answer
	int automatonNum = 0;
	while (automatonNum < 1 || automatonNum > automata.size()) {
		std::cin >> automatonNum;
		std::cin.clear();
	}
	std::cout << '\n';

	// Check words
	while (true) {

		// Get a new word
		std::cout << "Enter a word: ";
		std::string word;
		std::cin >> word;

		// Check the word and show message
		if (automata[automatonNum - 1].check_word(word))
			std::cout << "The word '" << word << "' was accepted!\n\n";
		else
			std::cout << "The word '" << word << "' was NOT accepted!\n\n";

		// More words?
		std::cout << "Do you want to enter another word? (yes,no): ";

		// Get answer
		std::string answer;

		while (answer != "yes" && answer != "no") {
			std::cin >> answer;
			std::cin.clear();
		}

		std::cout << '\n';

		if (answer == "no") break;

	} // while (true) (check words)

}

//------------------------------------------------------------------------

int main()
try {

	std::vector<Automata::FiniteAutomaton> automata;

	// Program loop
	while (true) {

		// Show appropriate message 
		std::cout << "What do you want to do?\n";
		std::cout << "1: Insert new automaton\n";
		std::cout << "2: Use an automaton\n";
		std::cout << "3: Exit\n";
		std::cout << ">> ";

		// Get input
		std::string input;
		std::cin >> input;
		std::cout << '\n';

		if (input == "1") {

			define_new_automaton(automata);
		}
		else if (input == "2") {

			use_an_automaton(automata);
		} 
		else if (input == "3") break;

	} // while (true) (program loop)

}
catch (const std::exception& e) {
	std::cerr << e.what() << '\n';
}
catch (...) {
	std::cerr << "Default exception...\n";
}

//------------------------------------------------------------------------
