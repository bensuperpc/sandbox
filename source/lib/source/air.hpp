#ifndef BENLIB_AIR_HPP_
#define BENLIB_AIR_HPP_

#include "cell.hpp"

namespace benlib
{
class air : public cell
{
public:
  air();
  ~air();

  std::unique_ptr<cell> create() override;
  std::string class_name() const override;
};
}  // namespace benlib
#endif
