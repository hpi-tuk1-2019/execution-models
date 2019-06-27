#include "TableReader.h"
#include "QuerySix.h"
#include "MathematicalOperators.h"
#include <vector>
#include <iostream>

double QuerySix::execute_hybrid(const table& tab) {  
  int size = tab.l_extendedprice.size();
  std::vector<BITMAP_TYPE> bitmap(size, true);

  op_discount_ge(tab, bitmap);
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += (int)(
                (tab.l_discount[i] <= 7) &&
                (tab.l_shipdate[i] < 788918400) &&
                (tab.l_shipdate[i] >= 757382400) &&
                (tab.l_quantity[i] < 2400))
           * tab.l_extendedprice[i] * tab.l_discount[i] * bitmap[i];
  }
  return (double)sum / 10000.0;
}

double QuerySix::execute_compiled(const table& tab){
  int sum = 0;
  int size =  tab.l_extendedprice.size();
  for (int i = 0; i < size; i++) {
    sum += (int)((tab.l_discount[i] >= SELECTIVITY) &&
                  (tab.l_discount[i] <= 7) &&
                  (tab.l_shipdate[i] < 788918400) &&
                  (tab.l_shipdate[i] >= 757382400) &&
                  (tab.l_quantity[i] < 2400))
            * tab.l_extendedprice[i] * tab.l_discount[i];
  }
  return (double)sum / 10000.0;
}

int count_bm(std::vector<BITMAP_TYPE> bm) {
  int count = 0;
  for (auto i: bm) {
    if (bm[i]) {
      count++;
    }
  }
  return count;
}

double QuerySix::execute(const table& tab){
  std::vector<BITMAP_TYPE> bitmap(tab.l_extendedprice.size(), true);

  op_discount_ge(tab, bitmap);
  op_discount_se(tab, bitmap);
  op_shipdate_s(tab, bitmap);
  op_shipdate_ge(tab, bitmap);
  op_quantity_s(tab, bitmap);
  return op_agg_sum(tab, bitmap);
}

double QuerySix::op_agg_sum(const table& tab, std::vector<BITMAP_TYPE>& bitmap){
  int sum = 0;
  int size = bitmap.size();
  for (int i = 0; i < size; i++) {
    sum = db_plus(sum,db_times(bitmap[i], db_times(tab.l_extendedprice[i], tab.l_discount[i])));
  }
  return (double)sum / 10000.00;
}

void QuerySix::op_shipdate_ge(const table& tab, std::vector<BITMAP_TYPE>& bitmap){
  int size = bitmap.size();
#pragma GCC ivdep
#pragma ivdep
  for (int i = 0; i < size; i++) {
    bitmap[i] = bitmap[i] * (tab.l_shipdate[i] >= 757382400);
  }
}

void QuerySix::op_shipdate_s(const table& tab, std::vector<BITMAP_TYPE>& bitmap){
  int size = bitmap.size();
#pragma GCC ivdep
#pragma ivdep
  for (int i = 0; i < size; i++) {
    bitmap[i] = bitmap[i] *  (tab.l_shipdate[i] < 788918400);
  }
}

void QuerySix::op_quantity_s(const table& tab, std::vector<BITMAP_TYPE>& bitmap){
  int size = bitmap.size();
#pragma GCC ivdep
#pragma ivdep
  for (int i = 0; i < size; i++) {
    bitmap[i] = bitmap[i] * (tab.l_quantity[i] < 2400);
  }
}

void QuerySix::op_discount_ge(const table& tab, std::vector<BITMAP_TYPE>& bitmap){
  int size = bitmap.size();
#pragma GCC ivdep
#pragma ivdep
    for ( int i = 0; i < size ; i ++) {
      bitmap[i] = (tab.l_discount[i] >= SELECTIVITY);
    }
}

void QuerySix::op_discount_se(const table& tab, std::vector<BITMAP_TYPE>& bitmap){
  int size = bitmap.size();
#pragma GCC ivdep
#pragma ivdep
  for (int i = 0; i < size; i++) {
    bitmap[i] = bitmap[i] * (tab.l_discount[i] <= 7);
  }
}
