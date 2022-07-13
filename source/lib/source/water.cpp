#include "water.hpp"

benlib::water::water()
{
  gravity = true;
  id = 1;
}

benlib::water::~water() {}

benlib::cell * benlib::water::create()
{
  return new water();
}

void benlib::water::class_name()
{
  std::cout << "water" << std::endl;
}
