#include "RandomFunctions.hpp"
#include <limits>

namespace custom
{
    EffortlessPRNG::EffortlessPRNG(EffortlessPRNG::result_type seed)
        : inner_seed(seed)
    {
    }

    EffortlessPRNG::result_type EffortlessPRNG::operator()()
    {
        inner_seed = inner_seed*3;
        return inner_seed;
    }

    EffortlessPRNG::result_type EffortlessPRNG::min()
    {
        return std::numeric_limits<EffortlessPRNG::result_type>::min();
    }

    EffortlessPRNG::result_type EffortlessPRNG::max()
    {
        return std::numeric_limits<EffortlessPRNG::result_type>::max();
    }
    AdvancedPRNG::AdvancedPRNG(AdvancedPRNG::result_type seed)
        : inner_seed(seed)
    {
    }

    AdvancedPRNG::result_type AdvancedPRNG::operator()()
    {
        inner_seed = (inner_seed >> 3);
        inner_seed *= 41;
        inner_seed -= 31;
        inner_seed += (inner_seed << 2);
        return inner_seed;
    }

    AdvancedPRNG::result_type AdvancedPRNG::min()
    {
        return std::numeric_limits<AdvancedPRNG::result_type>::min();
    }

    AdvancedPRNG::result_type AdvancedPRNG::max()
    {
        return std::numeric_limits<AdvancedPRNG::result_type>::max();
    }
    }