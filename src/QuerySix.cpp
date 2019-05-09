#include "TableReader.h"
#include "QuerySix.h"
#include <vector>

int QuerySix::execute(table &tab){

}

int QuerySix::op_agg_sum(table &tab){

}

std::vector<int> QuerySix::op_shipdate_ge(table &tab, std::vector<int> old_inds){
  std::vector<int> indices;
  for (int i = 0; i < old_inds.size(); i++) {
    if (tab.l_shipdate[i] >= 757382400) {
      indices.push_back(i)
    }
  }
  return indices
}

std::vector<int> QuerySix::op_shipdate_s(table &tab, std::vector<int> old_inds){
  std::vector<int> indices;
  for (int i = 0; i < old_inds.size(); i++) {
    if (tab.l_shipdate[i] < 788918400) {
      indices.push_back(i)
    }
  }
  return indices
}

std::vector<int> QuerySix::op_quantity_s(table &tab, std::vector<int> old_inds){
  std::vector<int> indices;
  for (int i = 0; i < old_inds.size(); i++) {
    if (tab.l_quantity[i] < 24) {
      indices.push_back(i)
    }
  }
  return indices
}

std::vector<int> QuerySix::op_discount_between(table &tab, std::vector<int> old_inds){
  std::vector<int> indices;
  for (int i = 0; i < old_inds.size(); i++) {
    if ((tab.l_orderkey[i] >= 0.05) && (tab.l_orderkey[i]) <= 0.07) {
      indices.push_back(i)
    }
  }
  return indices
}
