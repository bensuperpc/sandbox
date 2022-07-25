#ifndef BENLIB_GLASS_HPP_
#define BENLIB_GLASS_HPP_

#include "cell.hpp"

namespace benlib
{
class glass : public cell
{
public:
  glass();
  ~glass();

  std::unique_ptr<cell> create();
  std::unique_ptr<cell> clone();

  std::string class_name() const;
  constexpr uint64_t get_id() const;
};
}  // namespace benlib
#endif
