#include "TableReader.h"
#include "QuerySix.h"
#include <vector>
#include <iostream>

double QuerySix::execute_hybrid(const table& tab) {
  int size = tab.l_extendedprice.size();
  std::vector<bool> bitmap(size, true);

  op_discount_ge(tab, bitmap);
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += (int)(bitmap[i] &&
                (tab.l_discount[i] <= 7) &&
                (tab.l_shipdate[i] < 788918400) &&
                (tab.l_shipdate[i] >= 757382400) &&
                (tab.l_quantity[i] < 2400))
           * tab.l_extendedprice[i] * tab.l_discount[i];
  }
  return (double)sum / 10000.0;
}

double QuerySix::execute_compiled(const table& tab){
  int sum = 0;
  for (int i = 0; i < tab.l_extendedprice.size(); i++) {
    sum += (int)((tab.l_discount[i] >= 5) &&
                  (tab.l_discount[i] <= 7) &&
                  (tab.l_shipdate[i] < 788918400) &&
                  (tab.l_shipdate[i] >= 757382400) &&
                  (tab.l_quantity[i] < 2400))
            * tab.l_extendedprice[i] * tab.l_discount[i];
  }
  return (double)sum / 10000.0;
}

int count_bm(std::vector<bool> bm) {
  int count = 0;
  for (auto i: bm) {
    if (bm[i]) {
      count++;
    }
  }
  return count;
}

double QuerySix::execute(const table& tab){
  std::vector<bool> bitmap(tab.l_extendedprice.size(), true);

  op_discount_ge(tab, bitmap);
  op_discount_se(tab, bitmap);
  op_shipdate_s(tab, bitmap);
  op_shipdate_ge(tab, bitmap);
  op_quantity_s(tab, bitmap);
  return op_agg_sum(tab, bitmap);
}

double QuerySix::op_agg_sum(const table& tab, std::vector<bool>& bitmap){
  int sum = 0;
  int size = bitmap.size();
  for (int i = 0; i < size; i++) {
    sum += (int)bitmap[i]  * tab.l_extendedprice[i] * tab.l_discount[i];
  }
  return (double)sum / 10000.0;
}

void QuerySix::op_shipdate_ge(const table& tab, std::vector<bool>& bitmap){
  int size = bitmap.size();
  for (int i = 0; i < size; i++) {
    bitmap[i] = bitmap[i] && (tab.l_shipdate[i] >= 757382400);
  }
}

void QuerySix::op_shipdate_s(const table& tab, std::vector<bool>& bitmap){
  int size = bitmap.size();
  for (int i = 0; i < size; i++) {
    bitmap[i] = bitmap[i] &&  (tab.l_shipdate[i] < 788918400);
  }
}

void QuerySix::op_quantity_s(const table& tab, std::vector<bool>& bitmap){
  int size = bitmap.size();
  for (int i = 0; i < size; i++) {
    bitmap[i] = bitmap[i] && (tab.l_quantity[i] < 2400);
  }
}

void QuerySix::op_discount_ge(const table& tab, std::vector<bool>& bitmap){
  int size = bitmap.size();

  // int* l_discount_a[size];
  // std::copy(tab.l_discount.begin(), tab.l_discount.end(), &l_discount_a);
  int bitmap_a[size];
  for (int i = 0; i < 6005; i++) {
    bitmap_a[i] = bitmap[i];
  }
  // int*__restrict l_discount_a = const_cast<int*>(tab.l_discount.data());
  //bool*__restrict bitmap_a = const_cast<std::vector<bool>*>(&bitmap);
  // bool*__restrict bitmap_a = const_cast<bool*>(&bitmap[0]);
  // bitmap_a[i] = l_discount_a[i] >= 5;

    int a[size];
    int b[size];
    int c[size];

    for ( int i = 0; i < size ; i ++) {
      a[i] += bitmap_a[i];
    }

  for (int i = 0; i < 6005; i++) {
    bitmap[i] = (bool) tab.l_discount[i];
  }
}

void QuerySix::op_discount_se(const table& tab, std::vector<bool>& bitmap){
  int size = bitmap.size();
  for (int i = 0; i < size; i++) {
    bitmap[i] = bitmap[i] &&  (tab.l_discount[i] <= 7);
  }
}
