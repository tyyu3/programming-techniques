// Design Pattern Technique II.cpp : Defines the entry point for the application.
//

#include "Design Pattern Technique II.h"
#include "Multigen.hpp"

using namespace std;

int main()
{
    strategy::IntGenerator client;
    std::vector<int> res;

    std::cout << "current engine type is:\n";
    client.PrintName();
    std::cout << "\n";
    client.set_generator(std::unique_ptr<strategy::GenStrategy>(new strategy::GenStrategyLC));
    std::cout << "current engine type is:\n";
    client.PrintName();
    res = client.gen(-1,3,10);
    for (int i : res)
        std::cout << i << " ";
    res.clear();
    std::cout << "\n";

    client.set_generator(std::unique_ptr<strategy::GenStrategy>(new strategy::GenStrategyMT));
    std::cout << "current engine type is:\n";
    client.PrintName();
    res = client.gen(-3, 3, 10);
    for (int i : res)
        std::cout << i << " ";
    res.clear();
    std::cout << "\n";

    client.set_generator(std::unique_ptr<strategy::GenStrategy>(new strategy::GenStrategySC));
    std::cout << "current engine type is:\n";
    client.PrintName();
    res = client.gen(-3, 3, 10);
    for (int i : res)
        std::cout << i << " ";
    res.clear();
    std::cout << "\n";
	return 0;
}
