#include "TableReader.h"
#include "QueryFourteen.h"
#include "MathematicalOperators.h"
#include <vector>
#include <algorithm>
#include<unordered_map>

/*
-- SELECT 19.00 * sum(l_extendedprice) as promo_revenue
-- FROM lineitem, part
-- WHERE
--    l_partkey = p_partkey
--    AND l_shipdate >= date '[DATE]'
--    AND l_shipdate < date '[DATE]' + interval '1' month
--    AND p_retailsize < $$$$chose a value that excludes less then 5% of the parts$$$$
*/

void QueryFourteen::op_shipdate_ge(const table& tab, std::vector<BITMAP_TYPE> & bitmap)
{
    int size = bitmap.size();
#pragma GCC ivdep
#pragma ivdep
    for (int i = 0; i < size; i++) {
        // TODO: Insert correct date here
        bitmap[i] = bitmap[i] * (tab.l_shipdate[i] >= 757382400);
    }
}

void QueryFourteen::op_shipdate_s(const table& tab, std::vector<BITMAP_TYPE> & bitmap)
{
    int size = bitmap.size();
#pragma GCC ivdep
#pragma ivdep
    for (int i = 0; i < size; i++) {
        // TODO: Insert correct date here
        bitmap[i] = bitmap[i] * (tab.l_shipdate[i] < 757382400);
    }
}

void QueryFourteen::op_retailsize(const partTable& tab, std::vector<BITMAP_TYPE> & bitmap)
{
    int size = bitmap.size();
#pragma GCC ivdep
#pragma ivdep
    for (int i = 0; i < size; i++) {
        bitmap[i] = bitmap[i] * (tab.p_retailPrice[i] >= 100000); // more than 5% for small datasets, but less than 5 percent for big datasets --> 2.5% for scale = 1
    }
}

std::vector<int> QueryFourteen::op_join(const partTable& p_tab, const table& l_tab, const std::vector<BITMAP_TYPE> & l_bitmap, const std::vector<BITMAP_TYPE> & p_bitmap)
{
    int l_size = l_tab.l_shipdate.size();
    int p_size = p_tab.p_partkey.size();
    std::vector<int> l_counts(l_size, 0);
#pragma GCC ivdep
#pragma ivdep
    // this map counts the appearance of every value
    std::unordered_map<int, int> p_counts;
    for (int i = 0; i < p_size; i++) {
        auto key = p_tab.p_partkey[i];
        // if the key already exists, this insertion is ignored
        p_counts.insert(std::pair<int, int>(key, 0));
        // if the element is still in the table, the number of its occurances is counted up
        p_counts.at(key) += p_bitmap[i];
    }
    for (int i = 0; i < l_size; i++) {
        // count all possible combinations of partkeys for the elements still in the lineitem table
        l_counts[i] = dp_plus(l_counts[i], db_times(l_bitmap[i], p_counts.at(l_tab.l_partkey[i])));
    }
    return l_counts;
}

int QueryFourteen::op_sum(const table& tab, const std::vector<int> & counts)
{
    int size = counts.size();
#pragma GCC ivdep
#pragma ivdep
    int sum = 0;
    for (int i = 0; i < size; i++) {
        // TODO: Insert correct date here
        sum = db_plus(sum, db_times(counts[i],tab.l_extendedprice[i]));
    }
    return sum;
}

int QueryFourteen::execute(const table& l_tab, const partTable & p_tab)
{
    int l_size = l_tab.l_shipdate.size();
    int p_size = p_tab.p_partkey.size();
    std::vector<BITMAP_TYPE> l_bitmap(l_size, 1);
    std::vector<BITMAP_TYPE> p_bitmap(p_size, 1);

    op_shipdate_ge(l_tab, l_bitmap);
    op_shipdate_ge(l_tab, l_bitmap);
    op_retailsize(p_tab, p_bitmap);
    auto counts = op_join(p_tab, l_tab, l_bitmap, p_bitmap);
    auto sum = op_sum(l_tab, counts);
    return db_times(19.00, sum);
}

int QueryFourteen::execute_compiled(const table& lineitem, const partTable & part)
{
    return 0;
}

int QueryFourteen::execute_hybrid(const table & lineitem, const partTable & part)
{
    return 0;
}
