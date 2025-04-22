#pragma once

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>

#include "utils.h"

using namespace std;

class NFA {
   public:

    /*
     * Q (states): set of States in this NFA
     * sigma (alphabet) : set of symbols recognized by this NFA
     * delta (transition function) : unordered map of each pair of cartesian
     * product of states and alphabet to set of State
     * q_0 (start state) : start state of the NFA
     * F (final state) :
     */
    NFA(set<State> Q,
        set<Symbol> sigma,
        unordered_map<Q_x_sigma, set<State>, PairHash> delta,
        State q_0,
        set<State> F);

    /*
     * Runs the current NFA on given string in given mode
     * w (input string) : string that uses the alphabet of the NFA
     * mode [normal, verbose]
     */
    bool run(string w, runMode mode);

    bool runMultiple(set<string> L, runMode mode);

    void convert2DFA();

   private:
    // internal memory of the NFA
    set<State> Q_;
    set<Symbol> sigma_;
    unordered_map<Q_x_sigma, set<State>, PairHash> delta_;
    State q_0_;
    set<State> F_;

    // external memory
    set<State> currentStates;
};