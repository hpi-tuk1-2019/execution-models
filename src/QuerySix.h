#include "TableReader.h"

class QuerySix {
  private:
    std::vector<int> op_shipdate_ge(const table& tab, std::vector<int> old_inds);
    double op_agg_sum(const table& tab, std::vector<int> old_inds);
    std::vector<int> op_shipdate_s(const table& tab, std::vector<int> old_inds);
    std::vector<int> op_quantity_s(const table& tab, std::vector<int> old_inds);
    std::vector<int> op_discount_ge(const table& tab, std::vector<int> old_inds);
    std::vector<int> op_discount_se(const table& tab, std::vector<int> old_inds);
  public:
    double execute(const table& tab);
};
