// PT_lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CampEntry.hpp"
#include <iostream>
#include <string>
#include <string_view>

static int callback(void* data, int argc, char** argv, char** azColName)
{
    std::string id(argv[0]);
    std::string fn(argv[1]);
    std::string ln(argv[2]);
    std::string yr(argv[3]);
    std::string bd(argv[4]);
    std::string bm(argv[5]);
    std::string by(argv[6]);
    std::string tp(argv[7]);
    std::string st(argv[8]);
    std::cout << CampEntry(std::stoi(yr), std::stoi(tp), std::stoi(st), fn + ' ' + ln, {std::stoi(bd), std::stoi(bm), std::stoi(by)}) << '\n';
    return 0;
}

int main()
{
    char* ptr = new char[10];
    for (std::size_t i = 0; i < 10; ++i)
        ptr[i] = 'a';
    std::string str(ptr, ptr + 10);
    std::cout << reinterpret_cast<const void*>(str.c_str()) << ' ' << reinterpret_cast<void*>(ptr);
    //CampEntry ce1(1999, 3, 1, "Jim Jones", {1, 10, 1990});
    //std::cout << "Hello World!\n";
    //std::cout << ce1 << "\n";

    //sqlite3* db;
    //char* zErrMsg = 0;
    //int rc;
    //const char* data = "Callback function called";

    ///* Open database */
    //rc = sqlite3_open("data.sqlite", &db);

    //if (rc)
    //{
    //    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    //    return (0);
    //}
    //else
    //{
    //    fprintf(stderr, "Opened database successfully\n");
    //}

    ///* Create SQL statement */
    //char sql[45] = "SELECT * from user_details";

    ///* Execute SQL statement */
    //rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    //if (rc != SQLITE_OK)
    //{
    //    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    //    sqlite3_free(zErrMsg);
    //}
    //else
    //{
    //    fprintf(stdout, "Operation done successfully\n");
    //}
    //sqlite3_close(db);
    //return 0;
}
