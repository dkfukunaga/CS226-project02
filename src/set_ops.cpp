#include "set_ops.h"

namespace setops {

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

ValueSet set_intersection(const ValueSet& A, const ValueSet& B) {
    ValueSet result;
    for (const auto& elem : A) {
        if (B.find(elem) != B.end()) {
            result.insert(elem);
        }
    }
    return result;
}

ValueSet set_difference(const ValueSet& A, const ValueSet& B) {
    ValueSet result = A;
    for (const auto& elem : B) {
        if (result.find(elem) != result.end()) {
            result.extract(elem);
        }
    }
    return result;
}

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

ValuePairVec cartesian_product(const ValueSet& A, const ValueSet& B) {
    ValuePairVec result;
    for (auto elem_a : A) {
        for (auto elem_b : B) {
            result.push_back(ValuePair{elem_a, elem_b});
        }
    }
    return result;
}

ValueSetVec power_set(const ValueSet& A) {
    ValueSetVec result;
    result.push_back({}); // power set always includes the empty set

    for (const auto& elem : A) {
        size_t curr_size = result.size();
        for (size_t i = 0; i < curr_size; ++i) {
            ValueSet subset = result[i];
            subset.insert(elem);
            result.push_back(subset);
        }
    }

    return result;
}

} // namespace setops