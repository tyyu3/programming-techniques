#pragma once
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

namespace custom
{
template <typename Key, typename T>
class HashTable
{
public:
    using HashFunction = std::function<size_t(Key)>;
    HashTable(HashFunction h_f)
        : hash_function(h_f)
    {
    }
    std::list<T> get(const Key& key)
    {
        size_t hash = hash_function(key);
        if (table.at(hash % table.size()).empty())
        {
            return {};
        }
        Bucket& bucket = table[hash % table.size()];
        for (SameName& sn : bucket)
        {
            if (sn.first == key)
                return sn.second;
        }
        return {};
    }

    void emplace(const Key& key, T val)
    {
        std::list<T> l {val};
        emplace(key, l);
    }
    void emplace(const Key& key, std::list<T> vals)
    {
        size_t hash = hash_function(key);
        Bucket& bucket = table[hash % table.size()];
        bool emplaced = false;
        for (SameName& sn : bucket)
        {
            if (sn.first == key)
            {
                for (T& val : vals)
                {
                    sn.second.emplace_back(std::move(val));
                }
                return;
            }
        }
        if (bucket.size() != max_bucket)
        {
            if (bucket.empty())
                ++buckets_taken;
            bucket.emplace_back(std::make_pair(key, std::move(vals)));
        }
        else
        {
            rehash();
            emplace(key, vals);
        }
    }

    void rehash()
    {

        std::size_t new_size, new_max_bucket;
        if (buckets_taken * 7 > table.size())
        {
            new_size = table.size() * 2;
            new_max_bucket = 3;
        }
        else
        {
            new_size = table.size();
            new_max_bucket = max_bucket + 1;
        }
#ifndef NDEBUG
        std::cerr << "Rehash: " << table.size() << ", " << max_bucket
                  << " --> " << new_size << ", " << new_max_bucket << std::endl;
#endif // !NDEBUG
        HashTable new_table(hash_function);
        new_table.max_bucket = new_max_bucket;
        new_table.table.resize(new_size);
        for (Bucket& bucket : table)
            for (SameName& sn : bucket)
                new_table.emplace(sn.first, sn.second);
        std::swap(*this, new_table);
    }
    size_t size()
    {
        return table.size();
    }

    size_t count_collisions()
    {
        size_t res = 0;
        for (Bucket& bucket : table)
        {
            size_t s = bucket.size();
            if (s > 1)
            {
                res += s;
            }
        }
        return res;
    }

private:
    using SameName = std::pair<Key, std::list<T>>;
    using Bucket = std::list<SameName>;
    std::vector<Bucket> table = std::vector<Bucket>(11);

    size_t max_bucket = 3;
    size_t buckets_taken = 0;

    HashFunction hash_function;
};

}