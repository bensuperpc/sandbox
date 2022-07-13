#include "water.hpp"

benlib::water::water()
{
  gravity = true;
  id = 1;
}

benlib::water::~water() {}

std::unique_ptr<benlib::cell> benlib::water::create()
{
  return std::make_unique<water>();
}

void benlib::water::class_name()
{
  std::cout << "water" << std::endl;
}
