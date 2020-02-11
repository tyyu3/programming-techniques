#include "Search Technique.h"
#include "BinarySearch.hpp"
#include "CampEntry.cpp"
#include "Insertion Sort.hpp"
#include "LinearSearch.hpp"
#include "SQLiteCpp/SQLiteCpp.h"

#ifndef NDEBUG
#include "SearchTests.hpp"
#endif // NDEBUG
constexpr uint64_t namecount = 1;
static std::mt19937 prng(std::random_device {}());

std::vector<std::string> select_random_names(std::vector<CampEntry>::iterator begin, std::vector<CampEntry>::iterator end, int number)
{
    std::ptrdiff_t size = std::distance(begin, end);
    std::uniform_int_distribution<std::ptrdiff_t> dist(0, size - 1);
    std::vector<std::string> result;
    for (std::size_t i = 0; i < number; ++i)
        result.push_back(std::next(begin, dist(prng))->name());
    return result;
}

std::vector<CampEntry> read_from_db(std::string database, std::string table, const size_t size)
{
    std::vector<CampEntry> result;
    result.reserve(size);
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
#ifndef NDEBUG
    linear::test_linear();
    binary::test_binary();
#endif // NDEBUG
    std::map<std::string, std::vector<std::int64_t>> results;
    std::vector<size_t> sizes = {100, 11200, 22300, 33400, 44500, 55600, 66700, 77800, 88900, 100000 - 1};
    std::vector<CampEntry> scouts = read_from_db("data.sqlite", "user_details", 100000 - 1);
    //std::cout << scouts.size() << " is size\n";

    auto names = select_random_names(scouts.begin(), scouts.end(), namecount);
    std::vector<std::vector<CampEntry>::iterator> searchres1, searchres2, searchres3;

    std::multimap<std::string, CampEntry> m_map;
    for (auto& i : scouts)
    {
        m_map.insert(std::pair<std::string, CampEntry>(i.name(), i));
    }


    for (size_t i : sizes)
    {
        std::cout << "Timing for first " << i
                  << " rows...\n";
        //Linear Search
        std::vector<std::int64_t> timings;
        for (std::string name : names)
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
            searchres1 = custom::linear_search(scouts.begin(), scouts.begin() + i, name, [](CampEntry lhs, std::string rhs) { return lhs.name() == rhs; });
            std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
            timings.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            //std::cout << "S1 size" << searchres1.size() << "\n";
        }
        results["Linear Search"].push_back(std::accumulate(timings.begin(), timings.end(), (std::int64_t)0) / namecount);
        timings.clear();
        //
        //Binary Search Presorted
        std::vector<CampEntry> scouts_copy_binary_presorted;
        scouts_copy_binary_presorted.reserve(i);
        std::copy(scouts.begin(), scouts.begin() + i,
            std::back_inserter(scouts_copy_binary_presorted));
        std::sort(scouts_copy_binary_presorted.begin(), scouts_copy_binary_presorted.end(), [](CampEntry lhs, CampEntry rhs) { return lhs.name() < rhs.name(); });
        for (std::string name : names)
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
            searchres2 = custom::binary_search(
                scouts_copy_binary_presorted.begin(), scouts_copy_binary_presorted.end(), name, [](std::string lhs, std::string rhs) { return lhs < rhs; }, [](const CampEntry& elem) { return elem.name(); });
            std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
            timings.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            //std::cout << "S2 size" << searchres2.size() << "\n";
        }
        results["Presorted Binary Search"].push_back(std::accumulate(timings.begin(), timings.end(), (std::int64_t)0) / namecount);
        timings.clear();
        //
        //Binary Search with sort
        std::vector<CampEntry> scouts_copy_binary;
        scouts_copy_binary.reserve(i);
        for (std::string name : names)
        {
            std::copy(scouts.begin(), scouts.begin() + i,
                std::back_inserter(scouts_copy_binary));
            std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
            custom::insertion_sort(scouts_copy_binary.begin(), scouts_copy_binary.end(), [](CampEntry lhs, CampEntry rhs) { return lhs.name() < rhs.name(); });
            searchres3 = custom::binary_search(
                scouts_copy_binary.begin(), scouts_copy_binary.end(), name, [](std::string lhs, std::string rhs) { return lhs < rhs; }, [](const CampEntry& elem) { return elem.name(); });
            std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
            timings.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            scouts_copy_binary.clear();
            scouts_copy_binary.reserve(i);
            //std::cout << "S3 size" << searchres3.size()<<"\n";
        }
        results["Sort & Binary Search"].push_back(std::accumulate(timings.begin(), timings.end(), (std::int64_t)0) / namecount);
        timings.clear();
        //
        //Multimap
        for (std::string name : names)
        {
            std::vector<std::multimap<std::string, CampEntry>::iterator> found;
            std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
            auto range = m_map.equal_range(name);
            for (auto it = range.first; it != range.second; ++it)
            {
                found.push_back(it);
            }
            std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
            timings.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
            found.clear();
        }
        results["Multimap"].push_back(std::accumulate(timings.begin(), timings.end(), (std::int64_t)0) / namecount);
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
