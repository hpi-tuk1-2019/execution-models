#pragma once
#include "StopWatch.h"
#include "QuerySix.h"
#include "QueryOne.h"
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
	reading.write_to_file("benchmark_reading.csv");

	auto q = QuerySix();
	StopWatch normal = StopWatch("normal execution");
	for(int i=0;i<100;i++) {
		normal.tik();
		q.execute(fileTable);
		normal.tok();
	}
	normal.write_to_file("benchmark_normal.csv");

	StopWatch compiled = StopWatch("compiled execution");
	for (int i = 0; i < 100; i++) {
		compiled.tik();
		q.execute_compiled(fileTable);
		compiled.tok();
	}
	compiled.write_to_file("benchmark_compiled.csv");

    return 0;
}
