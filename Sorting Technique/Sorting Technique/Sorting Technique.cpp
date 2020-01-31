// Sorting Technique.cpp : Defines the entry point for the application.
//

#include "Sorting Technique.h"
#include "./SQLiteCpp/SQLiteCpp.h"
#include "CampEntry.cpp"
#include "Selection Sort.hpp"
#include "Insertion Sort.hpp"

std::vector<CampEntry> read_from_db(std::string database, std::string table, const size_t size)
{
    std::vector<CampEntry> result;
    result.reserve(size);
    try
    {
        //Open a DB
        SQLite::Database db("data.sqlite");
        // Create an SQL query with one parameter.
        SQLite::Statement query(db, "SELECT * FROM " + table + " LIMIT ?");
        // Set parameter to size
        query.bind(1, static_cast<unsigned>(size));
        while (query.executeStep())
        {
            std::string first_name  = query.getColumn(1);
            std::string last_name   = query.getColumn(2);
            int camp_year           = query.getColumn(3);
            int b_day               = query.getColumn(4);
            int b_month             = query.getColumn(5);
            int b_year              = query.getColumn(6);
            int troop               = query.getColumn(7);
            int shift               = query.getColumn(8);
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
    std::vector<CampEntry> scouts = read_from_db("data.sqlite", "user_details", 20);
    for (auto i : scouts)
    {
        std::cout << i << '\n';
    }
    std::cout << "\nSorted:\n";
    std::vector<CampEntry> scouts_copy;
    std::copy(scouts.begin(), scouts.end(),
        std::back_inserter(scouts_copy));
    custom::insertion_sort(scouts_copy.begin(), scouts_copy.end(), [](const CampEntry& lhs, const CampEntry& rhs) { return lhs > rhs; });
    for (auto i : scouts_copy)
    {
        std::cout << i << '\n';
    }
    return 0;
}
