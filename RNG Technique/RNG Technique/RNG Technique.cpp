// RNG Technique.cpp : Defines the entry point for the application.
//

#include "RNG Technique.h"
#include "ChiSquared.hpp"
#include "RandomFunctions.hpp"
namespace custom
{
/**
     * Вычисляет выборочное среднее вектора числовых значений
     * @tparam T тип значений
     * @param[in] sample вектор
     * @return выборочное среднее
     */
template <typename T>
double mean(std::vector<T> sample)
{
    return static_cast<double>(std::accumulate(std::begin(sample), std::end(sample), 0.0)) / std::size(sample);
}

/**
     * Вычисляет СКО вектора числовых значений
     * @tparam T тип значений
     * @param[in] sample вектор
     * @return СКО
     */
template <typename T>
double variance(std::vector<T> sample)
{
    double m = mean(sample);
    double s = 0;
    for (const auto& value : sample)
        s += (value - m) * (value - m);
    s /= sample.size();
    return std::sqrt(s);
}

/**
     * Вычисляет коэф. вариации вектора числовых значений
     * @tparam T тип значений
     * @param[in] sample вектор
     * @return коэф. вариации
     */
template <typename T>
double variability(std::vector<T> sample)
{
    return variance(sample) / mean(sample);
}
}

unsigned generated; //unused, global to prevent optimizing-out

int main()
{
    //set common seed
    constexpr int seed = 1;
    //initialize PRNGs
    custom::EffortlessPRNG eprng(seed);
    std::cout << "Effortless PRNG LIMITS:" << eprng.min() << " to " << eprng.max() << "\n";
    custom::AdvancedPRNG aprng(seed);
    std::cout << "Advanced PRNG LIMITS:" << aprng.min() << " to " << aprng.max() << "\n";
    std::mt19937 mtprng(seed);
    std::cout << "Mersenne-Twister PRNG LIMITS:" << mtprng.min() << " to " << mtprng.max() << "\n";
    std::vector<std::vector<std::uint32_t>> e_samples(20), a_samples(20), mt_samples(20);

    //test samples
    for (unsigned i = 0; i < 10; ++i)
    {
        for (unsigned j = 0; j < 20'000; ++j)
        {
            e_samples[i].push_back(eprng());
            a_samples[i].push_back(aprng());
            mt_samples[i].push_back(mtprng());
        }
    }
    double significance = 0.85;
    for (unsigned i = 0; i < 10; ++i)
    {
        std::cout << "effortless mean\t" << i << ": " << custom::mean(e_samples[i]) << "\n";
        std::cout << "effortless variance\t" << i << ": " << custom::variance(e_samples[i]) << "\n";
        std::cout << "effortless variability\t" << i << ": " << custom::variability(e_samples[i]) << "\n";
        std::cout << "effortless random?\t at " << significance << " : " << (custom::chi_squared_test(e_samples[i], eprng.min(), eprng.max(), significance, custom::DistributionType::UNIFORM_INT) ? "true" : "false") << "\n";
    }
    std::cout << "\n";
    for (unsigned i = 0; i < 10; ++i)
    {
        std::cout << "advanced mean\t" << i << ": " << custom::mean(a_samples[i]) << "\n";
        std::cout << "advanced variance\t" << i << ": " << custom::variance(a_samples[i]) << "\n";
        std::cout << "advanced variability\t" << i << ": " << custom::variability(a_samples[i]) << "\n";
        std::cout << "advanced random?\t at " << significance << " : " << (custom::chi_squared_test(a_samples[i], aprng.min(), aprng.max(), 0.1, custom::DistributionType::UNIFORM_INT) ? "true" : "false") << "\n";
    }
    std::cout << "\n";
    for (unsigned i = 0; i < 10; ++i)
    {
        std::cout << "mersenne-twister mean\t" << i << ": " << custom::mean(mt_samples[i]) << "\n";
        std::cout << "mersenne-twister variance\t" << i << ": " << custom::variance(mt_samples[i]) << "\n";
        std::cout << "mersenne-twister variability\t" << i << ": " << custom::variability(mt_samples[i]) << "\n";
        std::cout << "mersenne-twister random?\t at " << significance << " : " << (custom::chi_squared_test(mt_samples[i], mtprng.min(), mtprng.max(), 0.1, custom::DistributionType::UNIFORM_INT) ? "true" : "false") << "\n";
    }

    //timings
    std::vector<size_t> sizes = {1000, 112000, 223000, 334000, 445000, 556000, 667000, 778000, 889000, 1000000};
    std::map<std::string, std::vector<uint64_t>> results;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    for (size_t i : sizes)
    {
        std::cout << "Generating " << i
                  << " numbers...\n";
        start = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < i; ++j)
        {
            generated = eprng();
        }
        end = std::chrono::high_resolution_clock::now();
        results["Effortless"].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

        start = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < i; ++j)
        {
            generated = aprng();
        }
        end = std::chrono::high_resolution_clock::now();
        results["Advanced"].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

        start = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < i; ++j)
        {
            generated = mtprng();
        }
        end = std::chrono::high_resolution_clock::now();
        results["Mersenne-Twister"].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    }
    std::ofstream out("./../../../../timings.txt");
    out << "Sizes";
    for (auto i : sizes)
        out << "," << i;
    out << '\n';
    for (auto& i : results)
    {
        out << i.first;
        for (auto& j : i.second)
        {
            out << "," << j;
        }
        out << "\n";
    }
    return 0;
}
