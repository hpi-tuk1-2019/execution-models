#include "TableReader.h"

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
};
