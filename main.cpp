#include <iostream>
#include <vector>

#include "dfa.h"
#include "nfa.h"

using namespace std;

void testDFA() {
    cout << "\nTesting DFA from JFF file:" << endl;
    cout << "------------------------" << endl;

    try {
        // Create a DFA from the example JFF file
        DFA dfa("example.jff");

        // Test some strings - This DFA accepts strings that contain "01"
        // pattern anywhere
        cout << "Testing DFA that accepts strings containing '01'" << endl;

        set<string> acceptTests = {"01",  "0001", "1101",
                                   "010", "0101", "11011"};

        set<string> rejectTests = {"0", "1", "00", "11", "000", "111"};

        cout << "\nTesting accepting strings:" << endl;
        cout << "------------------------" << endl;
        dfa.runMultiple(acceptTests, runMode::VERBOSE);

        cout << "\nTesting rejecting strings:" << endl;
        cout << "------------------------" << endl;
        dfa.runMultiple(rejectTests, runMode::VERBOSE);

        // Test some invalid inputs
        cout << "\nTesting invalid inputs:" << endl;
        cout << "------------------------" << endl;
        try {
            dfa.run("01a", runMode::VERBOSE);
        } catch (const exception& e) {
            cout << "Expected error: " << e.what() << endl;
        }

        try {
            dfa.run("2", runMode::VERBOSE);
        } catch (const exception& e) {
            cout << "Expected error: " << e.what() << endl;
        }

        // Save the DFA back to a JFF file
        dfa.convert2JFF();
        cout << "\nDFA has been saved to output.jff" << endl;

    } catch (const exception& e) {
        cerr << "Error in DFA test: " << e.what() << endl;
    }
}

void testNFA() {
    cout << "\nTesting NFA:" << endl;
    cout << "------------" << endl;

    try {
        set<State> states = {"q0", "q1", "q2"};
        set<char> alphabet = {'0', '1'};

        unordered_map<Q_x_sigma, set<State>, PairHash> delta = {
            {{"q0", '0'}, {"q0", "q1"}}, {{"q0", '1'}, {"q0"}},
            {{"q1", '0'}, {"q1"}},       {{"q1", '1'}, {"q1", "q2"}},
            {{"q2", '0'}, {"q1"}},       {{"q2", '1'}, {"q0", "q2"}}};

        State start_state = "q0";
        set<State> final_state = {"q2"};

        NFA myNFA(states, alphabet, delta, start_state, final_state);

        set<string> accept = {"01", "0011", "1111", "011"};
        set<string> reject = {"0", "10", "110", "000"};

        cout << "Testing accepting strings:" << endl;
        for (const string& s : accept) {
            cout << "String '" << s << "': "
                 << (myNFA.run(s, runMode::VERBOSE) ? "Accepted" : "Rejected")
                 << endl;
        }

        cout << "\nTesting rejecting strings:" << endl;
        for (const string& s : reject) {
            cout << "String '" << s << "': "
                 << (myNFA.run(s, runMode::VERBOSE) ? "Accepted" : "Rejected")
                 << endl;
        }
    } catch (const exception& e) {
        cerr << "Error in NFA test: " << e.what() << endl;
    }
}

int main() {
    testDFA();
    testNFA();
    return 0;
}