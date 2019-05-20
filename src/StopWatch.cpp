#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include "StopWatch.h"

StopWatch::StopWatch(std::string st_name) {
  name = st_name;
}

void StopWatch::tik() {
  start = std::chrono::steady_clock::now();
}

void StopWatch::tok() {
  stop = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
  measurements.push_back(duration);
}

void StopWatch::print_stats() {
  std::cout << name <<  ": Execution Time: " << measurements.back() << " ms" << std::endl;
}

void StopWatch::write_to_file(std::string filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "File cannot be opened";
    }

    for (auto& m : measurements) {
        file << std::to_string(m) + "\n";
    }
}