#include "StopWatch.h"
#include "QuerySix.h"
#include "QueryOne.h"
#include <string>
#include <iostream>
#include <chrono>

int touch_all_values(std::vector<uint16_t>& vec){
  int a = 0;
	int size = vec.size();
  for (int i = 0; i < size; i++) {
		if (vec[i] <= 10) {
					a += 1;
		}
	}
  return a;
}

void measure_bandwidth(int measurement_count, long int obs_size) {
	std::vector<uint16_t> vec;
	StopWatch measure = StopWatch("bandwith_measurement");
	uint16_t k = 5;
	for (int i = 0; i < obs_size; i++) {
		vec.push_back((uint16_t)(rand() % 100));
	}
	std::cout << vec.size() * 2 << std::endl;
	for (int i = 0; i < measurement_count; i++) {
		measure.tik();
		int a = touch_all_values(vec);
		measure.tok();
		std::cout << a << std::endl;
		//measure.print_stats();
	}
	measure.write_to_file("measure_bandwidth_random_vec.csv");

}


int main(int argc, char *argv[]) {
  long int obs_size = 2500000;
  int rounds = 100;
  std::string filename = "../../assets/sample_data/lineitem.tbl";
    if (argc < 4) {
      std::cout << "Using standard values" << std::endl;
    } else {
      filename = argv[1];
      obs_size = std::stod(argv[2]);
      rounds = std::stod(argv[3]);
    }
    char delim = '|';

    StopWatch reading = StopWatch("reading csv");
    StopWatch q6sw = StopWatch("query 6 normal");

    reading.tik();
    auto fileTable = readFile(filename, delim);
    reading.tok();
    reading.print_stats();

    measure_bandwidth(rounds, obs_size);

    QuerySix q6;
    for (int i = 0; i < rounds; i++) {
      q6sw.tik();
      double res = q6.execute(fileTable);
      q6sw.tok();
      std::cout << res << std::endl;
    }
    q6sw.write_to_file("measure_bandwidth_q6.csv");



    return 0;
}
