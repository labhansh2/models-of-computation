#include <iostream>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <functional>

using namespace std;

struct TupleHash {
    std::size_t operator()(const std::tuple<std::string, char, char>& t) const {
        std::size_t h1 = std::hash<std::string>{}(std::get<0>(t));
        std::size_t h2 = std::hash<char>{}(std::get<1>(t));
        std::size_t h3 = std::hash<char>{}(std::get<2>(t));
        return h1 ^ (h2 << 1) ^ (h3 << 2); // bit-shifting for hash mixing
    }
};

enum runMode { NORMAL, VERBOSE };

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