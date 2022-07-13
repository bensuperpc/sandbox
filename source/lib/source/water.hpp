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

  std::unique_ptr<cell> create() override;
  void class_name() override;
};

}  // namespace benlib
#endif
