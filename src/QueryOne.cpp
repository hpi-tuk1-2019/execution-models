#include "TableReader.h"
#include "QueryOne.h"
#include "MathematicalOperators.h"
#include <vector>
#include <algorithm>


ResultMap QueryOne::execute(const table& tab){
    auto bitmap = op_shipdate_se(tab);
    auto groups = op_group_returnflag_linestatus(tab, bitmap);
    op_sum_qty(tab, bitmap, groups);
    op_sum_base_price(tab, bitmap, groups);
    op_sum_disk_price(tab, bitmap, groups);
    op_sum_charge(tab, bitmap, groups);
    op_count_order(tab, bitmap, groups);
    op_avg_qty(tab, groups);
    op_avg_price(tab, groups);
    op_avg_disc(tab, bitmap, groups);

    return groups;
}

ResultMap QueryOne::execute_hybrid(const table & tab)
{
    auto bitmap = op_shipdate_se(tab);
    ResultMap result;
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        result.insert(std::pair<std::pair<char, char>, ResultRow>(key, ResultRow()));
        auto& resultRow = result.at(key);
        int useRow = bitmap[i];
        resultRow.count_order += useRow;
        resultRow.sum_qty += tab.l_quantity[i] * useRow;
        resultRow.sum_base_price += tab.l_extendedprice[i] * useRow;
        resultRow.sum_disc_price += useRow * tab.l_extendedprice[i] * double(100 - tab.l_discount[i]) / 100.0;
        resultRow.sum_charge += useRow * tab.l_extendedprice[i] * double(100 - tab.l_discount[i]) / 100.0 * double(100 + tab.l_tax[i]) / 100.0;
        resultRow.avg_disc += useRow * tab.l_discount[i];
    }
    // calculate averages
    for (auto& resultRow : result) {
        auto& rr = resultRow.second;
        rr.avg_qty = double(rr.sum_qty) / double(rr.count_order);
        rr.avg_price = double(rr.sum_base_price) / double(rr.count_order);
        rr.avg_disc /= double(rr.count_order);
    }
    return result;
}

ResultMap QueryOne::execute_compiled(const table & tab)
{
    ResultMap result;
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        result.insert(std::pair<std::pair<char, char>, ResultRow>(key, ResultRow()));
        auto& resultRow = result.at(key);
        int useRow = tab.l_shipdate[i] <= 904694400;
        resultRow.count_order += useRow;
        resultRow.sum_qty += tab.l_quantity[i] * useRow;
        resultRow.sum_base_price += tab.l_extendedprice[i] * useRow;
        resultRow.sum_disc_price += useRow * tab.l_extendedprice[i] * double(100 - tab.l_discount[i]) / 100.0;
        resultRow.sum_charge += useRow * tab.l_extendedprice[i] * double(100 - tab.l_discount[i]) / 100.0 * double(100 + tab.l_tax[i]) / 100.0;
        resultRow.avg_disc += useRow * tab.l_discount[i];
    }
    // calculate averages
    for (auto& resultRow : result) {
        auto& rr = resultRow.second;
        rr.avg_qty = double(rr.sum_qty) / double(rr.count_order);
        rr.avg_price = double(rr.sum_base_price) / double(rr.count_order);
        rr.avg_disc /= double(rr.count_order);
    }
    return result;
}

std::vector<BITMAP_TYPE> QueryOne::op_shipdate_se(const table&__restrict tab) __restrict {
    std::vector<BITMAP_TYPE> bitmap(tab.l_shipdate.size());
    int size = tab.l_shipdate.size();
    for (int i = 0; i < size; i++) {
        bitmap[i] = tab.l_shipdate[i] <= 904694400;
    }
    return bitmap;
}


ResultMap QueryOne::op_group_returnflag_linestatus(const table& tab, const std::vector<BITMAP_TYPE>& bitmap) {
    ResultMap result;
    int size = tab.l_shipdate.size();
    for (int i = 0; i < size; i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        result.insert(std::pair<std::pair<char, char>, ResultRow>(key, ResultRow()));
    }
    return result;
}

void QueryOne::op_sum_qty(const table& tab, const std::vector<BITMAP_TYPE>& bitmap, ResultMap& groups)
{
    int size = tab.l_shipdate.size();
    for (int i = 0; i < size; i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_qty = db_plus(group.sum_qty,db_times((int)bitmap[i], tab.l_quantity[i]));
    }
}

void QueryOne::op_sum_base_price(const table & tab, const std::vector<BITMAP_TYPE>& bitmap, ResultMap& groups)
{
    int size = tab.l_shipdate.size();
    for (int i = 0; i < size; i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_base_price = db_plus(group.sum_base_price,db_times((int)bitmap[i], tab.l_extendedprice[i]));
    }
}

void QueryOne::op_sum_disk_price(const table & tab, const std::vector<BITMAP_TYPE>& bitmap, ResultMap& groups)
{
    int size = tab.l_shipdate.size();
    for (int i = 0; i < size; i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_disc_price = db_plus(group.sum_disc_price,db_times((int)bitmap[i], db_times(tab.l_extendedprice[i], db_minus(100,tab.l_discount[i]))));
    }
}

void QueryOne::op_sum_charge(const table & tab, const std::vector<BITMAP_TYPE>& bitmap, ResultMap& groups)
{
    int size = tab.l_shipdate.size();
    for (int i = 0; i < size; i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        auto currentCharge = db_times(tab.l_extendedprice[i], double(db_times(db_minus(100,tab.l_discount[i]),db_minus(100,tab.l_tax[i])))  / 10000.0);
        group.sum_charge = db_plus(group.sum_charge, db_times(currentCharge, (int)bitmap[i]));
    }
}

void QueryOne::op_avg_qty(const table & tab, ResultMap& groups)
{
    for (auto& group : groups) {
        group.second.avg_qty = db_divided(double(group.second.sum_qty),double(group.second.count_order));
    }
}

void QueryOne::op_avg_price(const table & tab, ResultMap& groups)
{
    for (auto& group : groups) {
        group.second.avg_price = db_divided(double(group.second.sum_base_price),double(group.second.count_order));
    }
}
 
void QueryOne::op_avg_disc(const table & tab, const std::vector<BITMAP_TYPE>& bitmap, ResultMap& groups)
{
    int size = tab.l_shipdate.size();
    for (int i = 0; i < size; i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.avg_disc = db_plus(group.avg_disc,db_times(tab.l_discount[i], (int)bitmap[i]));
    }
    for (auto& group : groups) {
        group.second.avg_disc = db_divided(group.second.avg_disc,double(group.second.count_order));
    }
}

void QueryOne::op_count_order(const table & tab, const std::vector<BITMAP_TYPE>& bitmap, ResultMap& groups)
{
    int size = tab.l_shipdate.size();
    for (int i = 0; i < size; i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.count_order = db_plus(group.count_order,bitmap[i]);
    }
}
