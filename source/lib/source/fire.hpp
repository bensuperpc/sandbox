#ifndef BENLIB_FIRE_HPP_
#define BENLIB_FIRE_HPP_

#include "cell.hpp"

namespace benlib
{
class fire : public cell
{
public:
  fire();
  ~fire();

  std::unique_ptr<cell> create();
  std::unique_ptr<cell> clone();

  std::string class_name() const;
  uint64_t get_id() const;
};
}  // namespace benlib
#endif
