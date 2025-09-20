#ifndef SET_OPS_H
#define SET_OPS_H

#include <vector>
#include "value_types.h"

namespace setops {

/**
 * @brief A ∪ B = { x | x ∈ A or x ∈ B }
 *        Set of all of the elements of both A and B.
 * 
 * @param A set A
 * @param B set B
 * @return ValueSet – A union B
 */
ValueSet set_union(const ValueSet& A, const ValueSet& B);

/**
 * @brief A ∩ B = { x | x ∈ A and x ∈ B }
 *        Set of all of the elements shared by A and B.
 * 
 * @param A set A
 * @param B set B
 * @return ValueSet – A intersection B
 */
ValueSet set_intersection(const ValueSet& A, const ValueSet& B);

/**
 * @brief A \ B = { x | x ∈ A and x ∉ B }
 *        Set of all of the elements of A that are not also in B.
 * 
 * @param A set A
 * @param B set B
 * @return ValueSet – difference of A and B
 */
ValueSet set_difference(const ValueSet& A, const ValueSet& B);

/**
 * @brief A ⊕ B = (A \ B) ∪ (B \ A)
 *        Set of all the elements that are in exactly one of A or B.
 * 
 * @param A set A
 * @param B set B
 * @return ValueSet – A xor B
 */
ValueSet set_symmetric_difference(const ValueSet& A, const ValueSet& B);

/**
 * @brief A × B = { (a, b) | a ∈ A and b ∈ B }
 * 
 * @param A set A
 * @param B set B
 * @return ValuePairVec 
 */
ValuePairVec cartesian_product(const ValueSet& A, const ValueSet& B);

/**
 * @brief P(A) = { S | S ⊆ A }
 * 
 * @param A set A
 * @return ValueSetVec 
 */
ValueSetVec power_set(const ValueSet& A);

} // namespace setops

#endif // SET_OPS_H