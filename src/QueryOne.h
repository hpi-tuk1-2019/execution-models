#pragma once
#include "TableReader.h"
#include <map>

struct ResultTable {
    std::vector<char> l_returnflag; // fixed text, size 1
    std::vector<char> l_linestatus; // fixed text, size 1
    std::vector<long long int> sum_qty;
    std::vector<long long int> sum_base_price; // sum(l_extendedprice)
    std::vector<long long int> sum_disc_price; // sum(l_extendedprice * (1 - l_discount))
    std::vector<long long int> sum_charge; // sum(l_extendedprice * (1 - l_discount) * (1 + l_tax))
    std::vector<double> avg_qty;
    std::vector<double> avg_price;
    std::vector<double> avg_disc;
    std::vector<int> count_order;
};

struct ResultRow {
    long long int sum_qty = 0;
    long long int sum_base_price = 0; // sum(l_extendedprice)
    long long int sum_disc_price = 0; // sum(l_extendedprice * (1 - l_discount))
    long long int sum_charge = 0; // sum(l_extendedprice * (1 - l_discount) * (1 + l_tax))
    double avg_qty = 0;
    double avg_price = 0;
    double avg_disc = 0;
    int count_order = 0;
};

class QueryOne {
  private:
    std::vector<int> op_shipdate_se(const table& tab);
    std::vector<int> op_sort_returnflag_linestatus(const table& tab, std::vector<int> old_inds);
    std::vector<int> op_group_returnflag_linestatus(const table& tab, std::vector<int> old_inds, ResultTable& resultTable);
    std::vector<long long int> op_sum_qty(const table& tab, std::vector<int> old_inds, std::vector<int> groups);
    std::vector<long long int> op_sum_base_price(const table& tab, std::vector<int> old_inds, std::vector<int> groups);
    std::vector<long long int> op_sum_disk_price(const table& tab, std::vector<int> old_inds, std::vector<int> groups);
    std::vector<long long int> op_sum_charge(const table& tab, std::vector<int> old_inds, std::vector<int> groups);
    std::vector<double> op_avg_qty(const table& tab, std::vector<int> old_inds, std::vector<int> groups);
    std::vector<double> op_avg_price(const table& tab, std::vector<int> old_inds, std::vector<int> groups);
    std::vector<double> op_avg_disc(const table& tab, std::vector<int> old_inds, std::vector<int> groups);
    std::vector<int> op_count_order(const table& tab, std::vector<int> old_inds, std::vector<int> groups);
  public:
    ResultTable execute(const table& tab);

    std::map<std::pair<char, char>, ResultRow> execute_compiled(const table& tab);
};
