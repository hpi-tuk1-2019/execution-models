#pragma once
#include "StopWatch.h"
#include "QuerySix.h"
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

int touch_all_values(const table& tab){
  int a = 0;
  for (int i = 0; i < tab.l_discount.size(); i++) {
    if ((tab.l_discount[i]) <= 7) {
      a++;
    }
  }
  return a;
}


int main(int argc, char *argv[]) {
    // use to check size of an int on your machine
    // std::cout << sizeof(int) << std::endl;
    std::string filename = "../../assets/sample_data/lineitem.tbl";
    char delim = '|';

    StopWatch reading = StopWatch("reading csv");
    reading.tik();
    auto fileTable = readFile(filename, delim);
    reading.tok();

    StopWatch mem_bandwidth = StopWatch("Touch all values (memory bandwidth measurement)");
    mem_bandwidth.tik();
    int a = touch_all_values(fileTable);
    mem_bandwidth.tok();
    std::cout << a;

    mem_bandwidth.print_stats();

	auto q = QuerySix();
	std::cout << q.execute(fileTable) << std::endl;

    int b = 0;
    std::cin >> b;

    return 0;
}
