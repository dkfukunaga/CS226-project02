#ifndef SET_OPS_IO_H
#define SET_OPS_IO_H

#include "value_types.h"
#include <iostream>

namespace setops {

// ostream operator for Value
// prints bool as "true" or "false"
// generated with chatgpt because this is beyond the scope of this assignment
inline std::ostream& operator<<(std::ostream& os, const Value& v) {
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, bool>)
            os << (arg ? "true" : "false");
        else
            os << arg;
    }, v);
    return os;
}

} // namespace setops

#endif // SET_OPS_IO_H