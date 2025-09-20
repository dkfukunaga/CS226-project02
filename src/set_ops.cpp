#include "set_ops.h"

namespace setops {

ValueSet        set_union(const ValueSet& A, const ValueSet& B) {
    ValueSet result;
    for (auto& elem : A) {
        result.insert(elem);
    }
    for (auto& elem : B) {
        result.insert(elem);
    }
    return result;
}

ValueSet        set_intersection(const ValueSet& A, const ValueSet& B) {
    ValueSet result;
    for (auto& elem_a : A) {
        for (auto& elem_b : B) {
            if (elem_a == elem_b) {
                result.insert(elem_a);
                break;
            }
        }
    }
    return result;
}

ValueSet        set_difference(const ValueSet& A, const ValueSet& B) {
    ValueSet result = A;
    for (auto& elem : B) {
        if (result.find(elem) != result.end()) {
            result.extract(elem);
        }
    }
    return result;
}

ValueSet        set_symmetric_difference(const ValueSet& A, const ValueSet& B) {
    ValueSet result;
    for (auto& elem : A) {
        if (B.find(elem) == B.end()) {
            result.insert(elem);
        }
    }
    for (auto& elem : B) {
        if (A.find(elem) == A.end()) {
            result.insert(elem);
        }
    }
    return result;
}

ValuePairVec    cartesian_product(const ValueSet& A, const ValueSet& B) {
    return {};
}

ValueSetVec     power_set(const ValueSet& A) {
    return {};
}

} // namespace setops