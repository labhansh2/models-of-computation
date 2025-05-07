#pragma once

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

#include "utils.h"

using namespace std;

class DFA {
   public:
    /*
     * Q (states): set of States in this DFA
     * sigma (alphabet) : set of symbols recognized by this DFA
     * delta (transition function) : unordered map of each element of cartesian
     * product of states and alphabet to a State 
     * q_0 (start state) : start state of the DFA 
     * F (final states) : accepting states of the DFA
     */
    DFA(set<State> Q,
        set<Symbol> sigma,
        unordered_map<Q_x_sigma, State, PairHash> delta,
        State q_0,
        set<State> F);

    /*
     * Takes in a jff file to create a DFA object
     */
    // DFA(string jffFilePath);
    
    /*
     * Takes DFA as an encoded string to initialize
     * ### TO DO ### : Think about the most efficient way of encoding
     */
    DFA(string encodedDFA);

    /*
     * Runs the DFA on a single input symbol
     * Returns the state DFA is in after the input s
     */
    State input(Symbol s);

    /*
     * Runs the current DFA on given string in given mode
     * w (input string) : string that uses the alphabet of the DFA
     * mode : runMode
     *     NORMAL : doesn't print the path
     *     VERBOSE : printst the path
     */
    bool run(string w, runMode mode);

    /*
     * Runs the current DFA on given sets of string in given mode
     * L : sets of string that uses the alphabet of the DFA
     * mode : runMode
     *     NORMAL : doesn't print the path
     *     VERBOSE : printst the path
     */
    bool runMultiple(set<string> L, runMode mode);

    /*
     * Converts the DFA into a JFF format and saves in
     * jff-files dir to view in JFLAP
     */
    void convert2JFF();

    /*
     * Resets the currentState to the start state
     */
    void reset();

   private:
    // internal memory of the machine
    set<State> Q_;
    set<Symbol> sigma_;
    unordered_map<Q_x_sigma, State, PairHash> delta_;
    State q_0_;
    set<State> F_;

    // external memory
    State currentState;
};