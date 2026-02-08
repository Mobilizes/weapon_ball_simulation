#ifndef PARTITION_HPP
#define PARTITION_HPP

#include "weapon_ball/utils/constants.hpp"

#include <vector>

template <typename T>
class DynamicPartition
{
public:
  DynamicPartition() : partition(UNIFORM_PARTITION_ROW * UNIFORM_PARTITION_COL) {}

  std::vector<T> & get(int row, int col) { return partition[row * UNIFORM_PARTITION_COL + col]; }

private:
  std::vector<std::vector<T>> partition;
};

#endif  // PARTITION_HPP
