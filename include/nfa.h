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

class NFA {
   public:
    using State = string;
    using Symbol = char;
    using Q_x_sigma = pair<State, Symbol>;

    /*
     * Q (states): set of States in this DFA
     * sigma (alphabet) : set of symbols recognized by this DFA
     * delta (transition function) : unordered map of each pair of cartesian
     * product of states and alphabet to set of State
     * q_0 (start state) : start state of the DFA
     * F (final state) :
     */
    NFA(set<State> Q,
        set<Symbol> sigma,
        unordered_map<Q_x_sigma, set<State>, PairHash> delta,
        State q_0,
        State F);

    /*
     * Runs the current DFA on given string in given mode
     * w (input string) : string that uses the alphabet of the DFA
     * mode [normal, verbose]
     */
    bool run(string w, bool mode);

    bool runMultiple(set<string> L, bool mode);

   private:
    // internal memory of the DFA
    set<State> Q_;
    set<Symbol> sigma_;
    unordered_map<Q_x_sigma, set<State>, PairHash> delta_;
    State q_0_;
    State F_;

    // external memory
    State currentState;

    void _convert2DFA();
};