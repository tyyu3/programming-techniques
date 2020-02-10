#pragma once
#include <iterator>
namespace custom
{

    // Iterator-associated type aliases
    template <typename Iterator>
    using diff_t = typename std::iterator_traits<Iterator>::difference_type;
    template <typename Iterator>
    using elem_type = typename std::iterator_traits<Iterator>::value_type;
    // Extractor function
    template <typename Iterator>
    const elem_type<Iterator>& trivial_extractor(const elem_type<Iterator>& elem)
    {
        return elem;
    }



    template <typename Iterator, typename Key, typename Comparator, typename KeyExtractor>
    Iterator upper_bound(Iterator begin, Iterator end, const Key& key, Comparator cmp, KeyExtractor extractor)
    {
        diff_t<Iterator> length = std::distance(begin, end);
        diff_t<Iterator> half;
        while (length > 0)
        {
            Iterator current;
            current = begin;
            half = length / 2;
            std::advance(current, half);
            if (!cmp(key, extractor(*current)))
            {
                begin = ++current;
                length -= half + 1;
            }
            else
            {
                length = half;
            }
        }
        return begin;
    }

    template <typename Iterator, typename Key, typename Comparator, typename KeyExtractor>
    Iterator lower_bound(Iterator begin, Iterator end, const Key& key, Comparator cmp, KeyExtractor extractor)
    {
        diff_t<Iterator> length = std::distance(begin, end), half;
        while (length > 0)
        {
            Iterator current = begin;
            half = length / 2;
            std::advance(current, half);
            if (cmp(extractor(*current), key))
            {
                begin = ++current;
                length -= half + 1;
            }
            else
            {
                length = half;
            }
        }
        return begin;
    }

    template <typename Iterator, typename Key, typename Comparator, typename KeyExtractor>
    std::vector<Iterator> binary_search(Iterator begin, Iterator end, const Key& key, Comparator cmp, KeyExtractor extractor)
    {
        Iterator lower = lower_bound(begin, end, key, cmp, extractor);
        Iterator upper = upper_bound(begin, end, key, cmp, extractor);
        std::vector<Iterator> result;
        while (lower != upper)
        {
            result.push_back(lower);
            std::advance(lower, 1);
        }
        return result;
    }
    template <typename Iterator, typename Key>
    std::vector<Iterator> binary_search(Iterator begin, Iterator end, const Key& key)
    {
        return binary_search(begin, end, key, std::less<elem_type<Iterator>>(), trivial_extractor<Iterator>);
    }

}