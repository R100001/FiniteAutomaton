
//------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------

#include <vector>
#include <iostream>

//------------------------------------------------------------------------

namespace Automata {

//------------------------------------------------------------------------

	class State {
	public:

		State() :initialS{ false }, finalS{ false } {};

		void add_outgoing_trans(int state) { outgoingTrans.push_back(state); }

		void add_incoming_trans(int state) { incomingTrans.push_back(state); }

		void add_loop_trans(int state) { incomingTrans.push_back(state); }

		void remove_outgoing_trans(int state) { 
			std::cout << "Removing outgoing state: " << state + 1 << '\n';
			for (int i = 0; i < outgoingTrans.size(); ++i)
				if (outgoingTrans[i] == state)
					outgoingTrans.erase(outgoingTrans.begin() + i);
		}

		void remove_incoming_trans(int state) {
			std::cout << "Removing incoming state: " << state + 1 << '\n';
			for (int i = 0; i < incomingTrans.size(); ++i)
				if (incomingTrans[i] == state)
					incomingTrans.erase(incomingTrans.begin() + i);
		}

		void set_initial() { initialS = true; }

		void set_final() { finalS = true; }


		std::vector<int> get_outgoing_trans() { return outgoingTrans; }

		std::vector<int> get_incoming_trans() { return incomingTrans; }

		std::vector<int> get_loop_trans() { return incomingTrans; }

		bool is_initial() { return initialS; }

		bool is_final() { return finalS; }

	private:

		std::vector<int> outgoingTrans;

		std::vector<int> incomingTrans;

		std::vector<int> loopTrans;

		bool initialS;

		bool finalS;

	}; // of class State

//------------------------------------------------------------------------

} // of namespace Automata

//------------------------------------------------------------------------
