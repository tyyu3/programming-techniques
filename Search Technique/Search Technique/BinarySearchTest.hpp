#pragma once
#include "CampEntry.hpp"
#include "BinarySearch.hpp"
#include "test_runner.hpp"
#include <vector>
#include <algorithm>

namespace binary
{
    void test_basic()
    {
        std::vector<int> a = {1, 2, 3, 5, 4, 6, 9, 11, 12};
        std::sort(a.begin(),a.end());
        auto res1 = custom::binary_search(a.begin(), a.end(), 3);
        ASSERT_EQUAL(*res1[0], *(a.begin() + 2));
    }
    void test_multiple()
    {
        std::vector<int> b = {1, 2, 3, 5, 4, 6, 9, 11, 12, 11};
        std::sort(b.begin(), b.end());
        auto res = custom::binary_search(b.begin(), b.end(), 11);
        ASSERT_EQUAL(*res[0], *(b.end() - 3));
        ASSERT_EQUAL(*res[1], *(b.end() - 2));
    }
    void test_class()
    {
        std::vector<CampEntry> vec = {{1944, 4, 2, "mike brooks", {18, 18, 1929}}, {1956, 4, 2, "mike koos", {18, 18, 1929}}, {1944, 4, 2, "mike brooks", {18, 18, 1929}}};
        std::sort(vec.begin(), vec.end());
        CampEntry tofind({1944, 4, 2, "mike brooks", {18, 18, 1929}});
        auto res = custom::binary_search(vec.begin(), vec.end(), tofind);
        ASSERT_EQUAL(* *res.begin(), *vec.begin());
        ASSERT_EQUAL(* *(res.end()-1), *(vec.end()-2));
        res = custom::binary_search(
            vec.begin(), vec.end(), "mike koos", [](std::string lhs, std::string rhs) { return lhs < rhs; }, [](const CampEntry& elem) { return elem.name(); });
        ASSERT_EQUAL((*res[0]).year(),1956);

    }
    void test_size()
    {
        std::vector<CampEntry> vec =
        {{1941, 4, 2, "mike brooks", {18, 18, 1929}},
        {1956, 4, 2, "mike koos", {18, 18, 1929}},
        {1942, 4, 2, "mike brooks", {18, 18, 1929}},
        {1943, 4, 2, "mike brooks", {18, 18, 1929}}};
        std::sort(vec.begin(), vec.end());
        auto res = custom::binary_search(
            vec.begin(), vec.end(), "mike koos", [](std::string lhs, std::string rhs) { return lhs < rhs; }, [](const CampEntry& elem) { return elem.name(); });
        ASSERT_EQUAL(res.size(), 1);
        res = custom::binary_search(
            vec.begin(), vec.end(), "mike koosy", [](std::string lhs, std::string rhs) { return lhs < rhs; }, [](const CampEntry& elem) { return elem.name(); });
        ASSERT_EQUAL(res.size(), 0);
        res = custom::binary_search(
            vec.begin(), vec.end(), "mike brooks", [](std::string lhs, std::string rhs) { return lhs < rhs; }, [](const CampEntry& elem) { return elem.name(); });
        ASSERT_EQUAL(res.size(), 3);
    }

    int test_binary()
    {
        TestRunner tr;
        RUN_TEST(tr, test_basic);
        RUN_TEST(tr, test_multiple);
        RUN_TEST(tr, test_class);
        RUN_TEST(tr, test_size);
        return 0;
    }
}