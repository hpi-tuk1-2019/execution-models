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
  
    reading.tik();
    auto newTable = filterValuesSmaller(fileTable, fileTable.l_receiptdate, 1996);
    reading.tok();
    reading.print_stats();

    return 0;
}
