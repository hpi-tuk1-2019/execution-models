#include "TableReader.h"
#include "QuerySix.h"
#include "StopWatch.h"
#include "MathematicalOperators.h"
#include <vector>
#include <iostream>

double QuerySix::execute_hybrid(const table& tab) {
    StopWatch cb = StopWatch("creating bitmap");
    StopWatch fb = StopWatch("filling bitmap");
    StopWatch cr = StopWatch("compiled rest");

    cb.tik();
    int size = tab.l_extendedprice.size();
    std::vector<int> bitmap(size, true);
    cb.tok();

    fb.tik();
    op_discount_ge(tab, bitmap);
    fb.tok();
    cr.tik();
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (
            (tab.l_discount[i] <= 7) &&
            (tab.l_shipdate[i] < 788918400) &&
            (tab.l_shipdate[i] >= 757382400) &&
            (tab.l_quantity[i] < 2400))
            * tab.l_extendedprice[i] * tab.l_discount[i] * bitmap[i];
    }
    cr.tok();

    cb.write_to_file("createBitmapHybrid.csv");
    fb.write_to_file("fillBitmapHybrid.csv");
    cr.write_to_file("compiledRestHybrid.csv");

    return (double)sum / 10000.0;
}

double QuerySix::execute_compiled(const table& tab) {
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

int count_bm(std::vector<int> bm) {
    int count = 0;
    for (auto i : bm) {
        if (bm[i]) {
            count++;
        }
    }
    return count;
}

double QuerySix::execute(const table& tab) {
    std::vector<int> bitmap(tab.l_extendedprice.size(), true);

    op_discount_ge(tab, bitmap);
    op_discount_se(tab, bitmap);
    op_shipdate_s(tab, bitmap);
    op_shipdate_ge(tab, bitmap);
    op_quantity_s(tab, bitmap);
    return op_agg_sum(tab, bitmap);
}

double QuerySix::op_agg_sum(const table& tab, std::vector<int>& bitmap) {
    int sum = 0;
    int size = bitmap.size();
    for (int i = 0; i < size; i++) {
        sum = db_plus(sum, db_times(bitmap[i], db_times(tab.l_extendedprice[i], tab.l_discount[i])));
    }
    return (double)sum / 10000.00;
}

void QuerySix::op_shipdate_ge(const table& tab, std::vector<int>& bitmap) {
    int size = bitmap.size();
    for (int i = 0; i < size; i++) {
        bitmap[i] = bitmap[i] * (tab.l_shipdate[i] >= 757382400);
    }
}

void QuerySix::op_shipdate_s(const table& tab, std::vector<int>& bitmap) {
    int size = bitmap.size();
    for (int i = 0; i < size; i++) {
        bitmap[i] = bitmap[i] * (tab.l_shipdate[i] < 788918400);
    }
}

void QuerySix::op_quantity_s(const table& tab, std::vector<int>& bitmap) {
    int size = bitmap.size();
    for (int i = 0; i < size; i++) {
        bitmap[i] = bitmap[i] * (tab.l_quantity[i] < 2400);
    }
}

void QuerySix::op_discount_ge(const table& tab, std::vector<int>& bitmap) {
    int size = bitmap.size();
    for (int i = 0; i < size; i++) {
        bitmap[i] = (tab.l_discount[i] >= 5);
    }
}

void QuerySix::op_discount_se(const table& tab, std::vector<int>& bitmap) {
    int size = bitmap.size();
    for (int i = 0; i < size; i++) {
        bitmap[i] = bitmap[i] * (tab.l_discount[i] <= 7);
    }
}
