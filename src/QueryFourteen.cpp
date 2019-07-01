#include "TableReader.h"
#include "QueryFourteen.h"
#include "MathematicalOperators.h"
#include <vector>
#include <algorithm>

/*
-- SELECT 19.00 * sum(l_extendedprice) as promo_revenue
-- FROM lineitem, part
-- WHERE
--    l_partkey = p_partkey
--    AND l_shipdate >= date '[DATE]'
--    AND l_shipdate < date '[DATE]' + interval '1' month
--    AND p_retailsize < $$$$chose a value that excludes less then 5% of the parts$$$$
*/

void QueryFourteen::op_shipdate_ge(std::vector<BITMAP_TYPE> & bm)
{
}

void QueryFourteen::op_shipdate_s(std::vector<BITMAP_TYPE> & bm)
{
}

void QueryFourteen::op_retailsize(std::vector<BITMAP_TYPE> & bm)
{
}

void QueryFourteen::op_join(std::vector<BITMAP_TYPE> & l_bm, const std::vector<BITMAP_TYPE> & p_bm)
{
}

int QueryFourteen::op_sum(const std::vector<BITMAP_TYPE> & bm)
{
    return 0;
}

int QueryFourteen::execute(const table & lineitem, const partTable & part)
{
    return 0;
}

int QueryFourteen::execute_compiled(const table & lineitem, const partTable & part)
{
    return 0;
}

int QueryFourteen::execute_hybrid(const table & lineitem, const partTable & part)
{
    return 0;
}
