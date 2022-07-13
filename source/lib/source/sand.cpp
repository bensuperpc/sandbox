#include "sand.hpp"

benlib::sand::sand()
{
  gravity = true;
  id = 3;
}

benlib::sand::~sand() {}

benlib::cell * benlib::sand::create()
{
  return new sand();
}

void benlib::sand::class_name()
{
  std::cout << "sand" << std::endl;
}
