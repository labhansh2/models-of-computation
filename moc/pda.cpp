#include <iostream>
#include <tuple>
#include <unordered_map>

#include "pda.h"

using namespace std;

PDA::PDA(set<State> Q,
         set<Symbol> sigma,
         set<Symbol> gamma,
         unordered_map<Q_x_sigma_e_x_gamma, Q_x_gamma, TupleHash> delta,
         State q_0,
         Symbol Z,
         State F)
    : Q_(Q),
      sigma_(sigma),
      gamma_(gamma),
      detla_(delta),
      q_0_(q_0),
      Z_(Z),
      F_(F) {
    PDA_stack.push(Z);
    currentState = q_0;
};

bool PDA::run(string w, runMode mode) {
    for (char c : w) {
        Q_x_sigma_e_x_gamma currentConfig(currentState, c, PDA_stack.top());
        Q_x_gamma nextAction = detla_[currentConfig];

        currentState = get<0>(nextAction);
        string pushStr = get<1>(nextAction);

        PDA_stack.pop();

        for (char s : pushStr) {
            PDA_stack.push(s);
        }
    }

    return PDA_stack.empty();
}

bool PDA::runMultiple(set<string> L, runMode mode) {
    bool flag = true;
    for (string w : L) {
        bool res = run(w, NORMAL);

        _reset();
        if (!res)
            flag = false;
    }

    return flag;
}

void PDA::_reset() {
    while (!PDA_stack.empty()) {
        PDA_stack.pop();
    }

    currentState = q_0_;
}