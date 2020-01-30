// Sorting Technique.cpp : Defines the entry point for the application.
//

#include "Sorting Technique.h"
#include "./SQLiteCpp/SQLiteCpp.h"
#include "CampEntry.cpp"

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
    CampEntry cr(2000, 1, 1, "Igor", {1, 2, 1990});
    std::vector<CampEntry> scouts = read_from_db("data.sqlite", "user_details", 10);
    for (auto i : scouts)
    {
        std::cout << i << '\n';
    }
    std::cout << "Hello CMake.\n";
    return 0;
}
