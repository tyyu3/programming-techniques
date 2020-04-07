/**
 * @file
 * @brief Заголовочный файл, содержащий реализацию критерия
 * хи-квадрат
 * @date Март 2020
 */
#pragma once
#include <algorithm>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <boost/math/distributions.hpp>
namespace custom
{
/// Допустимые типы распределений
enum class DistributionType
{
    UNIFORM_INT, ///< равномерное целочисленное
    UNIFORM_REAL, ///< равномерное непрерывное
};
/**
     * Вычисляет значение хи-квадрат для данной выборки
     * @tparam Number тип элемента выборки
     * @param[in] sample выборка
     * @param[in] min минимальное значение, которое могло быть получено при генерации выборки
     * @param[in] max максимальное значение, которое могло быть получено при генерации выборки
     * @param[in] type тип распределения
     * @return `std::pair`, первый элемент которой - посчитанное значение хи-квадрат,
     * второй - количество степеней свободы
     */
template <typename Number>
std::pair<double, std::size_t> chi_squared(const std::vector<Number>& sample, Number min, Number max, DistributionType type)
{
    std::ostringstream exception_message;
    if (min >= max)
    {
        exception_message << "Range minimum " << min << " is not less than range maximum " << max;
        throw std::invalid_argument(exception_message.str());
    }
    if (sample.size() < 2)
    {
        exception_message << "Sample size " << sample.size() << " is too small";
        throw std::invalid_argument(exception_message.str());
    }
    int add = (type == DistributionType::UNIFORM_INT ? 1 : 0);
    double interval = static_cast<double>(max) - min + add;

    std::size_t num_of_buckets = static_cast<size_t>(std::log2(sample.size()) + 1);
    if (type == DistributionType::UNIFORM_INT && static_cast<double>(num_of_buckets) > interval)
        num_of_buckets = static_cast<double>(interval);
    double bucket_size = interval / num_of_buckets;
    std::vector<Number> bucket_edges(num_of_buckets + 1);
    bucket_edges[0] = min;
    for (size_t i = 1; i <= num_of_buckets; ++i)
    {
        bucket_edges[i] = static_cast<Number>(min + bucket_size * i);
    }
    std::vector<double> probabilities_uniform(num_of_buckets);
    for (std::size_t i = 0; i < num_of_buckets - 1; ++i)
        probabilities_uniform[i] = (bucket_edges[i + 1] - bucket_edges[i]) / interval;
    probabilities_uniform[num_of_buckets - 1] = (bucket_edges[num_of_buckets] - bucket_edges[num_of_buckets - 1]) / interval;
    std::vector<double> probabilities_empirical(num_of_buckets, 0);
    for (Number num : sample)
    {
        size_t position = std::upper_bound(bucket_edges.begin(), bucket_edges.end(), num) - bucket_edges.begin() - 1;
        if (position == num_of_buckets && type == DistributionType::UNIFORM_INT/* && num == max*/)
        {
            ++probabilities_empirical[num_of_buckets-1];
            continue;
        }
        if (position == num_of_buckets)
        {
            exception_message << "Sample value " << num << " is not in range [" << min << "; " << max
                              << (type == DistributionType::UNIFORM_INT ? "]" : ")");
            throw std::invalid_argument(exception_message.str());
        }
        ++probabilities_empirical[position];
    }
    std::for_each(probabilities_uniform.begin(), probabilities_uniform.end(), [&sample](double& num) { num *= sample.size(); });
    double chi = 0;
    for (std::size_t i = 0; i < num_of_buckets; ++i)
    {
        double diff = probabilities_empirical[i] - probabilities_uniform[i];
        chi += diff * diff / probabilities_uniform[i];
    }
    return {chi, num_of_buckets - 1};
}

/**
     * Проверяет статистический критерий хи-квадрат Пирсона для заданной выборки
     * @tparam Number тип элемента выборки
     * @param[in] sample выборка
     * @param[in] min минимальное значение, которое могло быть получено при генерации выборки
     * @param[in] max максимальное значение, которое могло быть получено при генерации выборки
     * @param[in] significance_level уровень значимости (вероятность отклонить истинную гипотезу)
     * @param[in] type тип распределения
     * @return `true`, если выборка удовлетворяет критерию хи-квадрат, `false` в противном случае
     */
template <typename Number>
bool chi_squared_test(const std::vector<Number>& sample, Number min, Number max, double significance_level, DistributionType type)
{
    if (significance_level <= 0 || significance_level >= 1)
    {
        std::ostringstream exception_message;
        exception_message << "Significance level " << significance_level << " is not in (0; 1) interval";
        throw std::invalid_argument(exception_message.str());
    }
    auto chi = chi_squared<Number>(sample, min, max, type);
    namespace bm = boost::math;
    auto qt = bm::quantile(bm::chi_squared_distribution<double>(chi.second), 1- significance_level);
    return (chi.first <= qt);
}
}