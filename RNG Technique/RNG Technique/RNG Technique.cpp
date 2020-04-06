// RNG Technique.cpp : Defines the entry point for the application.
//

#include "RNG Technique.h"
#include "RandomFunctions.hpp"
#include "ChiSquared.hpp"

int main()
{
    custom::EffortlessPRNG eprng(1);
    for (int i = 0; i < 3;++i)
    {
        std::cout << eprng() <<"\n";
    }
    std::cout << "Hello CMake.\n";
    std::vector<double> test = {0, 1, 2, 3, 4};
    std::cout<<custom::chi_squared(test, 0., 5., custom::DistributionType::UNIFORM_REAL).first<<"\n";
    return 0;
}
