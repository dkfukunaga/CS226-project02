#ifndef VALUE_TYPES_H
#define VALUE_TYPES_H

#include <variant>
#include <set>
#include <utility>
#include <vector>
#include <string>

namespace setops {

// Value variant to create heterogeneous set
using Value = std::variant<bool, int, double, std::string>;

// heterogeneous set of Value
using ValueSet = std::set<Value>;

// pairs for cartesian product
using ValuePair = std::pair<Value, Value>;

// vector for cartesian product
using ValuePairVec = std::vector<ValuePair>;

// vector of sets for power set
using ValueSetVec = std::vector<ValueSet>;

} // namespace setops

#endif // VALUE_TYPES_H