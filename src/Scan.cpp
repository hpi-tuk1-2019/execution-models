#include "Scan.h"

table filterTable(const std::vector<bool>& bitmap, const table & oldTable)
{
    table newTable;
    filterColumn(bitmap, newTable.l_orderkey, oldTable.l_orderkey);
    filterColumn(bitmap, newTable.l_partkey, oldTable.l_partkey);
    filterColumn(bitmap, newTable.l_suppkey, oldTable.l_suppkey);
    filterColumn(bitmap, newTable.l_linenumber, oldTable.l_linenumber);
    filterColumn(bitmap, newTable.l_quantity, oldTable.l_quantity);
    filterColumn(bitmap, newTable.l_extendedprice, oldTable.l_extendedprice);
    filterColumn(bitmap, newTable.l_discount, oldTable.l_discount);
    filterColumn(bitmap, newTable.l_tax, oldTable.l_tax);
    filterColumn(bitmap, newTable.l_returnflag, oldTable.l_returnflag);
    filterColumn(bitmap, newTable.l_linestatus, oldTable.l_linestatus);
    filterColumn(bitmap, newTable.l_shipdate, oldTable.l_shipdate);
    filterColumn(bitmap, newTable.l_commitdate, oldTable.l_commitdate);
    filterColumn(bitmap, newTable.l_receiptdate, oldTable.l_receiptdate);
    filterColumn(bitmap, newTable.l_shipinstruct, oldTable.l_shipinstruct);
    filterColumn(bitmap, newTable.l_shipmode, oldTable.l_shipmode);
    filterColumn(bitmap, newTable.l_comment, oldTable.l_comment);
    
    return newTable;
}

template <typename T>
void filterColumn(const std::vector<bool>& bitmap, std::vector<T>& newColumn, const std::vector<T>& oldColumn)
{
    for (int i = 0; i < bitmap.size(); ++i) {
        if (bitmap[i]) {
            newColumn.push_back(oldColumn[i]);
        }
    }
}

table filterValuesSmaller(const table& oldTable, std::vector<int>& column, int value)
{
    std::vector<bool> bitmap;
    for (auto& c : column) {
        bool isSmaller = c < value ? true : false;
        bitmap.push_back(isSmaller);        
    }

    table newTable = filterTable(bitmap, oldTable);
    return newTable;
}