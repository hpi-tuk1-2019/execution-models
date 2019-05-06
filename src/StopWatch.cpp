#include <chrono>
#include <iostream>
#include <string>
#include "StopWatch.h"

StopWatch::StopWatch(std::string st_name) {
  name = st_name;
}

void StopWatch::tik() {
  start = std::chrono::steady_clock::now();
}

void StopWatch::tok() {
  stop = std::chrono::steady_clock::now();
}

void StopWatch::print_stats() {
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count();
  std::cout << name <<  ": Execution Time: " << duration << " ms" << std::endl;
}
