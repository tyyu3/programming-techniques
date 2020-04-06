/**
 * @file
 * @brief Заголовочный файл, содержащий реализацию сортировки выбором
 * @date Январь 2020
*/
#pragma once
#include <algorithm>
namespace custom
{
/** Реализует сортировку выбором диапазона элементов
     * @tparam Iterator Iterator тип, удовлетворяющий LegacyBidirectionalIterator и *Iterator должен быть Swappable
     * @tparam Comparator тип, удовлетворяющий C++ named requirement Compare
     * @param[in,out] begin,end итераторы, указывающие на диапазон, который
     * требуется отсортировать
     * @param cmp компаратор: возвращает `true`, если его первый аргумент должен стоять
     * в отсортированном диапазоне строго левее второго, `false` иначе
    */
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
    /** Реализует сортировку выбором диапазона элементов
     * @tparam Iterator Iterator тип, удовлетворяющий LegacyBidirectionalIterator и *Iterator должен быть Swappable
     * @tparam Comparator тип, удовлетворяющий C++ named requirement Compare
     * @param[in,out] begin,end итераторы, указывающие на диапазон, который
     * требуется отсортировать
    */ 
    template <typename Iterator>
    void selection_sort(Iterator begin, Iterator end)
    {
        using elem_type = decltype(*begin);
        selection_sort(begin, end, [](const elem_type& lhs, const elem_type& rhs) { return lhs < rhs; });
        return;
    }
}