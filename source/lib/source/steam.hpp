#ifndef BENLIB_STEAM_HPP_
#define BENLIB_STEAM_HPP_

#include "cell.hpp"

namespace benlib
{
class steam : public cell
{
public:
  steam();
  ~steam();

  std::unique_ptr<cell> create();
  std::unique_ptr<cell> clone();

  std::string class_name() const;
  uint64_t get_id() const;
};
}  // namespace benlib
#endif
