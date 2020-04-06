#include "CampEntry.hpp"
#include <ostream>

#include <utility>

bool operator==(const CampEntry& lhs, const CampEntry& rhs)
{
    return std::tie(lhs.year_, lhs.troop_, lhs.shift_, lhs.name_) ==
        std::tie(rhs.year_, rhs.troop_, rhs.shift_, rhs.name_);
}

bool operator<(const CampEntry& lhs, const CampEntry& rhs)
{
    return std::tie(lhs.year_, lhs.troop_, lhs.shift_, lhs.name_) < std::tie(rhs.year_, rhs.troop_, rhs.shift_, rhs.name_);
}

bool operator<=(const CampEntry& lhs, const CampEntry& rhs)
{
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const CampEntry& lhs, const CampEntry& rhs)
{
    return !(lhs <= rhs);
}

bool operator>=(const CampEntry& lhs, const CampEntry& rhs)
{
    return !(lhs < rhs);
}

bool operator!=(const CampEntry& lhs, const CampEntry& rhs)
{
    return !(lhs < rhs);
} 

std::ostream& operator<<(std::ostream& stream, const CampEntry& entry)
{
    stream << entry.year_ << '/' << entry.troop_ << '/'
           << entry.shift_ << '/'
           << entry.name_ << '/'
           << entry.bday_.bday << '.' << entry.bday_.bmonth << '.' << entry.bday_.byear;
    return stream;
}

