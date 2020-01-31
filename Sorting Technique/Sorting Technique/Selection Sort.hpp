#pragma once
#include <algorithm>
namespace custom
{
    template <typename Iterator, typename Comparator>
    void selection_sort(Iterator begin, Iterator end, Comparator cmp)
    {
        Iterator sorted_before = begin;
        Iterator next = begin;
        while (sorted_before != end)
        {
            next = std::min_element(sorted_before, end, cmp);
            if (next != sorted_before)
                std::iter_swap(sorted_before, next);
            ++sorted_before;
        }
        return;
    }

    template <typename Iterator>
    void selection_sort(Iterator begin, Iterator end)
    {
        using elem_type = decltype(*begin);
        selection_sort(begin, end, [](const elem_type& lhs, const elem_type& rhs) { return lhs < rhs; });
        return;
    }
}