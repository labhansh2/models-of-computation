#include <iostream>
#include <utility>

#include "nfa.h"

// ## TO DO ## : add sanity checks to see if it is a valid DFA
NFA::NFA(set<State> Q,
    set<Symbol> sigma,
    unordered_map<Q_x_sigma, set<State>, PairHash> delta,
    State q_0,
    State F)
: Q_(Q), sigma_(sigma), delta_(delta), q_0_(q_0), F_(F) {
currentState = q_0;
};

// example nfa
// {
//     {{"q0", '0'}, {"q0", "q1"}},
//     {{"q0", '1'}, {"q0"}},
//     {{"q1", '0'}, {"q1"}},
//     {{"q1", '1'}, {"q1", "q2"}},
//     {{"q2", '0'}, {"q1"}},
//     {{"q2", '1'}, {"q0", "q2"}}
// };
void NFA::_convert2DFA(){

}

bool _runHelper(string w){

}

bool NFA::run(string w, bool mode){



}

