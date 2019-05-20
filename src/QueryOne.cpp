#include "TableReader.h"
#include "QueryOne.h"
#include <vector>
#include <algorithm>

ResultTable QueryOne::execute(const table& tab){
  std::vector<int> initial_indices;
  for (int i = 0; i < tab.l_extendedprice.size(); i++) {
    initial_indices.push_back(i);
  }
  ResultTable resultTable;
  std::vector<int> indices1 = op_shipdate_se(tab, initial_indices);
  std::vector<int> indices2 = op_sort_returnflag_linestatus(tab, indices1);
  std::vector<int> groups = op_group_returnflag_linestatus(tab, indices2, resultTable);
  resultTable.sum_qty = op_sum_qty(tab, indices2, groups);
  resultTable.sum_base_price = op_sum_base_price(tab, indices2, groups);
  resultTable.sum_disc_price = op_sum_disk_price(tab, indices2, groups);
  resultTable.sum_charge = op_sum_charge(tab, indices2, groups);
  resultTable.avg_qty = op_avg_qty(tab, indices2, groups);
  resultTable.avg_price = op_avg_price(tab, indices2, groups);
  resultTable.avg_disc = op_avg_disc(tab, indices2, groups);
  resultTable.count_order = op_count_order(tab, indices2, groups);
  
  return resultTable;
}

std::vector<int> QueryOne::op_group_returnflag_linestatus(const table& tab, std::vector<int> old_inds, ResultTable& resultTable) {
  std::vector<int> groups;
  groups.push_back(0);
  resultTable.l_linestatus.push_back(tab.l_linestatus[old_inds[0]]);
  resultTable.l_returnflag.push_back(tab.l_returnflag[old_inds[0]]);
  for (int i = 1; i < old_inds.size(); i++) {
    if ((tab.l_returnflag[old_inds[i]] != tab.l_returnflag[old_inds[i-1]]) || 
        (tab.l_linestatus[old_inds[i]] != tab.l_linestatus[old_inds[i-1]])) {
      groups.push_back(i);
      resultTable.l_linestatus.push_back(tab.l_linestatus[old_inds[i]]);
      resultTable.l_returnflag.push_back(tab.l_returnflag[old_inds[i]]);
    }
  }
  groups.push_back(old_inds.size());
  return groups;
}

std::vector<long long int> QueryOne::op_sum_qty(const table & tab, std::vector<int> old_inds, std::vector<int> groups)
{
    std::vector<long long int> sum_qty(groups.size() - 1);
    for (int i = 0; i < groups.size() - 1; i++) {
        long long int sum = 0;
        for (int j = groups[i]; j < groups[i + 1]; j++) {
            sum += tab.l_quantity[old_inds[j]];
        }
        sum_qty[i] = sum;
    }
    return sum_qty;
}

std::vector<long long int> QueryOne::op_sum_base_price(const table & tab, std::vector<int> old_inds, std::vector<int> groups)
{
    std::vector<long long int> sum_base_price(groups.size() - 1);
    for (int i = 0; i < groups.size() - 1; i++) {
        long long int sum = 0;
        for (int j = groups[i]; j < groups[i + 1]; j++) {
            sum += tab.l_extendedprice[old_inds[j]];
        }
        sum_base_price[i] = sum;
    }
    return sum_base_price;
}

std::vector<long long int> QueryOne::op_sum_disk_price(const table & tab, std::vector<int> old_inds, std::vector<int> groups)
{
    std::vector<long long int> sum_disk_price(groups.size() - 1);
    for (int i = 0; i < groups.size() - 1; i++) {
        long long int sum = 0;
        for (int j = groups[i]; j < groups[i + 1]; j++) {
            sum += tab.l_extendedprice[old_inds[j]] * (100 - tab.l_discount[old_inds[j]]);
        }
        sum_disk_price[i] = sum;
    }
    return sum_disk_price;
}

std::vector<long long int> QueryOne::op_sum_charge(const table & tab, std::vector<int> old_inds, std::vector<int> groups)
{
    std::vector<long long int> sum_charge(groups.size() - 1);
    for (int i = 0; i < groups.size() - 1; i++) {
        long long int sum = 0;
        for (int j = groups[i]; j < groups[i + 1]; j++) {
            sum += tab.l_extendedprice[old_inds[j]] * (100 - tab.l_discount[old_inds[j]]) * (100 + tab.l_tax[old_inds[j]]);
        }
        sum_charge[i] = sum;
    }
    return sum_charge;
}

std::vector<double> QueryOne::op_avg_qty(const table & tab, std::vector<int> old_inds, std::vector<int> groups)
{
    std::vector<double> avg_qty(groups.size() - 1);
    for (int i = 0; i < groups.size() - 1; i++) {
        long long int sum = 0;
        for (int j = groups[i]; j < groups[i + 1]; j++) {
            sum += tab.l_quantity[old_inds[j]];
        }
        double count = groups[i + 1] - groups[i];
        avg_qty[i] = double(sum)/count;
    }
    return avg_qty;
}

std::vector<double> QueryOne::op_avg_price(const table & tab, std::vector<int> old_inds, std::vector<int> groups)
{
    std::vector<double> avg_price(groups.size() - 1);
    for (int i = 0; i < groups.size() - 1; i++) {
        long long int sum = 0;
        for (int j = groups[i]; j < groups[i + 1]; j++) {
            sum += tab.l_extendedprice[old_inds[j]];
        }
        double count = groups[i + 1] - groups[i];
        avg_price[i] = double(sum) / count;
    }
    return avg_price;
}

std::vector<double> QueryOne::op_avg_disc(const table & tab, std::vector<int> old_inds, std::vector<int> groups)
{
    std::vector<double> avg_disc(groups.size() - 1);
    for (int i = 0; i < groups.size() - 1; i++) {
        long long int sum = 0;
        for (int j = groups[i]; j < groups[i + 1]; j++) {
            sum += tab.l_discount[old_inds[j]];
        }
        double count = groups[i + 1] - groups[i];
        avg_disc[i] = double(sum) / count;
    }
    return avg_disc;
}

std::vector<int> QueryOne::op_count_order(const table & tab, std::vector<int> old_inds, std::vector<int> groups)
{
    std::vector<int> count(groups.size() - 1);
    for (int i = 0; i < groups.size() - 1; i++) {
        count[i] = groups[i + 1] - groups[i];
    }
    return count;
}

std::vector<int> QueryOne::op_sort_returnflag_linestatus(const table& tab, std::vector<int> old_inds){
  std::vector<int> indices;
  std::vector<std::tuple<char,char, int>> sub_table;
  sub_table.reserve(old_inds.size());
  for (auto i : old_inds) {
    sub_table.push_back(std::make_tuple(tab.l_returnflag[i],tab.l_linestatus[i],i));
  }
  std::sort(sub_table.begin(), sub_table.end(), [](const auto& a, const auto& b) {
    if (std::get<0>(a) == std::get<0>(b)) {
      return std::get<1>(a) < std::get<1>(b);
    }
    return std::get<0>(a) < std::get<0>(b);
  });
  indices.reserve(sub_table.size());
  for (auto a : sub_table) {
    indices.push_back(std::get<2>(a));
  }
  return indices;
}


std::vector<int> QueryOne::op_shipdate_se(const table& tab, std::vector<int> old_inds){
  std::vector<int> indices;
  for (auto i : old_inds) {
    if (tab.l_shipdate[i] <= 904694400) {
      indices.push_back(i);
    }
  }
  return indices;
}
