/**
 * @file
 * @brief Заголовочный файл, содержащий описание двух
 * собственных алгоритмов генерации псевдослучайных чисел
 * @date Март 2020
*/
#pragma once
#include <cstdint>

namespace custom
{
	class EffortlessPRNG
	{
    public:
        using result_type = std::uint32_t;
        EffortlessPRNG(result_type seed);
        static result_type min();
        static result_type max();

        result_type operator()();
    private:
        result_type inner_seed = 1;
	};
	class AdvancedPRNG
	{
    public:
        using result_type = std::uint32_t;
        AdvancedPRNG(result_type seed);
        static result_type min();
        static result_type max();

        result_type operator()();

    private:
        result_type inner_seed = 1;
    };
}