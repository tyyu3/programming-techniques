/**
 * @file
 * @brief Заголовочный файл, содержащий реализацию сортировки вставками
 * @date Январь 2020
*/
#pragma once
#include <algorithm>
namespace custom
{
    /** Реализует простую сортировку вставками диапазона элементов
     * @tparam Iterator Iterator тип, удовлетворяющий LegacyBidirectionalIterator и *Iterator должен быть Swappable
     * @tparam Comparator тип, удовлетворяющий C++ named requirement Compare
     * @param[in,out] begin,end итераторы, указывающие на диапазон, который
     * требуется отсортировать
     * @param cmp компаратор: возвращает `true`, если его первый аргумент должен стоять
     * в отсортированном диапазоне строго левее второго, `false` иначе
    */
    template <typename Iterator, typename Comparator>
    void insertion_sort(Iterator begin, Iterator end, Comparator cmp)
    {
        Iterator sorted_before = begin;
        Iterator current;
        while (sorted_before != end)
        {
            current = sorted_before;
            while (current != begin && cmp(*current,*std::prev(current)))
            {
                std::iter_swap(current, std::prev(current));
                --current;
            }
            ++sorted_before;
        }
        return;
    }
    /** Реализует простую сортировку вставками диапазона элементов
     * @tparam Iterator Iterator тип, удовлетворяющий LegacyBidirectionalIterator и *Iterator должен быть Swappable
     * @tparam Comparator тип, удовлетворяющий C++ named requirement Compare
     * @param[in,out] begin,end итераторы, указывающие на диапазон, который
     * требуется отсортировать
    */ 
    template <typename Iterator>
    void insertion_sort(Iterator begin, Iterator end)
    {
        using elem_type = decltype(*begin);
        insertion_sort(begin, end, [](const elem_type& lhs, const elem_type& rhs) { return lhs < rhs; });
        return;
    }
}