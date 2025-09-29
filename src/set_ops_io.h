#ifndef SET_OPS_IO_H
#define SET_OPS_IO_H

#include "value_types.h"
#include <cstdint>
#include <iostream>

namespace setops {

// flags to track type
const uint8_t NUM_VAL = 1;
const uint8_t DBL_VAL = 1 << 1;
const uint8_t STR_VAL = 1 << 2;

ValueSet parseSet(std::string line);

void parseToken(ValueSet& set, std::string raw_token, uint8_t flags);

// ostream operator for Value
// prints bool as "true" or "false"
// generated with chatgpt because this is beyond the scope of this assignment
inline std::ostream& operator<<(std::ostream& os, const Value& v) {
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, bool>)
            os << (arg ? "true" : "false");
        else if constexpr (std::is_same_v<T, std::string>)
            os << "\"" << arg << "\"";
        else
            os << arg;
    }, v);
    return os;
}

// simple ostream operator for Pair<Value, Value>
inline std::ostream& operator<<(std::ostream& out, const ValuePair& p) {
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

inline std::ostream& operator<<(std::ostream& out, const ValuePairVec& v) {
    if (v.empty()) {
        out << "{}";
        return out;
    }
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (it == v.begin())
            out << "{" << *it;
        else
            out << ", " << *it;
    }
    out << "}";
    return out;
}

inline std::ostream& operator<<(std::ostream& out, const ValueSet& s) {
    if (s.empty()) {
        out << "{}";
        return out;
    }
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it == s.begin())
            out << "{" << *it;
        else
            out << ", " << *it;
    }
    out << "}";
    return out;
}

inline std::ostream& operator<<(std::ostream& out, const ValueSetVec& v) {
    if (v.empty()) {
        out << "{}";
        return out;
    }
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (it == v.begin())
            out << "{" << *it;
        else
            out << ", " << *it;
    }
    out << "}";
    return out;
}

} // namespace setops

#endif // SET_OPS_IO_H