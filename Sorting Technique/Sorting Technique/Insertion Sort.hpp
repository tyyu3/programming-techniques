#pragma once
#include <algorithm>
namespace custom
{
    template <typename Iterator, typename Comparator>
    void insertion_sort(Iterator begin, Iterator end, Comparator cmp)
    {
        Iterator sorted_before = begin;
        Iterator current;
        while (sorted_before != end)
        {
            current = sorted_before;
            while (current != begin && cmp(*current,*(current-1)))
            {
                std::iter_swap(current, (current - 1));
                current--;
            }
            sorted_before++;
        }
        return;
    }

    template <typename Iterator>
    void insertion_sort(Iterator begin, Iterator end)
    {
        using elem_type = decltype(*begin);
        insertion_sort(begin, end, [](const elem_type& lhs, const elem_type& rhs) { return lhs < rhs; });
        return;
    }
}