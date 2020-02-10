#pragma once
#include "CampEntry.hpp"
#include "LinearSearch.hpp"
#include "test_runner.hpp"
#include <vector>

namespace linear
{
    void test_basic()
    {
        std::vector<int> a = {1, 2, 3, 5, 4, 6, 9, 11, 12};
        auto res1 = custom::linear_search(a.begin(), a.end(), 3);
        ASSERT_EQUAL(*res1[0], *(a.begin() + 2));
    }
    void test_multiple()
    {
        std::vector<int> b = {1, 2, 3, 5, 4, 6, 9, 11, 12, 11};
        auto res = custom::linear_search(b.begin(), b.end(), 11);
        ASSERT_EQUAL(*res[0], *(b.end() - 1));
        ASSERT_EQUAL(*res[1], *(b.end() - 3));
    }
    void test_class()
    {
        std::vector<CampEntry> vec = {{1944, 4, 2, "mike brooks", {18, 18, 1929}}, {1956, 4, 2, "mike koos", {18, 18, 1929}}, {1944, 4, 2, "mike brooks", {18, 18, 1929}}};
        CampEntry tofind({1944, 4, 2, "mike brooks", {18, 18, 1929}});
        auto res = custom::linear_search(vec.begin(), vec.end(), tofind);
        ASSERT_EQUAL(* *res.begin(), *vec.begin());
        ASSERT_EQUAL(* *(res.end()-1), *(vec.end()-1));
        res = custom::linear_search(vec.begin(), vec.end(), "mike koos", [](CampEntry lhs, std::string rhs){
        return lhs.name() == rhs;});
        ASSERT_EQUAL((*res[0]).year(),1956);
    }

    int test_linear()
    {
        TestRunner tr;
        RUN_TEST(tr, test_basic);
        RUN_TEST(tr, test_multiple);
        RUN_TEST(tr, test_class);
        return 0;
    }
}