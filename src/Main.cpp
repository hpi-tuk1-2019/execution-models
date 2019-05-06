#include "Scan.h"
#include <string>
#include <chrono>
#include "StopWatch.h"

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

    return 0;
}
