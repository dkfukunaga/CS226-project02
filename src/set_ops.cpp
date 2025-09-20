#include "set_ops.h"

namespace setops {

// A ∪ B = { x | x ∈ A or x ∈ B }
ValueSet set_union(const ValueSet& A, const ValueSet& B) {
    ValueSet result;
    for (const auto& elem : A) {
        result.insert(elem);
    }
    for (const auto& elem : B) {
        result.insert(elem);
    }
    return result;
}

// A ∩ B = { x | x ∈ A and x ∈ B }
ValueSet set_intersection(const ValueSet& A, const ValueSet& B) {
    ValueSet result;
    for (const auto& elem : A) {
        if (B.find(elem) != B.end()) {
            result.insert(elem);
        }
    }
    return result;
}

// A \ B = { x | x ∈ A and x ∉ B }
ValueSet set_difference(const ValueSet& A, const ValueSet& B) {
    ValueSet result = A;
    for (const auto& elem : B) {
        if (result.find(elem) != result.end()) {
            result.extract(elem);
        }
    }
    return result;
}

// A ⊕ B = (A \ B) ∪ (B \ A)
ValueSet set_symmetric_difference(const ValueSet& A, const ValueSet& B) {
    ValueSet result;
    for (const auto& elem : A) {
        if (B.find(elem) == B.end()) {
            result.insert(elem);
        }
    }
    for (const auto& elem : B) {
        if (A.find(elem) == A.end()) {
            result.insert(elem);
        }
    }
    return result;
}

// A × B = { (a, b) | a ∈ A and b ∈ B }
ValuePairVec cartesian_product(const ValueSet& A, const ValueSet& B) {
    return {};
}

// P(A) = { S | S ⊆ A }
ValueSetVec power_set(const ValueSet& A) {
    return {};
}

} // namespace setops