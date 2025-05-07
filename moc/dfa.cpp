#include <iostream>
#include <utility>

#include "dfa.h"

DFA::DFA(set<State> Q,
         set<Symbol> sigma,
         unordered_map<Q_x_sigma, State, PairHash> delta,
         State q_0,
         set<State> F)
    : Q_(Q), sigma_(sigma), delta_(delta), q_0_(q_0), F_(F) {

    if (!Q.contains(q_0))
        throw runtime_error("Invalid start state");
    for (State f : F) {
        if (!Q.contains(f))
            throw runtime_error("Invalid final states");
    }

    for (auto it : delta) {
        if (!Q.contains(it.first.first) || !sigma.contains(it.first.second) ||
            !Q.contains(it.second))
            throw runtime_error("Invalid Transition function");
    }
    currentState = q_0;
};

// ### TO DO ### : parse jff file to get DFA info and create a DFA obj
DFA::DFA(string jffFilePath) {}

bool DFA::run(string w, runMode mode) {
    for (Symbol c : w) {
        if (!sigma_.contains(c))
            throw runtime_error(
                "This automaton doesn't accpet the given string");

        pair<string, char> p(currentState, c);
        DFA::currentState = delta_[p];
        if (mode == VERBOSE) {
            cout << currentState << endl;
        }
    }

    return F_.contains(currentState);
};

bool DFA::runMultiple(set<string> L, runMode mode) {
    bool flag = true;

    for (string w : L) {
        bool res = run(w, NORMAL);
        if (!res)
            flag = false;
        reset();
    }

    return flag;
}

void DFA::reset() {
    currentState = q_0_;
}