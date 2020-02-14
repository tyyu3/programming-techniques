#pragma once
#include <string>

class CampEntry
{
public:
    struct Bday
    {
        int bday;
        int bmonth;
        int byear;
    };

    using Year = int;
    using Troop = int;
    using Shift = int;
    using Name = std::string;

    CampEntry() = delete;
    CampEntry(Year year, Troop troop, Shift shift, Name name, Bday bday)
        : year_(year)
        , troop_(troop)
        , shift_(shift)
        , name_(std::move(name))
        , bday_(bday)
    {
    }

    CampEntry(const CampEntry&) = default;
    CampEntry& operator=(const CampEntry&) = default;
    CampEntry(CampEntry&&) = default;
    CampEntry& operator=(CampEntry&&) = default;

    [[nodiscard]] Year year() const { return year_; }
    [[nodiscard]] Troop troop() const { return troop_; }
    [[nodiscard]] Shift shift() const { return shift_; }
    [[nodiscard]] Name name() const { return name_; }
    [[nodiscard]] Bday date() const { return bday_; }

    friend bool operator==(const CampEntry& lhs, const CampEntry& rhs);
    friend bool operator!=(const CampEntry& lhs, const CampEntry& rhs);
    friend bool operator<(const CampEntry& lhs, const CampEntry& rhs);
    friend bool operator>(const CampEntry& lhs, const CampEntry& rhs);
    friend bool operator<=(const CampEntry& lhs, const CampEntry& rhs);
    friend bool operator>=(const CampEntry& lhs, const CampEntry& rhs);
    friend std::ostream& operator<<(std::ostream& stream, const CampEntry& campentry);

private:
    Year year_;
    Troop troop_;
    Shift shift_;
    Name name_;
    Bday bday_;
};