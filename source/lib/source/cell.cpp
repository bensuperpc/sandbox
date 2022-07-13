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
  return std::move(std::make_unique<cell>());
}

std::string benlib::cell::class_name() const
{
  return "cell";
}
