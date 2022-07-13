#include "air.hpp"

benlib::air::air()
{
  id = 0;
}

benlib::air::~air() {}

std::unique_ptr<benlib::cell> benlib::air::create()
{
  return std::move(std::make_unique<air>());
}

void benlib::air::class_name()
{
  std::cout << "air" << std::endl;
}
