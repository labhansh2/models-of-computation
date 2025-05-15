#include <fstream>
#include <pugixml.hpp>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

#include "utils.h"

// TO DO : Add this as a utility function for all the automatons
// It should take the type of automaton it is parsing for
DFAComponents parseJFFFile(const string& filename) {
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str())) {
        throw runtime_error("Failed to load JFF file");
    }

    DFAComponents components;

    auto automaton = doc.child("structure").child("automaton");

    // Parse states
    for (auto state : automaton.children("state")) {
        string id = state.attribute("id").value();
        string name = state.attribute("name").value();
        components.Q.insert(name);

        if (state.child("initial")) {
            components.q_0 = name;
        }
        if (state.child("final")) {
            components.F.insert(name);
        }
    }

    // Parse transitions and build alphabet
    for (auto transition : automaton.children("transition")) {
        string from = transition.child("from").text().get();
        string to = transition.child("to").text().get();
        char symbol = transition.child("read").text().get()[0];

        components.sigma.insert(symbol);
        components.delta[make_pair("q" + from, symbol)] = "q" + to;
    }

    // Validate DFA properties
    for (const auto& state : components.Q) {
        for (const auto& symbol : components.sigma) {
            auto transition = make_pair(state, symbol);
            if (components.delta.find(transition) == components.delta.end()) {
                throw runtime_error("Missing transition for state " + state +
                                    " and symbol " + symbol);
            }
        }
    }

    return components;
}