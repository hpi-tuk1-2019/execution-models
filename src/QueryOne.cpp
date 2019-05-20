#include "TableReader.h"
#include "QueryOne.h"
#include <vector>
#include <algorithm>

ResultTable QueryOne::execute(const table& tab){
  ResultTable resultTable;
  std::vector<int> indices1 = op_shipdate_se(tab);
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

ResultTable QueryOne::execute_compiled(const table& tab) {
    std::vector<int> indices;
    for (int i = 0; i < tab.l_shipdate.size(); i++) {
        if (tab.l_shipdate[i] <= 904694400) {
            indices.push_back(i);
        }
    }
    std::sort(indices.begin(), indices.end(), [tab](const auto a, const auto b) {
        if (tab.l_returnflag[a] == tab.l_returnflag[b]) {
            return tab.l_linestatus[a] < tab.l_linestatus[b];
        }
        return tab.l_returnflag[a] < tab.l_returnflag[b];
    });
    ResultTable resultTable;
    resultTable.l_linestatus.push_back(tab.l_linestatus[indices[0]]);
    resultTable.l_returnflag.push_back(tab.l_returnflag[indices[0]]);
    // start aggregation for first group
    int count = 1;
    long long int qty_sum = tab.l_quantity[indices[0]];
    long long int sum_base_price = tab.l_extendedprice[indices[0]];
    long long int sum_disc_price = tab.l_extendedprice[indices[0]] * (100 - tab.l_discount[indices[0]]);
    long long int sum_charge = tab.l_extendedprice[indices[0]] * (100 - tab.l_discount[indices[0]]) * (100 + tab.l_tax[indices[0]]);
    long long int sum_disc = tab.l_discount[indices[0]];
    for (int i = 1; i < indices.size(); i++) {
        if ((tab.l_returnflag[indices[i]] != tab.l_returnflag[indices[i - 1]]) ||
            (tab.l_linestatus[indices[i]] != tab.l_linestatus[indices[i - 1]])) {
            // new group
            resultTable.l_linestatus.push_back(tab.l_linestatus[indices[i]]);
            resultTable.l_returnflag.push_back(tab.l_returnflag[indices[i]]);
            // values for the old group
            resultTable.sum_qty.push_back(qty_sum);
            resultTable.sum_base_price.push_back(sum_base_price);
            resultTable.sum_disc_price.push_back(sum_disc_price);
            resultTable.sum_charge.push_back(sum_charge);
            resultTable.avg_qty.push_back(double(qty_sum) / count);
            resultTable.avg_price.push_back(double(sum_base_price)/count);
            resultTable.avg_disc.push_back(double(sum_disc)/count);
            resultTable.count_order.push_back(count);
            // start aggregations for new group
            count = 1;
            qty_sum = tab.l_quantity[indices[i]];
            sum_base_price = tab.l_extendedprice[indices[i]];
            sum_disc_price = tab.l_extendedprice[indices[i]] * (100 - tab.l_discount[indices[i]]);
            sum_charge = tab.l_extendedprice[indices[i]] * (100 - tab.l_discount[indices[i]]) * (100 + tab.l_tax[indices[i]]);
            sum_disc = tab.l_discount[indices[i]];
        }
        else 
        {
            // aggregate group values
            count++;
            qty_sum += tab.l_quantity[indices[i]];
            sum_base_price += tab.l_extendedprice[indices[i]];
            sum_disc_price += tab.l_extendedprice[indices[i]] * (100 - tab.l_discount[indices[i]]);
            sum_charge += tab.l_extendedprice[indices[i]] * (100 - tab.l_discount[indices[i]]) * (100 + tab.l_tax[indices[i]]);
            sum_disc += tab.l_discount[indices[i]];
        }
    }
    // values for the last group
    resultTable.sum_qty.push_back(qty_sum);
    resultTable.sum_base_price.push_back(sum_base_price);
    resultTable.sum_disc_price.push_back(sum_disc_price);
    resultTable.sum_charge.push_back(sum_charge);
    resultTable.avg_qty.push_back(double(qty_sum) / count);
    resultTable.avg_price.push_back(double(sum_base_price) / count);
    resultTable.avg_disc.push_back(double(sum_disc) / count);
    resultTable.count_order.push_back(count);
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
    std::sort(old_inds.begin(), old_inds.end(), [tab](const auto a, const auto b) {
        if (tab.l_returnflag[a] == tab.l_returnflag[b]) {
            return tab.l_linestatus[a] < tab.l_linestatus[b];
        }
        return tab.l_returnflag[a] < tab.l_returnflag[b];
    });
    return old_inds;
}

std::vector<int> QueryOne::op_shipdate_se(const table& tab){
  std::vector<int> indices;
  for (int i = 0; i < tab.l_shipdate.size(); i++) {
    if (tab.l_shipdate[i] <= 904694400) {
      indices.push_back(i);
    }
  }
  return indices;
}
