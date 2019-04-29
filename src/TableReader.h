#include <vector>
#include <array>

typedef std::array<char, 45> dbString;

struct table {
    std::vector<int> col1;
    std::vector<dbString> col2;
};

table readFile(std::string filename);
