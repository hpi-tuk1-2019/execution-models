#pragma once
#include "TableReader.h"
#include <map>

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

typedef std::map<std::pair<char, char>, ResultRow> ResultMap;

class QueryOne {
  private:
    std::vector<int> op_shipdate_se(const table& tab);
    //std::vector<int> op_sort_returnflag_linestatus(const table& tab, std::vector<int> old_inds);
    ResultMap op_group_returnflag_linestatus(const table& tab, std::vector<int> old_inds);
    ResultMap op_sum_qty(const table& tab, std::vector<int> old_inds, ResultMap groups);
    ResultMap op_sum_base_price(const table& tab, std::vector<int> old_inds, ResultMap groups);
    ResultMap op_sum_disk_price(const table& tab, std::vector<int> old_inds, ResultMap groups);
    ResultMap op_sum_charge(const table& tab, std::vector<int> old_inds, ResultMap groups);
    ResultMap op_avg_qty(const table& tab, std::vector<int> old_inds, ResultMap groups);
    ResultMap op_avg_price(const table& tab, std::vector<int> old_inds, ResultMap groups);
    ResultMap op_avg_disc(const table& tab, std::vector<int> old_inds, ResultMap groups);
    ResultMap op_count_order(const table& tab, std::vector<int> old_inds, ResultMap groups);
  public:
    ResultMap execute(const table& tab);
    ResultMap execute_compiled(const table& tab);
};
