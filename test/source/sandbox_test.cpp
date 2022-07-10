#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "sandbox" ? 0 : 1;
}
