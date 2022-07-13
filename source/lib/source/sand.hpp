#ifndef BENLIB_SAND_HPP_
#define BENLIB_SAND_HPP_

#include "cell.hpp"

namespace benlib
{
class sand : public virtual cell
{
public:
  sand();
  ~sand();

  std::unique_ptr<cell> create() override;

  void class_name() override;
};

}  // namespace benlib
#endif
