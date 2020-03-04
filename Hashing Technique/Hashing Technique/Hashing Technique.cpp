// Hashing Technique.cpp : Defines the entry point for the application.
//

#include "Hashing Technique.h"
#include "CampEntryHash.hpp"
#include "HashTable.hpp"
#include "MyHashes.hpp"
#include "SQLiteCpp/SQLiteCpp.h"
static std::mt19937 prng(std::random_device {}());
constexpr unsigned namecount = 5;

std::vector<std::string> select_random_names(std::vector<CampEntryHash>::iterator begin, std::vector<CampEntryHash>::iterator end, int number)
{
    std::ptrdiff_t size = std::distance(begin, end);
    std::uniform_int_distribution<std::ptrdiff_t> dist(0, size - 1);
    std::vector<std::string> result;
    for (std::size_t i = 0; i < number; ++i)
        result.push_back(std::next(begin, dist(prng))->name());
    return result;
}


size_t count_collisions(std::vector<CampEntryHash>& data, std::function<size_t(std::string)> hash_f)
{
    std::vector<std::string> vals;
    vals.reserve(data.size());
    for (CampEntryHash& ceh : data)
    {
        vals.push_back(std::to_string(ceh.year()) + std::to_string(ceh.troop()) + std::to_string(ceh.shift()) + ceh.name() + std::to_string(ceh.date().bday) + std::to_string(ceh.date().bmonth) + std::to_string(ceh.date().byear));
    }
    std::vector<std::string>::iterator end_it = std::unique(vals.begin(), vals.end());
    vals.resize(static_cast<std::size_t>(std::distance(vals.begin(), end_it)));
    std::map<size_t, size_t> hashes;
    for (std::string& s : vals)
    {
        size_t h = hash_f(s);
        if (!hashes.count(h))
        {
            hashes[h] = 1;
        }
        else
        {
            ++hashes[h];
        }
    }
    size_t res = 0;
    for (auto& i : hashes)
    {
        if (i.second > 1)
        {
            res += i.second;
        }
    }
    return res;
}
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
    /*custom::HashTable<std::string, CampEntryHash> table_rot13([&](std::string key) { return hr.bad_hash(key); });
    for (CampEntryHash& ceh : scouts)
    {
        table_rot13.emplace(ceh.name(), ceh);
    }
    auto res = table_rot13.get("john");*/
    //Count collisions
    std::map<std::string, std::vector<double>> results_col;
    for (size_t i : sizes)
    {
        std::cout << "Counting collisions percentage for first " << i
                  << " rows...\n";
        std::vector<CampEntryHash> scouts_copy;
        std::copy(scouts.begin(), scouts.begin() + i,
            std::back_inserter(scouts_copy));
        results_col["Bad hash"].push_back(count_collisions(scouts_copy, [&](std::string key) { return hr.bad_hash(key); })*1./i);
        results_col["Rot13 hash"].push_back( count_collisions(scouts_copy, [&](std::string key) { return hr.rot13_hash(key); })*1./i);
        results_col["Rot19 hash"].push_back(count_collisions(scouts_copy, [&](std::string key) { return hr.rot19_hash(key); }) * 1. / i);
        results_col["Better hash"].push_back(count_collisions(scouts_copy, [&](std::string key) { return hr.better_hash(key); })*1./i);
    }
    //Get a list of names
    auto names = select_random_names(scouts.begin(), scouts.end(), namecount);
    //Time searches
    std::map<std::string, std::vector<uint64_t>> results_search;
    for (size_t i : sizes)
    {
        std::cout << "Timing for first " << i
                  << " rows...\n";
        std::vector<CampEntryHash> scouts_copy;
        std::copy(scouts.begin(), scouts.begin() + i,
            std::back_inserter(scouts_copy));
        custom::HashTable<std::string, CampEntryHash> table_bad_hash([&](std::string key) { return hr.bad_hash(key); });
        custom::HashTable<std::string, CampEntryHash> table_rot13([&](std::string key) { return hr.rot13_hash(key); });
        custom::HashTable<std::string, CampEntryHash> table_rot19([&](std::string key) { return hr.rot19_hash(key); });
        custom::HashTable<std::string, CampEntryHash> table_better_hash([&](std::string key) { return hr.better_hash(key); });
        for (CampEntryHash& ceh : scouts_copy)
        {
            table_bad_hash.emplace(ceh.name(), ceh);
            table_rot13.emplace(ceh.name(), ceh);
            table_rot19.emplace(ceh.name(), ceh);
            table_better_hash.emplace(ceh.name(), ceh);
        }
        std::vector<std::int64_t> timings_bad_hash, timings_rot13, timings_rot19, timings_better_hash;
        for (std::string name : names)
        {
            //Bad hash
            std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
            auto res1 = table_bad_hash.get(name);
            std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
            timings_bad_hash.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            //Rot13 hash
            start = std::chrono::high_resolution_clock::now();
            auto res2 = table_rot13.get(name);
            end = std::chrono::high_resolution_clock::now();
            timings_rot13.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            //Rot19 hash
            start = std::chrono::high_resolution_clock::now();
            auto res3 = table_rot19.get(name);
            end = std::chrono::high_resolution_clock::now();
            timings_rot19.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            //Better hash
            start = std::chrono::high_resolution_clock::now();
            auto res4 = table_better_hash.get(name);
            end = std::chrono::high_resolution_clock::now();
            timings_better_hash.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
        }
        results_search["Bad hash"].push_back(std::accumulate(timings_bad_hash.begin(), timings_bad_hash.end(), (std::int64_t)0) / namecount);
        results_search["Rot13 hash"].push_back(std::accumulate(timings_rot13.begin(), timings_rot13.end(), (std::int64_t)0) / namecount);
        results_search["Rot19 hash"].push_back(std::accumulate(timings_rot19.begin(), timings_rot19.end(), (std::int64_t)0) / namecount);
        results_search["Better hash"].push_back(std::accumulate(timings_better_hash.begin(), timings_better_hash.end(), (std::int64_t)0) / namecount);
    }

    /*std::cout << hr.better_hash("Jon Doe") << '\n';
    CampEntryHash ceh(1900, 4, 2, "Jon Doe", {10, 1, 1890}, [&](CampEntry ce) { return hr.better_hash(ce.name()); });
    std::cout <<"Hash is: "<< ceh.hash() << "\n";
    std::cout << ceh <<"\n";*/



    //Output results

    std::ofstream out("./../../../../collisions.txt");
    out << "Sizes";
    for (auto i : sizes)
        out << "," << i;
    out << '\n';
    for (auto& i : results_col)
    {
        out << i.first;
        for (auto& j : i.second)
        {
            out << "," << std::setprecision(5) << std::fixed << j;
        }
        out << "\n";
    }

    std::ofstream out2("./../../../../timings.txt");
    out2 << "Sizes";
    for (auto i : sizes)
        out2 << "," << i;
    out2 << '\n';
    for (auto& i : results_search)
    {
        out2 << i.first;
        for (auto& j : i.second)
        {
            out2 << "," << j;
        }
        out2 << "\n";
    }
    return 0;
}
