#ifndef SET_OPS_H
#define SET_OPS_H

#include "value_types.h"

/**
 * @namespace setops
 * @brief Provides mathematical set operations on heterogeneous value sets.
 *
 * The `setops` namespace defines a collection of functions for standard
 * set operations on `ValueSet`, a heterogeneous set of values represented
 * using `std::variant`. Supported operations include:
 *
 * - Union (A ∪ B)
 * - Intersection (A ∩ B)
 * - Difference (A \ B)
 * - Symmetric difference (A ⊕ B)
 * - Cartesian product (A × B)
 * - Power set (𝒫(A))
 *
 * Each function follows the standard mathematical definition, while
 * working with the `ValueSet` type defined in `value_types.h`.
 *
 * @see ValueSet
 * @see value_types.h
 */
namespace setops {

/**
 * @brief Computes the union of two sets.
 * 
 * Mathematical definition:
 *   A ∪ B = { x | x ∈ A or x ∈ B }
 * 
 * @param A Set A
 * @param B Set B
 * @return ValueSet Set containing all unique elements from A and B.
 */
ValueSet set_union(const ValueSet& A, const ValueSet& B);

/**
 * @brief Computes the intersection of two sets.
 *
 * Mathematical definition:
 *   A ∩ B = { x | x ∈ A and x ∈ B }
 * 
 * @param A Set A
 * @param B Set B
 * @return ValueSet Set containing only the elements present in both A and B.
 */
ValueSet set_intersection(const ValueSet& A, const ValueSet& B);

/**
 * @brief Computes the difference of two sets.
 *
 * Mathematical definition:
 *   A \ B = { x | x ∈ A and x ∉ B }
 * 
 * @param A Set A
 * @param B Set B
 * @return ValueSet Set containing elements of A that are not in B.
 */
ValueSet set_difference(const ValueSet& A, const ValueSet& B);

/**
 * @brief Computes the symmetric difference of two sets.
 *
 * Mathematical definition:
 *   A ⊕ B = (A \ B) ∪ (B \ A)
 * 
 * @param A Set A
 * @param B Set B
 * @return ValueSet Set containing elements present in exactly one of A or B.
 */
ValueSet set_symmetric_difference(const ValueSet& A, const ValueSet& B);

/**
 * @brief Computes the Cartesian product of two sets.
 *
 * Mathematical definition:
 *   A × B = { (a, b) | a ∈ A and b ∈ B }
 * 
 * @param A Set A
 * @param B Set B
 * @return ValuePairVec Vector of ordered pairs representing all (a, b) combinations.
 */
ValuePairVec cartesian_product(const ValueSet& A, const ValueSet& B);

/**
 * @brief Computes the power set of a set.
 *
 * Mathematical definition:
 *   𝒫(A) = { S | S ⊆ A }
 * 
 * @param A Set A
 * @return ValueSetVec Vector of all subsets of A.
 */
ValueSetVec power_set(const ValueSet& A);

} // namespace setops

#endif // SET_OPS_H