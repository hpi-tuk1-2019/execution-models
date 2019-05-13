#include "TableReader.h"
#include "QueryOne.h"
#include <vector>
#include <algorithm>

double QueryOne::execute(const table& tab){
  std::vector<int> initial_indices;
  for (int i = 0; i < tab.l_extendedprice.size(); i++) {
    initial_indices.push_back(i);
  }
  std::vector<int> indices1 = op_shipdate_se(tab, initial_indices);
  std::vector<int> indices2 = op_sort_returnflag_linestatus(tab, indices1);
  std::vector<int> groups = op_sort_returnflag_linestatus(tab, indices2);

  return 0;
}

std::vector<int> QueryOne::op_aggregate(const table& tab, std::vector<int> old_inds, std::vector<int> groups) {
  std::vector<std::tuple<char, char, double, double, double, double, double, double, double, int>> result_set;
  for (int i = 1; i < groups.size(), i++) {
    char l_returnflag = tab.l_returnflag[old_inds[groups[i-1]]];
    char l_linestatus = tab.l_linestatus[old_inds[groups[i-1]]];
    for (int j = groups[i-1]; j < groups[i]; j++) {
    }
  }
}

std::vector<int> QueryOne::op_group_returnflag_linestatus(const table& tab, std::vector<int> old_inds) {
  std::vector<int> groups;
  groups.push_back(0);
  for (int i = 1; i < old_inds.size(); i++) {
    if ((tab.l_returnflag[old_inds[i]] != tab.l_returnflag[old_inds[i-1]]) && (tab.l_linestatus[old_inds[i]] != tab.l_linestatus[old_inds[i-1]])) {
      groups.push_back(i);
    }
  }
  return groups;
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
