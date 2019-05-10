#include "TableReader.h"

class QuerySix {
  private:
    std::vector<int> op_shipdate_ge(table *tab, std::vector<int> old_inds);
    double op_agg_sum(table *tab, std::vector<int> old_inds);
    std::vector<int> op_shipdate_s(table *tab, std::vector<int> old_inds);
    std::vector<int> op_quantity_s(table *tab, std::vector<int> old_inds);
    std::vector<int> op_discount_between(table *tab, std::vector<int> old_inds);
  public:
    double execute(table *tab);
};
