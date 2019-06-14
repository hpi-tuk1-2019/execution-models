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
    std::string filename = "../../assets/sample_data2/lineitem.tbl";
    char delim = '|';

    StopWatch reading = StopWatch("reading csv");
		StopWatch q1sw = StopWatch("query one normal");
		StopWatch q1sw1 = StopWatch("query one hyrbid");
		StopWatch q1sw2 = StopWatch("query one compiled");
		StopWatch q6sw = StopWatch("query six normal");
		StopWatch q6sw2 = StopWatch("query six hybrid");
		StopWatch q6sw1 = StopWatch("query six compiled");

    reading.tik();
    auto fileTable = readFile(filename, delim);
    reading.tok();
    reading.print_stats();
		for (int i = 0; i < 10; i++) {
			QueryOne q1;
	    q1sw.tik();
	    q1.execute(fileTable);
	    q1sw.tok();
	    q1sw.print_stats();

     	q1sw1.tik();
     	q1.execute_hybrid(fileTable);
     	q1sw1.tok();
     	q1sw1.print_stats();

     	q1sw2.tik();
     	q1.execute_compiled(fileTable);
     	q1sw2.tok();
     	q1sw2.print_stats();

     	QuerySix q6;
     	q6sw.tik();
     	q6.execute(fileTable);
     	q6sw.tok();
     	q6sw.print_stats();

     	q6sw2.tik();
     	q6.execute_hybrid(fileTable);
     	q6sw2.tok();
     	q6sw2.print_stats();

     	q6sw1.tik();
     	q6.execute_compiled(fileTable);
     	q6sw1.tok();
     	q6sw1.print_stats();
		}
		q1sw.write_to_file("q1_normal.csv");
		q1sw1.write_to_file("q1_hybrid.csv");
		q1sw2.write_to_file("q1_compiled.csv");
		q6sw.write_to_file("q6_normal.csv");
		q6sw.write_to_file("q6_compiled.csv");
		q6sw.write_to_file("q6_hybrid.csv");


    return 0;
}
