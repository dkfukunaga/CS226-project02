#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "value_types.h"
#include "set_ops.h"
#include <algorithm> // for std::find, std::count

using namespace setops;

// compile command:
// g++ -std=c++17 -Isrc -Idoctest src/set_ops.cpp doctest/test_set_ops.cpp -o bin/run_tests
// run command:
// ./bin/run_tests.exe -s

TEST_CASE("basic union and intersection") {
    ValueSet A = {1, 2, 3};
    ValueSet B = {3, 4, 5};

    auto U = set_union(A, B);
    auto I = set_intersection(A, B);

    CHECK(U == ValueSet{1, 2, 3, 4, 5});
    CHECK(I == ValueSet{3});
}

TEST_CASE("union with empty set") {
    ValueSet A = {};
    ValueSet B = {1, 2};

    CHECK(set_union(A, B) == B);
    CHECK(set_union(B, A) == B);
    CHECK(set_union(A, A).empty());
}

TEST_CASE("intersection with empty set") {
    ValueSet A = {};
    ValueSet B = {1, 2};

    CHECK(set_intersection(A, B).empty());
    CHECK(set_intersection(B, A).empty());
    CHECK(set_intersection(A, A).empty());
}

TEST_CASE("difference and symmetric difference") {
    ValueSet A = {1, 2, 3};
    ValueSet B = {3, 4};

    auto D = set_difference(A, B);
    auto X = set_symmetric_difference(A, B);

    CHECK(D == ValueSet{1, 2});
    CHECK(X == ValueSet{1, 2, 4});
}

TEST_CASE("difference with empty set") {
    ValueSet A = {};
    ValueSet B = {1, 2};

    // A \ ∅ = A;  ∅ \ B = ∅
    CHECK(set_difference(B, A) == B);
    CHECK(set_difference(A, B).empty());
    CHECK(set_difference(A, A).empty());
}

TEST_CASE("symmetric difference with empty set") {
    ValueSet A = {};
    ValueSet B = {1, 2};

    // A ⊕ ∅ = A;  ∅ ⊕ B = B;  ∅ ⊕ ∅ = ∅
    CHECK(set_symmetric_difference(A, B) == B);
    CHECK(set_symmetric_difference(B, A) == B);
    CHECK(set_symmetric_difference(A, A).empty());
}

TEST_CASE("cartesian product") {
    ValueSet A = {1, 2};
    ValueSet B = {3, 4};

    auto P = cartesian_product(A, B);

    // Size: |A×B| = |A| * |B|
    REQUIRE(P.size() == A.size() * B.size());

    // Unordered membership checks
    CHECK(std::find(P.begin(), P.end(), ValuePair{1, 3}) != P.end());
    CHECK(std::find(P.begin(), P.end(), ValuePair{1, 4}) != P.end());
    CHECK(std::find(P.begin(), P.end(), ValuePair{2, 3}) != P.end());
    CHECK(std::find(P.begin(), P.end(), ValuePair{2, 4}) != P.end());

    // No duplicates
    CHECK(std::count(P.begin(), P.end(), ValuePair{1, 3}) == 1);
    CHECK(std::count(P.begin(), P.end(), ValuePair{1, 4}) == 1);
    CHECK(std::count(P.begin(), P.end(), ValuePair{2, 3}) == 1);
    CHECK(std::count(P.begin(), P.end(), ValuePair{2, 4}) == 1);
}

TEST_CASE("cartesian product with empty set") {
    ValueSet A = {1, 2};
    ValueSet B = {}; // empty

    auto P = cartesian_product(A, B);
    CHECK(P.empty()); // |A×∅| = 0
}

TEST_CASE("power set") {
    ValueSet A = {1, 2};

    auto P = power_set(A);

    // Should have 4 subsets: {}, {1}, {2}, {1,2}
    CHECK(P.size() == 4);

    // Unordered membership checks
    CHECK(std::find(P.begin(), P.end(), ValueSet{}) != P.end());
    CHECK(std::find(P.begin(), P.end(), ValueSet{1}) != P.end());
    CHECK(std::find(P.begin(), P.end(), ValueSet{2}) != P.end());
    CHECK(std::find(P.begin(), P.end(), ValueSet{1,2}) != P.end());
}

TEST_CASE("power set of singleton") {
    ValueSet A = {std::string("x")};

    auto P = power_set(A);

    // P({x}) = { ∅, {x} }
    REQUIRE(P.size() == 2);
    CHECK(std::find(P.begin(), P.end(), ValueSet{}) != P.end());
    CHECK(std::find(P.begin(), P.end(), ValueSet{std::string("x")}) != P.end());
}

TEST_CASE("mixed-type variant semantics (int vs string vs double)") {
    // By default: variants are equal only if same alternative AND equal value.
    ValueSet A = {1, std::string("1"), 1.0};

    // Sanity: all three are distinct elements
    CHECK(A.size() == 3);
    CHECK(A.find(1) != A.end());
    CHECK(A.find(std::string("1")) != A.end());
    CHECK(A.find(1.0) != A.end());

    // Intersection with {1.0} hits only the double
    ValueSet OnlyDouble = {1.0};
    CHECK(set_intersection(A, OnlyDouble) == ValueSet{1.0});

    // Intersection with {"1"} hits only the string
    ValueSet OnlyString = {std::string("1")};
    CHECK(set_intersection(A, OnlyString) == ValueSet{std::string("1")});

    // Intersection with {1} hits only the int
    ValueSet OnlyInt = {1};
    CHECK(set_intersection(A, OnlyInt) == ValueSet{1});

    // Symmetric difference with {1} removes int 1, keeps others
    CHECK(set_symmetric_difference(A, OnlyInt) == ValueSet{std::string("1"), 1.0});

    // Union with {1} doesn't add duplicates
    CHECK(set_union(A, OnlyInt) == A);
}

TEST_CASE("cartesian product with mixed types and empties") {
    ValueSet A = {1, std::string("1")};
    ValueSet B = {1.0};

    auto P = cartesian_product(A, B);

    REQUIRE(P.size() == A.size() * B.size()); // 2 * 1 = 2
    CHECK(std::find(P.begin(), P.end(), ValuePair{Value{1}, Value{1.0}}) != P.end());
    CHECK(std::find(P.begin(), P.end(), ValuePair{Value{std::string("1")}, Value{1.0}}) != P.end());

    // With empty partner, product is empty
    ValueSet Empty = {};
    CHECK(cartesian_product(A, Empty).empty());
    CHECK(cartesian_product(Empty, B).empty());
}
