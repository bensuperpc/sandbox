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
  std::string class_name() const override;
};

}  // namespace benlib
#endif
