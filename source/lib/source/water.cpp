#include "water.hpp"

benlib::water::water()
{
  gravity = true;
}

benlib::water::~water() {}

std::unique_ptr<benlib::cell> benlib::water::create()
{
  return std::make_unique<benlib::water>();
}

std::unique_ptr<benlib::cell> benlib::water::clone()
{
  auto obj = std::make_unique<benlib::water>();
  obj->gravity = this->gravity;
  return std::move(obj);
}

std::string benlib::water::class_name() const
{
  return "water";
}

uint64_t benlib::water::get_id() const
{
  return 1;
}
