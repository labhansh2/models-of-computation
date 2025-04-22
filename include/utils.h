#include <iostream>
#include <string>
#include <utility>

using namespace std;

// types for the project
using State = string;
using Symbol = char;
using Q_x_sigma = pair<State, Symbol>;
using Q_x_sigma_e_x_gamma = tuple<State, Symbol, Symbol>;
using Q_x_gamma = tuple<State, string>;

enum runMode { NORMAL, VERBOSE };

struct PairHash {
    size_t operator()(const pair<string, char>& p) const noexcept {
        return hash<string>{}(p.first) ^ (hash<char>{}(p.second) << 1);
    }
};

struct TupleHash {
    size_t operator()(const tuple<string, char, char>& t) const {
        size_t h1 = hash<string>{}(get<0>(t));
        size_t h2 = hash<char>{}(get<1>(t));
        size_t h3 = hash<char>{}(get<2>(t));
        return h1 ^ (h2 << 1) ^ (h3 << 2);  // bit-shifting for hash mixing
    }
};

bool hasState(set<State> currentStates, set<State> finalStates) {
    for (State q : currentStates) {
        if (finalStates.contains(q))
            return true;
    }

    return false;
}