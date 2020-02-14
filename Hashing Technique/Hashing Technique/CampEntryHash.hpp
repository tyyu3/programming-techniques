#pragma once
#include "CampEntry.hpp"
#include <functional>

class CampEntryHash : public CampEntry
{
public:
    using HashFunction = std::function<size_t(CampEntry)>;
    CampEntryHash(Year year, Troop troop, Shift shift, Name name, Bday bday, HashFunction h_f)
        : CampEntry(year, troop, shift, name, bday)
        , hash_function {std::move(h_f)}
    {
        hash_ = hash_function(*this);
    }

    HashFunction hash_function;
    [[nodiscard]] size_t hash() const { return hash_; }

private:
    size_t hash_;
};