#include "cell.hpp"

benlib::cell::cell() {}

benlib::cell::~cell() {}

uint64_t benlib::cell::get_id()
{
  return id;
}

void benlib::cell::set_id(uint64_t _id)
{
  this->id = _id;
}

std::unique_ptr<benlib::cell> benlib::cell::create()
{
  return std::make_unique<cell>();
}

void benlib::cell::class_name()
{
  std::cout << "cell" << std::endl;
}
