// Hashing Technique.cpp : Defines the entry point for the application.
//

#include "Hashing Technique.h"
#include "CampEntryHash.hpp"
#include "MyHashes.hpp"

int main()
{
    Hasher hr(31, 100000000 + 9);
    std::cout << hr.better_hash("aaaaa") << '\n';

    CampEntryHash ceh(1900, 4, 2, "Jon Doe!", {10, 1, 1890}, [](CampEntry ce) { return ce.name().length(); });
    std::cout <<"Hash is: "<< ceh.hash() << "\n";
    std::cout << "Hello CMake.\n";
    return 0;
}
