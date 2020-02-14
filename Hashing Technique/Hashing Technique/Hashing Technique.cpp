// Hashing Technique.cpp : Defines the entry point for the application.
//

#include "Hashing Technique.h"
#include "CampEntryHash.hpp"
#include "MyHashes.hpp"

int main()
{
    Hasher hr(31, 10000 + 9);
    std::cout << hr.better_hash("Jon Doe") << '\n';

    CampEntryHash ceh(1900, 4, 2, "Jon Doe", {10, 1, 1890}, [&](CampEntry ce) { return hr.better_hash(ce.name()); });
    std::cout <<"Hash is: "<< ceh.hash() << "\n";
    std::cout << "Hello CMake.\n";
    return 0;
}
