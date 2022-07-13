#ifndef BENLIB_AIR_HPP_
#define BENLIB_AIR_HPP_

#include "cell.hpp"

namespace benlib
{
class air : public virtual cell
{
public:
  air();
  ~air();
  cell *create() override;
  void class_name() override;
  
};
}  // namespace benlib
#endif