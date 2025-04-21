#include <functional>
#include <iostream>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>

#include "utils.h"

using namespace std;

class PDA {
   public:
    using State = string;
    using Symbol = char;
    using Q_x_sigma_e_x_gamma = tuple<State, Symbol, Symbol>;
    using Q_x_gamma = tuple<State, string>;

    PDA(set<State> Q,
        set<Symbol> sigma,
        set<Symbol> gamma,
        unordered_map<Q_x_sigma_e_x_gamma, Q_x_gamma, TupleHash> delta,
        State q_0,
        Symbol Z,
        State F);

    bool run(string w, runMode mode);

    bool runMultiple(set<string> L, runMode mode);

   private:
    // internal memory of the PDA
    set<State> Q_;
    set<Symbol> sigma_;
    set<Symbol> gamma_;
    unordered_map<Q_x_sigma_e_x_gamma, Q_x_gamma, TupleHash> detla_;
    State q_0_;
    Symbol Z_;
    State F_;

    // external memory
    stack<Symbol> PDA_stack;
    State currentState;

    void _reset();
};