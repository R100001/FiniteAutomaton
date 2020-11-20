
//------------------------------------------------------------------------

#include <iostream>

//------------------------------------------------------------------------

#include "FinAut.h"

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

		if (input == "1") {  // Create new automaton

			// Get input filename
			std::cout << "Filename: ";
			std::string infile;
			std::cin >> infile;
			std::cout << '\n';

			// Push the new automaton to the vector
			automata.push_back(Automata::FiniteAutomaton{ infile });
		}
		else if (input == "2") { // Use an automaton

			// Show appropriate message
			std::cout << "Choose an automaton to use (1-" << automata.size() << "):\n";
			for (int i = 0; i < automata.size(); ++i)
				std::cout << i + 1 << ": " << (std::string)automata[i] << '\n';
			std::cout << '\n';

			// Get answer
			int automatonNum;
			std::cin >> automatonNum;
			std::cout << '\n';

			// Check words
			while (true) {

				// Get a new word
				std::cout << "Enter a word: ";
				std::string word;
				std::cin >> word;

				// Check the word and show message
				if (automata[automatonNum-1].check_word(word))
					std::cout << "The word '" << word << "' was accepted!\n\n";
				else
					std::cout << "The word '" << word << "' was NOT accepted!\n\n";

				// Ask user if he wants to check another word
				std::cout << "Do you want to enter another word? (yes,no): ";

				bool anotherWord = false;
				while (true) {

					std::string answer;
					std::cin >> answer;

					if (answer == "yes") {
						anotherWord = true;
						break;
					}
					else if (answer == "no") break;

				}
				// If answer == 'no'
				if (!anotherWord) break;

			} // while (true) (check words)

		} else if (input == "3") break;

	} // while (true) (program loop)

}
catch (std::runtime_error e) {
	std::cerr << e.what() << '\n';
}
catch (...) {
	std::cerr << "Default exception...\n";
}

//------------------------------------------------------------------------
