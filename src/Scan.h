#pragma once
#include "TableReader.h"

table filterTable(const std::vector<bool>& bitmap, const table& oldTable);

template <typename T>
void filterColumn(const std::vector<bool>& bitmap, std::vector<T>& newColumn, const std::vector<T>& oldColumn);

table filterValuesSmaller(const table& oldTable, std::vector<int>& column, int value);

