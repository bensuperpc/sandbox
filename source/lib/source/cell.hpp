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
  // virtual void update() = 0;
  virtual std::unique_ptr<cell> create();
  virtual std::unique_ptr<cell> clone();

  virtual std::string class_name() const;
  virtual const uint64_t get_id() const;

protected:
  bool gravity = false;
  bool border = false;
};

}  // namespace benlib
#endif
