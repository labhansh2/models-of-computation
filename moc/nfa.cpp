#include <iostream>
#include <utility>
#include <set>

#include "nfa.h"

using namespace std;

// ## TO DO ## : add sanity checks to see if it is a valid DFA
NFA::NFA(set<State> Q,
         set<Symbol> sigma,
         unordered_map<Q_x_sigma, set<State>, PairHash> delta,
         State q_0,
         State F)
    : Q_(Q), sigma_(sigma), delta_(delta), q_0_(q_0), F_(F) {
    // ### TO DO ### : Add states that are reached by an empty string
    currentState = {q_0_};
};

void NFA::convert2DFA() {
    set<State> tempCurrStates;
}

bool NFA::run(string w, runMode mode) {
    for (Symbol c : w) {
        set<State> tempCurrStates;
        for (State q : currentState) {
            set<State> res = delta_[{q, c}];
            for (State q_p : res) {
                tempCurrStates.insert(q_p);
            }
        }
        currentState = tempCurrStates;
    }

    return currentState.contains(F_);
}

bool NFA::runMultiple(set<string> L, runMode mode) {
    bool flag = true;
    for (string w : L) {
        bool res = run(w, mode);
        if (!res) flag = false;
    }
    return flag;
}
