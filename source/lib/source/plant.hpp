#ifndef BENLIB_PLANT_HPP_
#define BENLIB_PLANT_HPP_

#include "cell.hpp"

namespace benlib
{
class plant : public cell
{
public:
  plant();
  ~plant();

  std::unique_ptr<cell> create();
  std::unique_ptr<cell> clone();

  std::string class_name() const;
  uint64_t get_id() const;
};
}  // namespace benlib
#endif
