#include "TableReader.h"
#include "QuerySix.h"
#include <vector>

double QuerySix::execute(const table& tab){
  std::vector<int> initial_indices;
  for (int i = 0; i < tab.l_extendedprice.size(); i++) {
    initial_indices.push_back(i);
  }
  std::vector<int> indices1 = op_discount_between(tab, initial_indices);
  std::vector<int> indices2 = op_shipdate_s(tab, indices1);
  std::vector<int> indices3 = op_shipdate_ge(tab, indices2);
  std::vector<int> indices4 = op_quantity_s(tab, indices3);
  return op_agg_sum(tab, indices4);
}

double QuerySix::op_agg_sum(const table& tab, std::vector<int> old_inds){
  double sum = 0;
  for (auto i : old_inds) {
    sum += tab.l_extendedprice[i] * tab.l_discount[i];
  }
  return (double)sum / 10000.0;

}

std::vector<int> QuerySix::op_shipdate_ge(const table& tab, std::vector<int> old_inds){
  std::vector<int> indices;
  for (auto i : old_inds) {
    if (tab.l_shipdate[i] >= 757382400) {
      indices.push_back(i);
    }
  }
  return indices;
}

std::vector<int> QuerySix::op_shipdate_s(const table& tab, std::vector<int> old_inds){
  std::vector<int> indices;
  for (auto i : old_inds) {
    if (tab.l_shipdate[i] < 788918400) {
      indices.push_back(i);
    }
  }
  return indices;
}

std::vector<int> QuerySix::op_quantity_s(const table& tab, std::vector<int> old_inds){
  std::vector<int> indices;
  for (auto i : old_inds) {
    if (tab.l_quantity[i] < 2400) {
      indices.push_back(i);
    }
  }
  return indices;
}

std::vector<int> QuerySix::op_discount_between(const table& tab, std::vector<int> old_inds){
  std::vector<int> indices;
  for (auto i : old_inds) {
    if ((tab.l_discount[i] >= 5) && (tab.l_discount[i]) <= 7) {
      indices.push_back(i);
    }
  }
  return indices;
}
