#include "dfa.h"

#include <iostream>
#include <utility>

// ## TO DO ## : add sanity checks to see if it is a valid DFA
DFA::DFA(set<State> Q,
         set<Symbol> sigma,
         unordered_map<Q_x_sigma, State, PairHash> delta,
         State q_0,
         State F)
    : Q_(Q), sigma_(sigma), delta_(delta), q_0_(q_0), F_(F) {
     currentState = q_0;
    };

bool DFA::run(string w, runMode mode) {
    for (char c : w) {
        pair<string, char> p(currentState, c);
        DFA::currentState = delta_[p];
        if (mode == VERBOSE) {
            cout << currentState << endl;
        }
    }

    return (currentState == F_);
};

bool DFA::runMultiple(set<string> L, runMode mode) {
    bool flag = true;

    for (string w : L) {
        bool res = run(w, NORMAL);
        if (!res)
            flag = false;
    }

    return flag;
}