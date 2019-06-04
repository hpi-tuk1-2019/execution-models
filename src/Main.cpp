#pragma once
#include "StopWatch.h"
#include "QuerySix.h"
#include <string>
#include <iostream>
#include <chrono>
#include <cstdlib>

void print_char_array(std::array<char, 45> char_array) {
  for (int i = 0; i < sizeof(char_array); i++) {
    std::cout << char_array[i];
  }
  std::cout <<  ", ";
}

void print_sample(table table_obj, int sample_size = 20) {
  for (int i = 0; i < sample_size; i++){
    std::cout << table_obj.l_orderkey.at(i) << ", ";
    std::cout << table_obj.l_partkey.at(i) << ", ";
    std::cout << table_obj.l_suppkey.at(i) << ", ";
    std::cout << table_obj.l_linenumber.at(i) << ", ";
    std::cout << table_obj.l_quantity.at(i) << ", ";
    std::cout << table_obj.l_extendedprice.at(i) << ", ";
    std::cout << table_obj.l_discount.at(i) << ", ";
    std::cout << table_obj.l_tax.at(i) << ", ";
    std::cout << table_obj.l_returnflag.at(i) << ", ";
    std::cout << table_obj.l_linestatus.at(i) << ", ";
    std::cout << table_obj.l_shipdate.at(i) << ", ";
    std::cout << table_obj.l_commitdate.at(i) << ", ";
    std::cout << table_obj.l_receiptdate.at(i) << ", ";

    print_char_array(table_obj.l_shipinstruct.at(i));
    print_char_array(table_obj.l_shipmode.at(i));
    print_char_array(table_obj.l_comment.at(i));
    std::cout << "\n";
  }
}

int touch_all_values(std::vector<auto>& vec){
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
  StopWatch measure = StopWatch("Memory bandwidth measurement Random Vector");
  uint16_t k = 5;
    //std::cout << k.size() << std::endl;
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
  measure.write_to_file("bandwith.csv");

}


int main(int argc, char *argv[]) {
    // use to check size of an int on your machine
    // std::cout << sizeof(int) << std::endl;
  std::string filename = "../../assets/sample_data/lineitem.tbl";
  char delim = '|';

  StopWatch reading = StopWatch("reading csv");
  reading.tik();
    //auto fileTable = readFile(filename, delim);
  reading.tok();
  <<<<<<< HEAD

  StopWatch mem_bandwidth = StopWatch("Memory bandwidth measurement (TCP-H Full Table Scan)");
  mem_bandwidth.tik();
  int a = touch_all_values(fileTable);
  mem_bandwidth.tok();
  std::cout << a;

  mem_bandwidth.print_stats();

  measure_bandwidth(10, 250000000);

  StopWatch mem_bandwidth2 = StopWatch("Memory bandwidth measurement (Query 6 Compiled)");
  auto q = QuerySix();
  mem_bandwidth.tik();
  int a2 = q.execute(fileTable);
  mem_bandwidth2.tok();
  std::cout << a2 << std::endl;
  mem_bandwidth2.print_stats();

  return 0;
}
