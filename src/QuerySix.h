#include "TableReader.h"

class QuerySix {
  private:
    void op_shipdate_ge(const table& tab, std::vector<bool>& bitmap);
    double op_agg_sum(const table& tab, std::vector<bool>& bitmap);
    void op_shipdate_s(const table& tab, std::vector<bool>& bitmap);
    void op_quantity_s(const table& tab, std::vector<bool>& bitmap);
    void op_discount_ge(const table& tab, std::vector<bool>& bitmap);
    void op_discount_se(const table& tab, std::vector<bool>& bitmap);
  public:
    double execute(const table& tab);
    double execute_compiled(const table& tab);
    double execute_hybrid(const table& tab);
};
