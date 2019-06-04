#pragma once
#include <vector>
#include <array>

typedef std::array<char, 45> dbString;

// column based representation of the LINEITEM TPCH table

struct table {
    // lineitem table
    std::vector<uint64_t> l_orderkey; // id
    std::vector<uint64_t> l_partkey; // id
    std::vector<uint64_t> l_suppkey; // id
    std::vector<uint64_t> l_linenumber; // integer
    std::vector<uint64_t> l_quantity; // decimal
    std::vector<uint64_t> l_extendedprice; // decimal
    std::vector<uint64_t> l_discount; // decimal
    std::vector<uint64_t> l_tax; // decimal
    std::vector<char> l_returnflag; // fixed text, size 1
    std::vector<char> l_linestatus; // fixed text, size 1
    std::vector<uint64_t> l_shipdate; // date
    std::vector<uint64_t> l_commitdate; // date
    std::vector<uint64_t> l_receiptdate; // date
    std::vector<dbString> l_shipinstruct; // fixed text, size 25
    std::vector<dbString> l_shipmode; // fixed text, size 10
    std::vector<dbString> l_comment; // variable text size 44
};

table readFile(std::string filename, const char delim);
uint64_t parseInt(std::ifstream& file, const char delim);
dbString parseString(std::ifstream& file, const char delim);
char parseChar(std::ifstream& file, const char delim);
uint64_t parseDate(std::ifstream& file, const char delim);
