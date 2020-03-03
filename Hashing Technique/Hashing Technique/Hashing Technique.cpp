// Hashing Technique.cpp : Defines the entry point for the application.
//

#include "Hashing Technique.h"
#include "CampEntryHash.hpp"
#include "HashTable.hpp"
#include "MyHashes.hpp"
#include "SQLiteCpp/SQLiteCpp.h"

std::vector<CampEntryHash> read_from_db(std::string database, std::string table, const size_t size)
{
    std::vector<CampEntryHash> result;
    result.reserve(size);
    Hasher hr(31, 10000 + 9);
    try
    {
        //Open a DB
        SQLite::Database db("./../../../../" + database);
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
            result.emplace_back(CampEntryHash(camp_year, troop, shift, first_name + " " + last_name, {b_day, b_day, b_year}, [&](CampEntry ce) { return hr.rot13_hash(ce.name()); }));
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
    std::vector<size_t> sizes = {100, 11200, 22300, 33400, 44500, 55600, 66700, 77800, 88900, 100000 - 1};
    std::vector<CampEntryHash> scouts = read_from_db("data.sqlite", "user_details", 100000 - 1);
    Hasher hr(31, 10000 + 9);
    custom::HashTable<std::string, CampEntryHash> table([&](std::string key) { return hr.better_hash(key); });
    for (CampEntryHash& ceh : scouts)
    {
        table.emplace(ceh.name(), ceh);
        //std::cout << ceh << "\n";
    }
    /*
    std::cout << hr.better_hash("Jon Doe") << '\n';
    CampEntryHash ceh(1900, 4, 2, "Jon Doe", {10, 1, 1890}, [&](CampEntry ce) { return hr.better_hash(ce.name()); });
    std::cout <<"Hash is: "<< ceh.hash() << "\n";
    std::cout << ceh <<"\n";*/

    //table.emplace(ceh.name(), ceh);
    return 0;
}
