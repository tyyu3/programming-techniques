#pragma once
namespace custom
{
    template <typename Iterator, typename Key, typename BinaryPredicate>
    std::vector<Iterator> linear_search(Iterator begin, Iterator end, const Key& key, BinaryPredicate equal)
    {
        std::vector<Iterator> results;
        for (Iterator it = begin; it != end; std::advance(it, 1))
        {
            if (equal(*it, key))
            {
                results.push_back(it);
            }
        }
        return results;
    }
    template <typename Iterator, typename Key>
    std::vector<Iterator> linear_search(Iterator begin, Iterator end, const Key& key)
    {
        return linear_search(begin, end, key, std::equal_to<typename std::iterator_traits<Iterator>::value_type>());
    }
}