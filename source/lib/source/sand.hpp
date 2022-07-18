#ifndef BENLIB_SAND_HPP_
#define BENLIB_SAND_HPP_

#include "cell.hpp"

namespace benlib
{
class sand : public cell
{
public:
  sand();
  ~sand();

  std::unique_ptr<cell> create();
  std::unique_ptr<cell> clone();

  std::string class_name() const;
  uint64_t get_id() const;
};

}  // namespace benlib
#endif
