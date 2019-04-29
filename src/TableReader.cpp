#include "TableReader.h"

#include <string>
#include <fstream>

table readFile(std::string filename) {
    std::ifstream file(filename);

    table fileTable;
    
    if (file.is_open())
    {
        std::string value;
        while (!file.eof())
        {
            // col1
            std::getline(file, value, ',');
            int col1Value = std::stoi(value);
            fileTable.col1.push_back(col1Value);

            // col2
            std::getline(file, value, ',');

            dbString col2Value;
            std::copy(value.begin(), value.end(), col2Value);
            fileTable.col2.push_back(col2Value);
        }
}
