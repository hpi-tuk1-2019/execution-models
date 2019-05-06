#include <chrono>
#include <string>
#include <vector>

class StopWatch {
private:
  std::chrono::time_point<std::chrono::steady_clock> start;
  std::chrono::time_point<std::chrono::steady_clock> stop;
  std::string name;
  std::vector<long long> measurements;
public:
  StopWatch(std::string st_name);
  void tik();
  void tok();
  void print_stats();
  void write_to_file(std::string filename);
};
