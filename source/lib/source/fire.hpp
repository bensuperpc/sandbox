#ifndef BENLIB_FIRE_HPP_
#define BENLIB_FIRE_HPP_

#include "cell.hpp"

namespace benlib
{
class fire : public virtual cell
{
public:
  fire();
  ~fire();

  cell *create() override;

  void class_name() override;
};
}  // namespace benlib
#endif
