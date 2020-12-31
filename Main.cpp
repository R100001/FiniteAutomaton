
//------------------------------------------------------------------------

#include <iostream>
#include <filesystem>

//------------------------------------------------------------------------

#include "FinAut.h"
#include "AutErr.h"

//------------------------------------------------------------------------

// Define a new automaton from an input file and expand the vector 'automata'
// Inputs:
//		std::vector<Automata::FiniteAutomaton>& automata: A vector containing all the defined automata
// Outputs:
//
void define_new_automaton(std::vector<Automata::FiniteAutomaton>& automata, bool folder) {

	// Get input filename
	std::cout << "Type 'back' to go back\n";
	if (folder)
		std::cout << "Folder name: ";
	else
		std::cout << "Filename: ";
	std::string name;
	std::cin >> name;
	std::cout << '\n';
	if (name == "back") return;

	// Push the new automaton to the vector
	try {
		if (folder) {

			// For every file in the folder 'name'
			for (const auto& infile : std::filesystem::directory_iterator(name)) {

				// Check if any automaton is already defined
				bool alreadyDefined = false;
				for (const Automata::FiniteAutomaton& automaton : automata) {
					if (infile.path().string() == automaton) {
						alreadyDefined = true;
						break;
					}
				}

				// If it not defined define it
				if(!alreadyDefined)
					automata.push_back(Automata::FiniteAutomaton{ infile.path().string() });
			}
		}
		else {

			// Check if automaton is already defined
			for (const Automata::FiniteAutomaton& automaton : automata)
				if (name == automaton) return;

			// If it not defined define it
			automata.push_back(Automata::FiniteAutomaton{ name });
		}
	}
	catch (const Automata::Errors& e) {
		std::cerr << e.what() << "\n\n";
	}
	catch (const std::runtime_error& e) {
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
	std::cout << "0: Back\n";
	for (unsigned int i = 0; i < automata.size(); ++i)
		std::cout << i + 1 << ": " << (std::string)automata[i] << '\n';
	std::cout << '\n';

	// Get answer
	int automatonNum = -1;
	while (std::cin.bad() || automatonNum < 0 || automatonNum > automata.size()) {
		std::cout << ">> ";
		std::cin >> automatonNum;
		std::cin.clear();
	}
	std::cout << '\n';
	if (!automatonNum) return;

	// Check words
	while (true) {

		// Get a new word
		std::cout << "Enter a word: ";
		std::string word;
		std::cin >> word;

		// Check the word and show message
		if (automata[STATICCASTAUTOMATON(automatonNum) - 1].check_word_efficiently(word))
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
		std::cout << "3: Exit\n\n";
		std::cout << ">> ";

		// Get input
		std::string input;
		std::cin >> input;
		std::cout << '\n';

		if (input == "1") {

			std::cout << "0: Back\n";
			std::cout << "1: Insert one automaton\n";
			std::cout << "2: Insert automata from a folder\n\n";

			int answer = -1;
			while (std::cin.bad() || answer < 0 || answer > 2) {
				std::cout << ">> ";
				std::cin >> answer;
				std::cin.clear(); 
			}
			std::cout << '\n';

			if (!answer) continue;

			define_new_automaton(automata, answer - 1);
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
