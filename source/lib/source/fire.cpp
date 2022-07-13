#include "fire.hpp"

benlib::fire::fire()
{
  id = 2;
}

benlib::fire::~fire() {}

std::unique_ptr<benlib::cell> benlib::fire::create()
{
  return std::make_unique<fire>();
}

void benlib::fire::class_name()
{
  std::cout << "fire" << std::endl;
}
