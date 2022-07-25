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
  // virtual cell();
  virtual ~cell();
  // virtual void update() = 0;
  virtual std::unique_ptr<cell> create() = 0;
  virtual std::unique_ptr<cell> clone() = 0;
  // virtual std::unique_ptr<cell> update(const uint64_t x, const uint64_t y) = 0;

  virtual std::string class_name() const = 0;
  virtual uint64_t get_id() const = 0;

protected:
  bool gravity;
  bool border = 0;
};

}  // namespace benlib
#endif
