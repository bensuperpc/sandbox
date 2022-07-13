#include "air.hpp"

benlib::air::air()
{
  id = 0;
  // map_type[id] = *this;
}

benlib::air::~air() {}

benlib::cell * benlib::air::create()
{
  std::cout << "air" << std::endl;
  return new air();
}

void benlib::air::class_name()
{
  std::cout << "air" << std::endl;
}
