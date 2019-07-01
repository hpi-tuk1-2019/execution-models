#include "TableReader.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>


int parseInt(std::ifstream& file, const char delim) {
    std::string value;
    std::getline(file, value, delim);
    return std::stoi(value);
}

int parseDecimal(std::ifstream& file, const char delim){
    std::string value;
    std::getline(file, value, delim);
    double real_value = std::stod(value);
    return (int)(real_value * 100);
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

int parseDate(std::ifstream& file, const char delim) {
  std::string value;
  std::tm t = {};
  std::getline(file, value, delim);
  std::istringstream ss(value);
  ss >> std::get_time(&t, "%Y-%m-%d");
  int date = mktime(&t);
  return date;
}

table readFile(const std::string& filename, const char delim, int noLineItems)
{
    std::ifstream file(filename);
    table fileTable;

    if (!file.is_open()) {
        std::cout << "File cannot be opened";
        return fileTable;
    }


    // length of table and columntypes from lineitem.tbl
    for(int i = 0; i < noLineItems; ++i)
    {
        fileTable.l_orderkey.push_back(parseInt(file, delim));
        fileTable.l_partkey.push_back(parseInt(file, delim));
        fileTable.l_suppkey.push_back(parseInt(file, delim));
        fileTable.l_linenumber.push_back(parseInt(file, delim));
        fileTable.l_quantity.push_back(parseDecimal(file, delim));
        fileTable.l_extendedprice.push_back(parseDecimal(file, delim));
        fileTable.l_discount.push_back(parseDecimal(file, delim));
        fileTable.l_tax.push_back(parseDecimal(file, delim));
        fileTable.l_returnflag.push_back(parseChar(file, delim));
        fileTable.l_linestatus.push_back(parseChar(file, delim));
        fileTable.l_shipdate.push_back(parseDate(file, delim));
        fileTable.l_commitdate.push_back(parseDate(file, delim));
        fileTable.l_receiptdate.push_back(parseDate(file, delim));
        fileTable.l_shipinstruct.push_back(parseString(file, delim));
        fileTable.l_shipmode.push_back(parseString(file, delim));
        fileTable.l_comment.push_back(parseString(file, delim));
    }

    return fileTable;
}

partTable readPartFile(const std::string & filename, const char delim, int noLineItems)
{
    std::ifstream file(filename);
    partTable fileTable;

    if (!file.is_open()) {
        std::cout << "File cannot be opened";
        return fileTable;
    }

    // length of table and columntypes from lineitem.tbl
    for (int i = 0; i < noLineItems; ++i)
    {
        fileTable.p_partkey.push_back(parseInt(file, delim));
        fileTable.p_name.push_back(parseString(file, delim));
        fileTable.p_mfgr.push_back(parseString(file, delim));
        fileTable.p_brand.push_back(parseString(file, delim));
        fileTable.p_type.push_back(parseString(file, delim));
        fileTable.p_size.push_back(parseInt(file, delim));
        fileTable.p_container.push_back(parseString(file, delim));
        fileTable.p_retailPrice.push_back(parseDecimal(file, delim));
        fileTable.p_comment.push_back(parseString(file, delim));
    }
    return fileTable;
}
