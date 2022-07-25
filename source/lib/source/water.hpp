#ifndef BENLIB_WATER_HPP_
#define BENLIB_WATER_HPP_

#include "cell.hpp"

namespace benlib
{
class water : public cell
{
public:
  water();
  ~water();

  std::unique_ptr<cell> create();
  std::unique_ptr<cell> clone();

  std::string class_name() const;
  constexpr uint64_t get_id() const;
};

}  // namespace benlib
#endif
