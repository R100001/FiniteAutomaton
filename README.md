# FiniteAutomaton
Code to read deterministic or non-deterministic automata and check if a word can be accepted by them


An automaton can be defined with a file structured like it will be shown below:

n           // 1 <= n < oo              "n is the number of states the automaton has"
x           // 1 <= x <= n              "x is the initial state of the automaton"
y1,y2...yn  // 1 <= y1,y2...yn <= n     "y1, y2...yn is the final states of the automaton"
m           // 1 <= m < oo              "m is the number of transitions between states in the automaton"
yi w yj     // 1 <= i,j <= n            "yi, yj is the connected states"
.                                       "w is a symbol from the language that the automaton understands"
.                                       "the given transitions must be equal to m"

To be continued...
