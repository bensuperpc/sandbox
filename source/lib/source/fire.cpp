#include "fire.hpp"

benlib::fire::fire()
{
  id = 2;
}

benlib::fire::~fire() {}

benlib::cell * benlib::fire::create()
{
  return new fire();
}

void benlib::fire::class_name()
{
  std::cout << "fire" << std::endl;
}
