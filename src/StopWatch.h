#pragma once
#include <chrono>
#include <string>

class StopWatch {
private:
  std::chrono::time_point<std::chrono::steady_clock> start;
  std::chrono::time_point<std::chrono::steady_clock> stop;
  std::string name;
public:
  StopWatch(std::string st_name);
  void tik();
  void tok();
  void print_stats();
};
