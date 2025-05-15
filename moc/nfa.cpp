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

// void NFA::convert2DFA() {
//     set<State> tempCurrStates;
// }

bool NFA::run(string w, runMode mode) {
    if (mode == runMode::VERBOSE) {
        cout << "Starting states: ";
        for (const auto& state : currentStates) {
            cout << state << " ";
        }
        cout << endl;
    }

    for (Symbol c : w) {
        if (mode == runMode::VERBOSE) {
            cout << "Input: " << c << endl;
        }

        set<State> tempCurrStates;
        for (State q : currentStates) {
            set<State> res = delta_[{q, c}];
            for (State q_p : res) {
                tempCurrStates.insert(q_p);
            }
        }
        currentStates = tempCurrStates;

        if (mode == runMode::VERBOSE) {
            cout << "State Transitions";
            for (const auto& state : currentStates) {
                cout << state << " ";
            }
            cout << endl;
        }
    }

    bool accepted = false;
    for (State q : currentStates) {
        if (F_.contains(q)) {
            accepted = true;
            break;
        }
    }

    if (mode == runMode::VERBOSE) {
        cout << "Final states: ";
        for (const auto& state : currentStates) {
            cout << state << " ";
        }
        cout << endl;
        cout << "Result: " << (accepted ? "accepted" : "rejected") << endl;
    }

    return accepted;
}

bool NFA::runMultiple(set<string> L, runMode mode) {
    bool allAccepted = true;
    size_t total = L.size();
    size_t accepted = 0;

    for (const string& w : L) {
        if (mode == runMode::VERBOSE) {
            cout << "\nProcessing string: " << w << endl;
            cout << "------------------------" << endl;
        }

        bool result = run(w, mode);
        if (result) {
            accepted++;
        } else {
            allAccepted = false;
        }
        reset();
    }

    if (mode == runMode::VERBOSE) {
        cout << "\nSummary:" << endl;
        cout << "--------" << endl;
        cout << "Total strings: " << total << endl;
        cout << "Accepted: " << accepted << endl;
        cout << "Rejected: " << (total - accepted) << endl;
    }

    return allAccepted;
}

void NFA::reset() {
    currentStates = {q_0_};
}
