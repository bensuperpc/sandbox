#include "cell.hpp"

benlib::cell::cell() {}

benlib::cell::~cell() {}

const uint64_t benlib::cell::get_id() const
{
  return 0;
}

std::unique_ptr<benlib::cell> benlib::cell::create()
{
  return std::move(std::make_unique<cell>());
}

std::unique_ptr<benlib::cell> benlib::cell::clone()
{
  return std::make_unique<benlib::cell>(*this);
}

std::string benlib::cell::class_name() const
{
  return "cell";
}
