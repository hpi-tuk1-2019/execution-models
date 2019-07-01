#pragma once
#include "TableReader.h"
#include <map>
#define BITMAP_TYPE int

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
      void op_shipdate_ge(std::vector<BITMAP_TYPE>& bm);
      void op_shipdate_s(std::vector<BITMAP_TYPE>& bm);
      void op_retailsize(std::vector<BITMAP_TYPE>& bm);
      void op_join(std::vector<BITMAP_TYPE>& l_bm, const std::vector<BITMAP_TYPE>& p_bm);
      int op_sum(const std::vector<BITMAP_TYPE>& bm);

  public:
    int execute(const table& lineitem, const partTable& part);
    int execute_compiled(const table& lineitem, const partTable& part);
    int execute_hybrid(const table& lineitem, const partTable& part);
};
