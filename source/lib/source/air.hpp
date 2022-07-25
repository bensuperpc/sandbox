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

  std::unique_ptr<cell> create();
  std::unique_ptr<cell> clone();

  std::string class_name() const;
  constexpr uint64_t get_id() const;
};
}  // namespace benlib
#endif
