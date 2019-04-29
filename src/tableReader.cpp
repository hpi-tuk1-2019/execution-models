#include "TableReader.h"

#include <string>
#include <fstream>
#include <iostream>

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
            fileTable.col2.push_back(value);
        }


}
