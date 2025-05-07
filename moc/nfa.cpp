#include <iostream>
#include <set>
#include <utility>

#include "nfa.h"

using namespace std;

NFA::NFA(set<State> Q,
         set<Symbol> sigma,
         unordered_map<Q_x_sigma, set<State>, PairHash> delta,
         State q_0,
         set<State> F)
    : Q_(Q), sigma_(sigma), delta_(delta), q_0_(q_0), F_(F) {
    // ### TO DO ### : Add states that are reached by an empty string : do we
    // even need to do this??

    if (!Q.contains(q_0))
        throw runtime_error("Invalid start state");
    for (State f : F) {
        if (!Q.contains(f))
            throw runtime_error("Invalid final states");
    }

    for (auto it : delta) {
        if (!Q.contains(it.first.first) || !sigma.contains(it.first.second))
            throw runtime_error("Invalid Transition function");

        for (State q : it.second) {
            if (!Q.contains(q))
                throw runtime_error("Invalid Transition function");
        }
    }

    currentStates = {q_0_};
};

void NFA::convert2DFA() {
    set<State> tempCurrStates;
}

bool NFA::run(string w, runMode mode) {
    // Can you optimize this?
    for (Symbol c : w) {
        set<State> tempCurrStates;
        for (State q : currentStates) {
            set<State> res = delta_[{q, c}];
            for (State q_p : res) {
                tempCurrStates.insert(q_p);
            }
        }
        currentStates = tempCurrStates;
    }

    for (State q : currentStates) {
        if (F_.contains(q))
            return true;
    }

    return false;
}

bool NFA::runMultiple(set<string> L, runMode mode) {
    bool flag = true;
    for (string w : L) {
        bool res = run(w, mode);
        if (!res)
            flag = false;

        reset();
    }
    return flag;
}

void NFA::reset() {
    currentStates = {q_0_};
}
