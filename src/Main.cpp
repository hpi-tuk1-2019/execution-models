#include "TableReader.h"
#include <string>

int main(int argc, char *argv[]) {
    std::string filename = "../../assets/sample_data/lineitem.tbl";
    char delim = '|';

    auto table = readFile(filename, delim);

    return 0;
}
