#include "Search Technique.h"
#include "CampEntry.cpp"
#include "LinearSearch.hpp"
#include "SQLiteCpp/SQLiteCpp.h"

#ifndef NDEBUG
#include "SearchTests.hpp"
#endif // NDEBUG


using namespace std;

std::vector<CampEntry> read_from_db(std::string database, std::string table, const size_t size)
{
    std::vector<CampEntry> result;
    result.reserve(size);
    try
    {
        //Open a DB
        SQLite::Database db("./../../../../" + database);
        // Create an SQL query with one parameter.
        SQLite::Statement query(db, "SELECT * FROM " + table  + " LIMIT ?");
        // Set parameter to size
        query.bind(1, static_cast<unsigned>(size));
        while (query.executeStep())
        {
            std::string first_name = query.getColumn(1);
            std::string last_name = query.getColumn(2);
            int camp_year = query.getColumn(3);
            int b_day = query.getColumn(4);
            int b_month = query.getColumn(5);
            int b_year = query.getColumn(6);
            int troop = query.getColumn(7);
            int shift = query.getColumn(8);
            result.emplace_back(CampEntry(camp_year, troop, shift, first_name + " " + last_name, {b_day, b_day, b_year}));
        }
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
    return result;
}

int main()
{
#ifndef  NDEBUG
    linear::test_linear();
    binary::test_binary();
#endif // NDEBUG
    std::map<std::string, std::vector<std::int64_t>> results;
    std::vector<size_t> sizes = {100, 11200, 22300, 33400, 44500, 55600, 66700, 77800, 88900, 100000-1};
    std::vector<CampEntry> scouts = read_from_db("data.sqlite", "user_details", 100000-1);
    std::cout << scouts.size()<<" is size\n";
    for (size_t i : sizes)
    {
        std::cout << "Timing for first " << i
                  << " rows...\n";
        std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
        custom::linear_search(scouts.begin(), scouts.begin()+i, "morgan wright", [](CampEntry lhs, std::string rhs) { return lhs.name() == rhs; });
        std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
        results["Linear Search"].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

        /*std::vector<CampEntry> scouts_copy_insertion;
        scouts_copy_insertion.reserve(i);
        std::copy(scouts.begin(), scouts.begin() + i,
            std::back_inserter(scouts_copy_insertion));
        start = std::chrono::high_resolution_clock::now();
        custom::insertion_sort(scouts_copy_insertion.begin(), scouts_copy_insertion.end());
        end = std::chrono::high_resolution_clock::now();
        results["Insertion sort"].push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());*/
    }
    //reuslts
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
