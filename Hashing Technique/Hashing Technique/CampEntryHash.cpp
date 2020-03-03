#include "CampEntryHash.hpp"
#include <iostream>
std::ostream& operator<<(std::ostream& stream, const CampEntryHash& entry)
{
    stream << static_cast<const CampEntry&>(entry);
    stream << "/" << entry.hash_;
    //stream << "X" << "/";
    return stream;
}