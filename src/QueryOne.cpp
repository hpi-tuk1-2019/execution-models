#include "TableReader.h"
#include "QueryOne.h"
#include <vector>
#include <algorithm>


ResultMap QueryOne::execute(const table& tab){
    auto filteredIndices = op_shipdate_se(tab);
    auto groups = op_group_returnflag_linestatus(tab, filteredIndices);
    groups = op_sum_qty(tab, filteredIndices, groups);
    groups = op_sum_qty(tab, filteredIndices, groups);
    groups = op_sum_base_price(tab, filteredIndices, groups);
    groups = op_sum_disk_price(tab, filteredIndices, groups);
    groups = op_sum_charge(tab, filteredIndices, groups);
    groups = op_avg_qty(tab, filteredIndices, groups);
    groups = op_avg_price(tab, filteredIndices, groups);
    groups = op_avg_disc(tab, filteredIndices, groups);
    groups = op_count_order(tab, filteredIndices, groups);
  
    return groups;
}

ResultMap QueryOne::execute_compiled(const table & tab)
{
    ResultMap result;
    for (int i = 1; i < tab.l_shipdate.size(); i++) {
        if (tab.l_shipdate[i] > 904694400) {
            continue;
        }
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        if (result.count(key) == 0) {
            result.insert(std::pair<std::pair<char, char>, ResultRow>(key, ResultRow()));
        }
        auto& resultRow = result.at(key);
        resultRow.count_order++;
        resultRow.sum_qty += tab.l_quantity[i];
        resultRow.sum_base_price += tab.l_extendedprice[i];
        resultRow.sum_disc_price += tab.l_extendedprice[i] * double(100 - tab.l_discount[i]) / 100.0;
        resultRow.sum_charge += tab.l_extendedprice[i] * double(100 - tab.l_discount[i]) / 100.0 * double(100 + tab.l_tax[i]) / 100.0;
        resultRow.avg_disc += tab.l_discount[i];
    }
    // calculate averages
    for (auto& resultRow : result) {
        auto& rr = resultRow.second;
        rr.avg_qty = (double(rr.sum_qty) / rr.count_order);
        rr.avg_price = (double(rr.sum_base_price) / rr.count_order);
        rr.avg_disc = (double(rr.sum_disc_price) / rr.count_order);
    }
    return result;
}

std::vector<int> QueryOne::op_shipdate_se(const table& tab) {
    std::vector<int> indices;
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        if (tab.l_shipdate[i] <= 904694400) {
            indices.push_back(i);
        }
    }
    return indices;
}


ResultMap QueryOne::op_group_returnflag_linestatus(const table& tab, std::vector<int> old_inds) {
    ResultMap result;  
    for (auto i: old_inds) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        if (result.count(key) == 0) {
            result.insert(std::pair<std::pair<char, char>, ResultRow>(key, ResultRow()));
        }
    }
    return result;
}

ResultMap QueryOne::op_sum_qty(const table & tab, std::vector<int> old_inds, ResultMap groups)
{
    for (auto i: old_inds) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_qty += tab.l_quantity[i];
    }
    return groups;
}

ResultMap QueryOne::op_sum_base_price(const table & tab, std::vector<int> old_inds, ResultMap groups)
{
    for (auto i: old_inds) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_base_price += tab.l_extendedprice[i];
    }
    return groups;
}

ResultMap QueryOne::op_sum_disk_price(const table & tab, std::vector<int> old_inds, ResultMap groups)
{
    for (auto i : old_inds) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_disc_price += tab.l_extendedprice[i] * (100 - tab.l_discount[i]);
    }
    return groups;
}

ResultMap QueryOne::op_sum_charge(const table & tab, std::vector<int> old_inds, ResultMap groups)
{
    for (auto i : old_inds) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.sum_charge += tab.l_extendedprice[i] * double(100 - tab.l_discount[i]) / 100.0 * double(100 + tab.l_tax[i]) / 100.0;
    }
    return groups;
}

ResultMap QueryOne::op_avg_qty(const table & tab, std::vector<int> old_inds, ResultMap groups)
{
    // needs to be the first avg function called because of count
    for (auto i : old_inds) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.avg_qty += tab.l_quantity[i];
        group.count_order++;
    }
    for (auto& group : groups) {
        group.second.avg_qty /= double(group.second.count_order);
    }
    return groups;
}

ResultMap QueryOne::op_avg_price(const table & tab, std::vector<int> old_inds, ResultMap groups)
{
    for (auto i : old_inds) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.avg_price += tab.l_extendedprice[i];
    }
    for (auto& group : groups) {
        group.second.avg_price /= double(group.second.count_order);
    }
    return groups;
}

ResultMap QueryOne::op_avg_disc(const table & tab, std::vector<int> old_inds, ResultMap groups)
{
    for (auto i : old_inds) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.avg_disc += tab.l_discount[i];
    }
    for (auto& group : groups) {
        group.second.avg_disc /= double(group.second.count_order);
    }
    return groups;
}

ResultMap QueryOne::op_count_order(const table & tab, std::vector<int> old_inds, ResultMap groups)
{
    for (auto& group : groups) {
        group.second.count_order = 0;
    }
    for (auto i : old_inds) {
        auto key = std::pair<char, char>(tab.l_returnflag[i], tab.l_linestatus[i]);
        auto& group = groups.at(key);
        group.count_order++;
    }
    
    return groups;
}
/*
std::vector<int> QueryOne::op_sort_returnflag_linestatus(const table& tab, std::vector<int> old_inds){
    std::sort(old_inds.begin(), old_inds.end(), [tab](const auto a, const auto b) {
        if (tab.l_returnflag[a] == tab.l_returnflag[b]) {
            return tab.l_linestatus[a] < tab.l_linestatus[b];
        }
        return tab.l_returnflag[a] < tab.l_returnflag[b];
    });
    return old_inds;
}
*/

