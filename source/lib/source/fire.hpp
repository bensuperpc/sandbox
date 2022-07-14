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
  std::unique_ptr<cell> clone() override;

  std::string class_name() const override;

  const uint64_t get_id() const override;
};
}  // namespace benlib
#endif
