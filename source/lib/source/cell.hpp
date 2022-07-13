#ifndef BENLIB_CELL_HPP_
#define BENLIB_CELL_HPP_

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace benlib
{
class cell
{
public:
  cell();
  ~cell();
  uint64_t get_id();
  void set_id(uint64_t _id);
  // virtual void update() = 0;
  virtual cell* create();

  virtual void class_name();

protected:
  bool gravity = false;
  bool border = false;
  uint64_t id = 0;
};

}  // namespace benlib
#endif
