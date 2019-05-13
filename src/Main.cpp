#pragma once
#include "Scan.h"
#include "StopWatch.h"
#include <string>
#include <iostream>
#include <chrono>

void print_char_array(std::array<char, 45> char_array) {
	for (int i = 0; i < sizeof(char_array); i++) {
		std::cout << char_array[i];
	}
	std::cout <<  ", ";
}

void print_sample(table table_obj, int sample_size = 20) {
    for (int i = 0; i < sample_size; i++){
        std::cout << table_obj.l_orderkey.at(i) << ", ";
        std::cout << table_obj.l_partkey.at(i) << ", ";
        std::cout << table_obj.l_suppkey.at(i) << ", ";
        std::cout << table_obj.l_linenumber.at(i) << ", ";
        std::cout << table_obj.l_quantity.at(i) << ", ";
        std::cout << table_obj.l_extendedprice.at(i) << ", ";
        std::cout << table_obj.l_discount.at(i) << ", ";
        std::cout << table_obj.l_tax.at(i) << ", ";
        std::cout << table_obj.l_returnflag.at(i) << ", ";
        std::cout << table_obj.l_linestatus.at(i) << ", ";
        std::cout << table_obj.l_shipdate.at(i) << ", ";
        std::cout << table_obj.l_commitdate.at(i) << ", ";
        std::cout << table_obj.l_receiptdate.at(i) << ", ";

        print_char_array(table_obj.l_shipinstruct.at(i));
        print_char_array(table_obj.l_shipmode.at(i));
        print_char_array(table_obj.l_comment.at(i));
        std::cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    std::string filename = "../../assets/sample_data/lineitem.tbl";
    char delim = '|';
		
    StopWatch reading = StopWatch("reading csv");
    reading.tik();
    auto fileTable = readFile(filename, delim);
    reading.tok();
    reading.print_stats();
  
    StopWatch scan = StopWatch("scan table");
    scan.tik();
    auto newTable = filterValuesSmaller(fileTable, fileTable.l_receiptdate, 1996);
    scan.tok();
    scan.print_stats();
    scan.write_to_file("../../data/test.csv");

    print_sample(newTable);

    return 0;
}
