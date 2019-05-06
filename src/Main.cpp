#include "Scan.h"
#include <string>

int main(int argc, char *argv[]) {
    std::string filename = "../../assets/sample_data/lineitem.tbl";
    char delim = '|';

    table fileTable = readFile(filename, delim);

    auto newTable = filterValuesSmaller(fileTable, fileTable.l_receiptdate, 1996);

    return 0;
}
