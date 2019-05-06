#include "TableReader.h"
#include <string>
#include <iostream>

void print_sample(table table_obj) {
    int sample_size = 20;
    for (int i = 0; i < sample_size; i++){
        // std::cout << table_obj.l_orderkey.at(i) << std::endl;
        // std::cout << table_obj.l_partkey.at(i) << std::endl;
        // std::cout << table_obj.l_suppkey.at(i) << std::endl;
        // std::cout << table_obj.l_linenumber.at(i) << std::endl;
        std::cout << table_obj.l_quantity.at(i) << std::endl;
        // std::cout << table_obj.l_extendedprice.at(i) << std::endl;
        // std::cout << table_obj.l_discount.at(i) << std::endl;
        // std::cout << table_obj.l_tax.at(i) << std::endl;
        // std::cout << table_obj.l_returnflag.at(i) << std::endl;
        // std::cout << table_obj.l_linestatus.at(i) << std::endl;
        std::cout << table_obj.l_shipdate.at(i) << std::endl;
        // std::cout << table_obj.l_commitdate.at(i) << std::endl;
        // std::cout << table_obj.l_receiptdate.at(i) << std::endl;
        // std::cout << table_obj.l_shipinstruct.at(i) << std::endl;
        // std::cout << table_obj.l_shipmode.at(i) << std::endl;
        // std::cout << table_obj.l_comment.at(i) << std::endl;
    }
}

int main(int argc, char *argv[]) {
    std::string filename = "../../assets/sample_data/lineitem.tbl";
    char delim = '|';

    auto table = readFile(filename, delim);

    print_sample(table);

    return 0;
}

