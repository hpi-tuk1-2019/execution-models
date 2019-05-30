#include "TableReader.h"
#include "QueryOne.h"
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
        bool useRow = bitmap[i];
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
        bool useRow = tab.l_shipdate[i] <= 904694400;
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

std::vector<bool> QueryOne::op_shipdate_se(const table& tab) {
    std::vector<bool> bitmap(tab.l_shipdate.size());
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        bitmap[i] = tab.l_shipdate[i] <= 904694400;
    }
    return bitmap;
}


ResultMap QueryOne::op_group_returnflag_linestatus(const table& tab, const std::vector<bool>& bitmap) {
    ResultMap result;  
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        result.insert(std::pair<std::pair<char, char>, ResultRow>(key, ResultRow()));
    }
    return result;
}

void QueryOne::op_sum_qty(const table & tab, const std::vector<bool>& bitmap, ResultMap& groups)
{
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_qty += bitmap[i] * tab.l_quantity[i];
    }
}

void QueryOne::op_sum_base_price(const table & tab, const std::vector<bool>& bitmap, ResultMap& groups)
{
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_base_price += bitmap[i] * tab.l_extendedprice[i];
    }
}

void QueryOne::op_sum_disk_price(const table & tab, const std::vector<bool>& bitmap, ResultMap& groups)
{
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_disc_price += bitmap[i] * tab.l_extendedprice[i] * (100 - tab.l_discount[i]);
    }
}

void QueryOne::op_sum_charge(const table & tab, const std::vector<bool>& bitmap, ResultMap& groups)
{
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        auto currentCharge = tab.l_extendedprice[i] * double(100 - tab.l_discount[i]) / 100.0 * double(100 + tab.l_tax[i]) / 100.0;
        group.sum_charge += currentCharge * bitmap[i];
    }
}

void QueryOne::op_avg_qty(const table & tab, ResultMap& groups)
{
    for (auto& group : groups) {
        group.second.avg_qty = double(group.second.sum_qty)/double(group.second.count_order);
    }
}

void QueryOne::op_avg_price(const table & tab, ResultMap& groups)
{
    for (auto& group : groups) {
        group.second.avg_price = double(group.second.sum_base_price)/double(group.second.count_order);
    }
}

void QueryOne::op_avg_disc(const table & tab, const std::vector<bool>& bitmap, ResultMap& groups)
{
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.avg_disc += tab.l_discount[i] * bitmap[i];
    }
    for (auto& group : groups) {
        group.second.avg_disc /= double(group.second.count_order);
    }
}

void QueryOne::op_count_order(const table & tab, const std::vector<bool>& bitmap, ResultMap& groups)
{
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.count_order += bitmap[i];
    }
}
/*
std::vector<int> QueryOne::op_sort_returnflag_linestatus(const table& tab, const std::vector<int> old_inds){
    std::sort(old_inds.begin(), old_inds.end(), [tab](const auto a, const auto b) {
        if (tab.l_returnflag[a] == tab.l_returnflag[b]) {
            return tab.l_linestatus[a] < tab.l_linestatus[b];
        }
        return tab.l_returnflag[a] < tab.l_returnflag[b];
    });
    return old_inds;
}
*/

