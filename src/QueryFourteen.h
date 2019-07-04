#pragma once
#include "TableReader.h"
#include <map>

/*
-- SELECT 19.00 * sum(l_extendedprice) as promo_revenue
-- FROM lineitem, part
-- WHERE
--    l_partkey = p_partkey
--    AND l_shipdate >= date '[DATE]'
--    AND l_shipdate < date '[DATE]' + interval '1' month
--    AND p_retailsize < $$$$chose a value that excludes less then 5% of the parts$$$$
*/

class QueryFourteen {
  private:
      void op_shipdate_ge(const table& tab, std::vector<BITMAP_TYPE>& bitmap);
      void op_shipdate_s(const table& tab, std::vector<BITMAP_TYPE>& bitmap);
      void op_retailsize(const partTable& tab, std::vector<BITMAP_TYPE>& bitmap);
      std::vector<int> op_join(const partTable& p_tab, const table& l_tab, const std::vector<BITMAP_TYPE>& l_bitmap, const std::vector<BITMAP_TYPE>& p_bitmap);
      int op_sum(const table& tab, const std::vector<int>& counts);

  public:
    int execute(const table& lineitem, const partTable& part);
    int execute_compiled(const table& lineitem, const partTable& part);
    int execute_hybrid(const table& lineitem, const partTable& part);
};
