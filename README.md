# DFA_minimizer
This project will used to minimize DFA

# DFA 
In DFA, for each input symbol, one can determine the state to which the machine will move. Hence, it is called Deterministic Automaton. As it has a finite number of states, the machine is called Deterministic Finite Machine.
A DFA has five-tuple:
	T = (Q, Σ, δ, q0, F)
	Q	->A finite set of states
	Σ	->A finite input alphabet
	q0	->The initial state, q0 is in Q
	F	-> A set of final states, which is a subset of Q
	δ	-> A transition function, which is a total function from Q x Σ to Q
  
		 δ: (Q x Σ) –> Q	   δ is defined for any q in Q and s in Σ, and 
		 δ(q,s) = q’	   is equal to some state q’ in Q, could be q’=q

	Intuitively, δ(q,s) is the state entered by M after reading symbol s while in state q.

                                        Method: Myhill-Nerode Theorem
Algorithm
Step 1:  Make a table taking all states of N*N where N is number of states

Step 2: Mark all pairs which are one final and other non-final

Step 3: Repeat step 2 until we cannot mark anymore states ALso If there is any unmarked pair, mark it if the pair {δ (qi, A), δ (qi, A)} is marked for some input alphabet.

Step 4: Take all unmarked pair and combine them to single state
