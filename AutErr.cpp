
//------------------------------------------------------------------------

#include "AutErr.h"

//------------------------------------------------------------------------

namespace Automata {

//------------------------------------------------------------------------

	// Create an error object giving the line that the error occured
	// and the type of the error
	// Inputs:
	//		int line: The number of the line that the error occured
	//		ErrorType error: The type of the error
	// Outputs:
	//
	Errors::Errors(std::string infile, int line, ErrorType error) {
		filename = infile;
		eLine = line;
		eType = error;
	}

//------------------------------------------------------------------------

	// Return an appropriate error message
	// Inputs:
	// Outputs:
	//		std::string msg: A string containing the error description
	//
	std::string Errors::what() const {

		if (eType == ErrorType::fileDoesNotExist)
			return "File " + filename + " does not exist!";

		std::string msg = "Error in file: " + filename + "\nLine: " + std::to_string(eLine) + '\n';

		if (eType == ErrorType::nStatesError)
			msg += "Please use a positive integer";

		else if (eType == ErrorType::initStateError)
			msg += "Please use an integer in range [1,nStates]";

		else if (eType == ErrorType::nFinalStatesError)
			msg += "Please use an integer in range [0,nStates]";

		else if (eType == ErrorType::finalStatesError)
			msg += "Please use an integer in range [1,nStates]";

		else if (eType == ErrorType::providedFinalStatesError)
			msg += "Please provide as many final states as were declared in the previous line";

		else if (eType == ErrorType::nTransitionsError)
			msg += "Please use a non-negative integer";

		else if (eType == ErrorType::transitionsError)
			msg += "Please use integers in range [1,nStates] and an appropriate symbol";
		
		return msg;

	} // of function Errors::what()

//------------------------------------------------------------------------

} // of namespace Automata

//------------------------------------------------------------------------
