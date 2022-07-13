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

  std::unique_ptr<cell> create() override;

  std::string class_name() const override;
};
}  // namespace benlib
#endif
