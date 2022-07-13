#ifndef BENLIB_CELL_HPP_
#define BENLIB_CELL_HPP_

#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
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
  virtual std::unique_ptr<cell> create();

  virtual std::string class_name() const;

protected:
  bool gravity = false;
  bool border = false;
  uint64_t id = 0;
};

}  // namespace benlib
#endif
