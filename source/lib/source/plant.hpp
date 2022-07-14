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

  std::unique_ptr<cell> create() override;
  std::unique_ptr<cell> clone() override;

  std::string class_name() const override;
  const uint64_t get_id() const override;
};
}  // namespace benlib
#endif
