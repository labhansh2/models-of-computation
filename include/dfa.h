#pragma once

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

struct PairHash {
    size_t operator()(const pair<string, char>& p) const noexcept {
        return hash<string>{}(p.first) ^
               (hash<char>{}(p.second) << 1);
    }
};

enum runMode {
    NORMAL, VERBOSE
};

class DFA {
   public:
    using State = string;
    using Symbol = char;
    using Q_x_sigma = pair<State, Symbol>;

    /*
     * Q (states): set of States in this DFA
     * sigma (alphabet) : set of symbols recognized by this DFA
     * delta (transition function) : unordered map of each pair of cartesian
     * product of states and alphabet to a State q_0 (start state) : start state
     * of the DFA F (final state) :
     */
    DFA(set<State> Q,
        set<Symbol> sigma,
        unordered_map<Q_x_sigma, State, PairHash> delta,
        State q_0,
        State F);

    /*
     * Runs the current DFA on given string in given mode
     * w (input string) : string that uses the alphabet of the DFA
     * mode : runMode
     */
    bool run(string w, runMode mode);

    /*
     * Runs the current DFA on given sets of string in given mode
     * L : sets of string that uses the alphabet of the DFA
     * mode : runMode
     *     nomal mode: doesn't print the path
     *     verbose mode: printst the path
     */
    bool runMultiple(set<string> L, runMode mode);

   private:
    // internal memory of the machine
    set<State> Q_;
    set<Symbol> sigma_;
    unordered_map<Q_x_sigma, State, PairHash> delta_;
    State q_0_;
    State F_;

    // external memory
    State currentState;
};