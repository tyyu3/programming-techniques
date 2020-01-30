// Sorting Technique.cpp : Defines the entry point for the application.
//

#include "Sorting Technique.h"
#include "./SQLiteCpp/SQLiteCpp.h"
#include "CampEntry.cpp"
using namespace std;

int main()
{
    CampEntry cr(2000, 1, 1, "Igor", {1, 2, 1990});
    try
    {
        SQLite::Database db("example.db3");
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
    cout << "Hello CMake." << endl;
    return 0;
}
