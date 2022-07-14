#include "air.hpp"

benlib::air::air() {}

benlib::air::~air() {}

std::unique_ptr<benlib::cell> benlib::air::create()
{
  return std::move(std::make_unique<benlib::air>());
}

std::unique_ptr<benlib::cell> benlib::air::clone()
{
  auto obj = std::make_unique<benlib::air>();
  obj->gravity = this->gravity;
  return std::move(obj);
}

std::string benlib::air::class_name() const
{
  return "air";
}

const uint64_t benlib::air::get_id() const
{
  return 0;
}
