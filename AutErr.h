//------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------

#include <string>

//------------------------------------------------------------------------

namespace Automata {

//------------------------------------------------------------------------

	// Handle the errors that may occur when using the namespace 'Automata'
	//
	class Errors {
	public:

		enum class ErrorType {
			nStatesError, initStateError, nFinalStatesError,
			finalStatesError, nTransitionsError, transitionsError,
			providedFinalStatesError, fileDoesNotExist
		};

		// Create an error object giving the line that the error occured
		Errors(int line, ErrorType error);

		// Get the error
		std::string what();

	private:
		// Define the errors by the line that they occured
		int eLine;
		ErrorType eType;

	}; // of class errors
}