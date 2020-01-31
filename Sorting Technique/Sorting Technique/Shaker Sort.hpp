#pragma once
#include <algorithm>
namespace custom
{
    template <typename Iterator, typename Comparator>
    void shaker_sort(Iterator begin, Iterator end, Comparator cmp)
    {
        Iterator left = begin;
        Iterator right = end;
        bool swapped = true;
        while (left != right-- && swapped)
        {
            swapped = false;
            for (auto i = left; i != right; ++i)
            {
                if (cmp(*(i+1), *i))
                {
                    std::iter_swap(i, i + 1);
                    swapped = true;
                }
            }
            if (!swapped)
                break;

            swapped = false;
            for (auto i = right - 1; i != left; --i)
            {
                if (cmp(*i,*(i - 1)))
                {
                    std::iter_swap(i, i - 1);
                    swapped = true;
                }
            }
            ++left;
        }
        return;
    }

    template <typename Iterator>
    void shaker_sort(Iterator begin, Iterator end)
    {
        using elem_type = decltype(*begin);
        shaker_sort(begin, end, [](const elem_type& lhs, const elem_type& rhs) { return lhs < rhs; });
        return;
    }
}