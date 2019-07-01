#include "StopWatch.h"
#include "QuerySix.h"
#include "QueryOne.h"
#include "QueryFourteen.h"
#include <string>
#include <iostream>
#include <chrono>

void print_char_array(const std::array<char, stringLegth>& char_array) {
    for (int i = 0; i < sizeof(char_array); i++) {
        std::cout << char_array[i];
    }
    std::cout << ", ";
}

void print_sample(const table& table_obj, const int sample_size = 20) {
    for (int i = 0; i < sample_size; i++) {
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

void print_res_q1(const ResultMap &res) {
    for (auto entry : res) {
        std::cout << entry.second.avg_disc << std::endl;
        break;
    }
}

int main(int argc, char *argv[]) {
	/*
    if (argc < 4) {
		std::cerr << "Usage: " << argv[0] << " <filepath> <#lineitems> <#executions>" << std::endl;
		return 1;
	}*/
	std::string filename = "../../assets/sample_data/lineitem.tbl";
    std::string partFilename = "../../assets/sample_data/part.tbl";
	int noLineItems = 6005;
	int noExecutions = 1;
    /*
	try {
		filename = argv[1];
		noLineItems = std::stoi(argv[2]);
		noExecutions = std::stoi(argv[3]);
	}
	catch (const std::exception & e) {
		std::cerr << "Usage: " << argv[0] << " <filepath> <#lineitems> <#executions>" << std::endl;
		return 1;
	}
    */
    char delim = '|';

    StopWatch reading = StopWatch("reading csv");
    StopWatch q1sw = StopWatch("query one normal");
    StopWatch q1sw1 = StopWatch("query one hyrbid");
    StopWatch q1sw2 = StopWatch("query one compiled");
    StopWatch q6sw = StopWatch("query six normal");
    StopWatch q6sw2 = StopWatch("query six hybrid");
    StopWatch q6sw1 = StopWatch("query six compiled");
    StopWatch q14sw = StopWatch("query fourteen normal");

    reading.tik();
    auto fileTable = readFile(filename, delim, noLineItems);
    auto partTable = readPartFile(partFilename, delim, 200);
    reading.tok();
    reading.print_stats();
    for (int i = 0; i < noExecutions; i++) {
        ResultMap resq1;
        QueryOne q1;
        q1sw.tik();
        resq1 = q1.execute(fileTable);
        q1sw.tok();
        print_res_q1(resq1);
        q1sw.print_stats();

        q1sw1.tik();
        resq1 = q1.execute_hybrid(fileTable);
        q1sw1.tok();
        print_res_q1(resq1);
        q1sw1.print_stats();

        q1sw2.tik();
        resq1 = q1.execute_compiled(fileTable);
        q1sw2.tok();
        print_res_q1(resq1);
        q1sw2.print_stats();

        double resq6;
        QuerySix q6;
        q6sw.tik();
        resq6 = q6.execute(fileTable);
        q6sw.tok();
        std::cout << resq6 << std::endl;
        q6sw.print_stats();

        q6sw2.tik();
        resq6 = q6.execute_hybrid(fileTable);
        q6sw2.tok();
        std::cout << resq6 << std::endl;
        q6sw2.print_stats();

        q6sw1.tik();
        resq6 = q6.execute_compiled(fileTable);
        q6sw1.tok();
        std::cout << resq6 << std::endl;
        q6sw1.print_stats();

        QueryFourteen q14;
        q14sw.tik();
        auto res14 = q14.execute(fileTable, partTable);
        std::cout << res14 << std::endl;
        q14sw.tok();
        q14sw.print_stats();
    }

    q1sw.write_to_file("q1_normal.csv");
    q1sw1.write_to_file("q1_hybrid.csv");
    q1sw2.write_to_file("q1_compiled.csv");
    q6sw.write_to_file("q6_normal.csv");
    q6sw1.write_to_file("q6_compiled.csv");
    q6sw2.write_to_file("q6_hybrid.csv");

    return 0;
}
