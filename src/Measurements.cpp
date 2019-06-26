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
		std::cerr << "Usage: " << argv[0] << " <filepath> <#items> <#executions>" << std::endl;
		return 1;
	}
  try {
		filename = argv[1];
		obs_size = std::stoi(argv[2]);
		rounds = std::stoi(argv[3]);
	}
	catch (const std::exception & e) {
		std::cerr << "Usage: " << argv[0] << " <filepath> <#items> <#executions>" << std::endl;
		return 1;
	}

    char delim = '|';

    StopWatch reading = StopWatch("reading csv");
    StopWatch q6sw = StopWatch("query 6 normal");

    reading.tik();
    auto fileTable = readFile(filename, delim, obs_size);
    reading.tok();
    reading.print_stats();

    measure_bandwidth(rounds, obs_size);

    QuerySix q6;
    for (int i = 0; i < rounds; i++) {
      int size = fileTable.l_extendedprice.size();
      std::vector<BITMAP_TYPE> bitmap(size, true);
      q6sw.tik();
      q6.op_discount_ge(fileTable, bitmap);
      q6sw.tok();
      std::cout << bitmap[5] << std::endl;
    }
    q6sw.write_to_file("measure_bandwidth_q6.csv");



    return 0;
}
