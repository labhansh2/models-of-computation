#include <iostream>

#include "dfa.h"

using namespace std;

int main() {

    // testing 

    
    using State = string;
    using Symbol = char;
    using Q_x_sigma = pair<State, Symbol>;

    set<string> states = {"q0", "q1", "q2"};
    set<char> alphabet = {'0', '1'};

    // Transition function
    unordered_map<Q_x_sigma, State, PairHash> transitions = {
        {{"q0", '0'}, "q1"}, {{"q0", '1'}, "q0"}, {{"q1", '0'}, "q1"},
        {{"q1", '1'}, "q2"}, {{"q2", '0'}, "q1"}, {{"q2", '1'}, "q0"}};

    State start_state = "q0";
    State final_state = "q2";

    DFA dfa(states, alphabet, transitions, start_state, final_state);
    
    cout << dfa.run("000101", NORMAL) << endl;
    cout << dfa.run("001", NORMAL) << endl ;
    cout << dfa.run("1101", NORMAL) << endl;
    cout << dfa.run("000101", NORMAL) << endl;

    cout << dfa.run("0", NORMAL) << endl;
}