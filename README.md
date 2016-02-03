# DFA-cpp
Created a simple Deterministic Finite Automata using C++.

Using this utility, you can create a simple DFA checker that will read in the DFA specification through stdin and test the string provided as a command-line argument against the DFA. 

### Usage
Build the source simply by using 
```make dfa```

Run the file using
```./dfa teststring < template```

Create a template file to store information on your dfa akin to the following.
```
start_state final_state	  a     b
q0		                  q1	q3				
q1		                  q2	q4
q2		                  q9	q5
q3		                  q4	q6
q4		                  q5	q7
q5		                  q9	q8
q6		                  q7	q6
q7		                  q8	q7
q8		                  q9	q8
q9		                  q9	q9
```
The provided template file will only return true if your string has exactly two `a`'s and at least two `b`'s. 

Error checking hasn't been fully implemented, so your file needs to match this format exactly. Currently only supports one start and final state, although support for more final states may come later. Supports as many language characters as you wish, must only be one character long though. Supports as many states as needed, but each character must map to a state. 
