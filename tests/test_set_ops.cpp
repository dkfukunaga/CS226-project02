#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/value_types.h"
#include "../src/set_ops.h"
#include <sstream>

using namespace setops;

TEST_CASE("basic union and intersection") {
    ValueSet A = {1, 2, 3};
    ValueSet B = {3, 4, 5};

    auto U = set_union(A, B);
    auto I = set_intersection(A, B);

    CHECK(U == ValueSet{1, 2, 3, 4, 5});
    CHECK(I == ValueSet{3});
}

TEST_CASE("difference and symmetric difference") {
    ValueSet A = {1, 2, 3};
    ValueSet B = {3, 4};

    auto D = set_difference(A, B);
    auto X = set_symmetric_difference(A, B);

    CHECK(D == ValueSet{1, 2});
    CHECK(X == ValueSet{1, 2, 4});
}

TEST_CASE("cartesian product") {
    ValueSet A = {1, 2};
    ValueSet B = {3, 4};

    auto P = cartesian_product(A, B);

    // unordered check
    CHECK(std::find(P.begin(), P.end(), ValuePair{1, 3}) != P.end());
    CHECK(std::find(P.begin(), P.end(), ValuePair{2, 4}) != P.end());
}

TEST_CASE("power set") {
    ValueSet A = {1, 2};

    auto P = power_set(A);

    // Should have 4 subsets: {}, {1}, {2}, {1,2}
    CHECK(P.size() == 4);
}
