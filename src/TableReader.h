#pragma once
#include <vector>
#include <array>

typedef std::array<char, 45> dbString;

// column based representation of the LINEITEM TPCH table

struct table {
    // lineitem table
    std::vector<int> l_orderkey; // id
    std::vector<int> l_partkey; // id
    std::vector<int> l_suppkey; // id
    std::vector<int> l_linenumber; // integer
    std::vector<int> l_quantity; // decimal
    std::vector<int> l_extendedprice; // decimal
    std::vector<int> l_discount; // decimal
    std::vector<int> l_tax; // decimal
    std::vector<char> l_returnflag; // fixed text, size 1
    std::vector<char> l_linestatus; // fixed text, size 1
    std::vector<int> l_shipdate; // date
    std::vector<int> l_commitdate; // date
    std::vector<int> l_receiptdate; // date
    std::vector<dbString> l_shipinstruct; // fixed text, size 25
    std::vector<dbString> l_shipmode; // fixed text, size 10
    std::vector<dbString> l_comment; // variable text size 44
};

struct partTable {
    std::vector<int> p_partkey;
    std::vector<dbString> p_name;
    std::vector<dbString> p_mfgr;
    std::vector<dbString> p_brand;
    std::vector<dbString> p_type;
    std::vector<int> p_size;
    std::vector<dbString> p_container;
    std::vector<int> p_retailPrice;
    std::vector<dbString> p_comment;
};

table readFile(const std::string& filename, const char delim, int noLineItems);
partTable readPartFile(const std::string& filename, const char delim, int noLineItems);

int parseInt(std::ifstream& file, const char delim);
dbString parseString(std::ifstream& file, const char delim);
char parseChar(std::ifstream& file, const char delim);
int parseDate(std::ifstream& file, const char delim);


