#include <fstream>
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

    for (const auto& state : Q) {
        for (const auto& symbol : sigma) {
            auto transition = make_pair(state, symbol);
            if (delta.find(transition) == delta.end()) {
                throw runtime_error("Missing transition for state " + state +
                                    " and symbol " + symbol);
            }
        }
    }

    currentState = q_0;
};

DFA::DFA(string jffFilePath) {
    try {
        auto components = parseJFFFile(jffFilePath);
        Q_ = components.Q;
        sigma_ = components.sigma;
        delta_ = components.delta;
        q_0_ = components.q_0;
        F_ = components.F;
        currentState = q_0_;
    } catch (const exception& e) {
        throw runtime_error("Failed to create DFA from JFF file: " +
                            string(e.what()));
    }
}

State DFA::input(Symbol s) {
    if (!sigma_.contains(s)) {
        throw runtime_error("Symbol '" + string(1, s) + "' not in alphabet");
    }

    auto transition = make_pair(currentState, s);
    if (delta_.find(transition) == delta_.end()) {
        throw runtime_error("No transition defined for state " + currentState +
                            " and symbol " + s);
    }

    currentState = delta_[transition];
    return currentState;
}

bool DFA::run(string w, runMode mode) {
    if (mode == runMode::VERBOSE) {
        cout << "Starting state: " << currentState << endl;
    }

    for (Symbol c : w) {
        try {
            State nextState = input(c);
            if (mode == runMode::VERBOSE) {
                cout << "Input: " << c << " -> State: " << nextState << endl;
            }
        } catch (const exception& e) {
            throw runtime_error("Error processing input '" + string(1, c) +
                                "': " + e.what());
        }
    }

    bool accepted = F_.contains(currentState);
    if (mode == runMode::VERBOSE) {
        cout << "Final state: " << currentState << " ("
             << (accepted ? "accepted" : "rejected") << ")" << endl;
    }

    return accepted;
};

bool DFA::runMultiple(set<string> L, runMode mode) {
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

void DFA::reset() {
    currentState = q_0_;
}

// ### TO DO ### : Turn this into a utility function for all automaton and use it that way
void DFA::convert2JFF() {
    ofstream jffFile("output.jff");
    if (!jffFile.is_open()) {
        throw runtime_error("Failed to create JFF file");
    }

    // Write XML header and structure
    jffFile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
            << endl;
    jffFile << "<structure>" << endl;
    jffFile << "\t<type>fa</type>" << endl;
    jffFile << "\t<automaton>" << endl;

    // Write states
    jffFile << "\t\t<!--The list of states.-->" << endl;
    int stateId = 0;
    unordered_map<State, int> stateIds;

    for (const auto& state : Q_) {
        stateIds[state] = stateId;
        jffFile << "\t\t<state id=\"" << stateId << "\" name=\"" << state
                << "\">" << endl;
        // Add arbitrary but valid coordinates for visualization
        jffFile << "\t\t\t<x>" << (100 + stateId * 100) << "</x>" << endl;
        jffFile << "\t\t\t<y>" << (100 + (stateId % 2) * 50) << "</y>" << endl;

        if (state == q_0_) {
            jffFile << "\t\t\t<initial/>" << endl;
        }
        if (F_.contains(state)) {
            jffFile << "\t\t\t<final/>" << endl;
        }
        jffFile << "\t\t</state>" << endl;
        stateId++;
    }

    // Write transitions
    jffFile << "\t\t<!--The list of transitions.-->" << endl;
    for (const auto& [transition, toState] : delta_) {
        const auto& [fromState, symbol] = transition;
        jffFile << "\t\t<transition>" << endl;
        jffFile << "\t\t\t<from>" << stateIds[fromState] << "</from>" << endl;
        jffFile << "\t\t\t<to>" << stateIds[toState] << "</to>" << endl;
        jffFile << "\t\t\t<read>" << symbol << "</read>" << endl;
        jffFile << "\t\t</transition>" << endl;
    }

    // Close structure
    jffFile << "\t</automaton>" << endl;
    jffFile << "</structure>" << endl;

    jffFile.close();
}