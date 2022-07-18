#include "glass.hpp"

benlib::glass::glass() {}

benlib::glass::~glass() {}

std::unique_ptr<benlib::cell> benlib::glass::create()
{
  return std::make_unique<benlib::glass>();
}

std::unique_ptr<benlib::cell> benlib::glass::clone()
{
  auto obj = std::make_unique<benlib::glass>();
  obj->gravity = this->gravity;
  return std::move(obj);
}

std::string benlib::glass::class_name() const
{
  return "glass";
}

uint64_t benlib::glass::get_id() const
{
  return 5;
}
