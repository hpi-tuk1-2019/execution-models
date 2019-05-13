#include "TableReader.h"

class QueryOne {
  private:
    std::vector<int> op_shipdate_se(const table& tab, std::vector<int> old_inds);
    std::vector<int> op_aggregate(const table& tab, std::vector<int> old_inds, std::vector<int> groups);
    std::vector<int> op_sort_returnflag_linestatus(const table& tab, std::vector<int> old_inds);
    std::vector<int> op_group_returnflag_linestatus(const table& tab, std::vector<int> old_inds);
  public:
    double execute(const table& tab);
};
