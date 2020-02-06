#pragma once
namespace custom
{
    template <typename Iterator, typename Key>
    std::vector<Iterator> linear_search(Iterator begin, Iterator end, const Key& key)
    {
        std::vector<Iterator> results;
        for (Iterator it = begin; it != end; std::advance(it))
        {
            if (*it == key)
            {
                results.push_back(it);
            }
        }
        return results;
    }
}