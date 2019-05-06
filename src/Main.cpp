#include "TableReader.h"
#include <string>
#include <chrono>
#include "StopWatch.h"

int main(int argc, char *argv[]) {
    std::string filename = "../../assets/sample_data/lineitem.tbl";
    char delim = '|';
    StopWatch reading = StopWatch("reading csv");
    reading.tik();
    auto table = readFile(filename, delim);
    reading.tok();
    reading.print_stats();
    return 0;
}
