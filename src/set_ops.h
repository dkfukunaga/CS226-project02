#ifndef SET_OPS_H
#define SET_OPS_H

#include <vector>
#include "value_types.h"

namespace setops {

ValueSet        set_union(const ValueSet& A, const ValueSet& B);
ValueSet        set_intersection(const ValueSet& A, const ValueSet& B);
ValueSet        set_difference(const ValueSet& A, const ValueSet& B);
ValueSet        set_symmetric_difference(const ValueSet& A, const ValueSet& B);

ValuePairVec    cartesian_product(const ValueSet& A, const ValueSet& B);

ValueSetVec     power_set(const ValueSet& A);

} // namespace setops

#endif // SET_OPS_H