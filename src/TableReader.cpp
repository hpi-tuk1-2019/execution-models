#include "TableReader.h"

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>


int parseInt(std::ifstream& file, const char delim) {
    std::string value;
    std::getline(file, value, delim);
    return std::stoi(value);
}

dbString parseString(std::ifstream& file, const char delim) {
    std::string fileValue;
    dbString dbValue;
    std::getline(file, fileValue, delim);
    fileValue.copy(&dbValue[0], fileValue.length());
    return dbValue;
}

char parseChar(std::ifstream& file, const char delim) {
    std::string value;
    std::getline(file, value, delim);
    if (value.length() != 1) {
        std::cout << "This is not a char column, something went wrong";
    }
    return value.front();
}

table readFile(std::string filename, const char delim)
{
    std::ifstream file(filename);
    table fileTable;
    
    if (!file.is_open()) {
        std::cout << "File cannot be opened";
        return fileTable;
    }

    while (!file.eof())
    {
        fileTable.l_orderkey.push_back(parseInt(file, delim));
        fileTable.l_partkey.push_back(parseInt(file, delim));
        fileTable.l_suppkey.push_back(parseInt(file, delim));
        fileTable.l_linenumber.push_back(parseInt(file, delim));
        fileTable.l_quantity.push_back(parseInt(file, delim));
        fileTable.l_extendedprice.push_back(parseInt(file, delim));
        fileTable.l_discount.push_back(parseInt(file, delim));
        fileTable.l_tax.push_back(parseInt(file, delim));
        fileTable.l_returnflag.push_back(parseChar(file, delim));
        fileTable.l_linestatus.push_back(parseChar(file, delim));
        fileTable.l_shipdate.push_back(parseInt(file, delim));
        fileTable.l_commitdate.push_back(parseInt(file, delim));
        fileTable.l_receiptdate.push_back(parseInt(file, delim));
        fileTable.l_shipinstruct.push_back(parseString(file, delim));
        fileTable.l_shipmode.push_back(parseString(file, delim));
        fileTable.l_comment.push_back(parseString(file, delim));
    }
    
    return fileTable;
}

