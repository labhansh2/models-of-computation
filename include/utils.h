#include <iostream>
#include <string>
#include <utility>

using namespace std;

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