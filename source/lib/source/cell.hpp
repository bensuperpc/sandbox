#ifndef BENLIB_CELL_HPP_
#define BENLIB_CELL_HPP_

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace benlib
{
class cell
{
public:
  cell();
  ~cell();

protected:
  bool gravity = false;
  bool border = false;
  uint64_t id = 0;
};

}  // namespace benlib
#endif
