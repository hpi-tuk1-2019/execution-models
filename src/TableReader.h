#include <vector>

struct table {
    std::vector<int> col1;
    std::vector<std::array<char, 20>> col2;
};

table readFile(std::string filename);