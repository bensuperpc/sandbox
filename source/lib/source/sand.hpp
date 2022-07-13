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

  std::unique_ptr<cell> create() override;

  std::string class_name() const override;
};

}  // namespace benlib
#endif
