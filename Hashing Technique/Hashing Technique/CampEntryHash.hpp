#pragma once
#include "CampEntry.hpp"

class CampEntryHash : public CampEntry
{
public:
    CampEntryHash(Year year, Troop troop, Shift shift, Name name, Bday bday, size_t (*hash_func)(CampEntry))
        : CampEntry(year, troop, shift, name, bday)
        , hash_function(hash_func)
    {
        hash_ = hash_function(*this);
    }

    size_t (*hash_function)(CampEntry);
    [[nodiscard]] size_t hash() const { return hash_; }

private:
    size_t hash_;
};