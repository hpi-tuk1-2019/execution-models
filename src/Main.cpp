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

    auto q1 = QueryOne();
    StopWatch queryOne = StopWatch("queryOne");
    queryOne.tik();
    auto result1 = q1.execute(fileTable);
    queryOne.tok();
    queryOne.print_stats();

    StopWatch queryOneCompiled = StopWatch("queryOne compiled");
    queryOneCompiled.tik();
    auto result2 = q1.execute_compiled(fileTable);
    queryOneCompiled.tok();
    queryOneCompiled.print_stats();

    StopWatch queryOneHybrid = StopWatch("queryOne hybrid");
    queryOneHybrid.tik();
    auto result3 = q1.execute_hybrid(fileTable);
    queryOneHybrid.tok();
    queryOneHybrid.print_stats();

    for (auto& row : result1) {
        std::cout << row.second.count_order << " ";
    }
    std::cout << std::endl;
    for (auto& row : result2) {
        std::cout << row.second.count_order << " ";
    }
    std::cout << std::endl;
    for (auto& row : result3) {
        std::cout << row.second.count_order << " ";
    }

    int a;
    std::cin >> a;
    return 0;
}
