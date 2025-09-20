#ifndef VALUE_TYPES_H
#define VALUE_TYPES_H

#include <variant>
#include <set>
#include <utility> // for std::pair
#include <vector>
#include <string>

namespace setops {

/**
 * @brief Represents a heterogeneous value.
 *
 * A Value can be one of:
 * - bool
 * - int
 * - double
 * - std::string
 *
 * This type is the element type for ValueSet.
 */
using Value = std::variant<bool, int, double, std::string>;

/**
 * @brief Represents a set of heterogeneous values.
 *
 * Implemented as std::set<Value> with default ordering and equality.
 * Used as the core container for set operations such as union, intersection, etc.
 */
using ValueSet = std::set<Value>;

/**
 * @brief Represents an ordered pair (a, b) of heterogeneous values.
 *
 * Used in the Cartesian product operation.
 */
using ValuePair = std::pair<Value, Value>;

/**
 * @brief Represents a collection of ordered pairs of heterogeneous values.
 *
 * Implemented as std::vector<ValuePair>; duplicates are possible.
 * Returned by the Cartesian product function.
 */
using ValuePairVec = std::vector<ValuePair>;

/**
 * @brief Represents a collection of sets of heterogeneous values.
 *
 * Implemented as std::vector<ValuePair>; duplicates are possible.
 * Returned by the power set function.
 */
using ValueSetVec = std::vector<ValueSet>;

} // namespace setops

#endif // VALUE_TYPES_H