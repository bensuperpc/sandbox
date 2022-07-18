#include "steam.hpp"

benlib::steam::steam() {}

benlib::steam::~steam() {}

std::unique_ptr<benlib::cell> benlib::steam::create()
{
  return std::make_unique<benlib::steam>();
}

std::unique_ptr<benlib::cell> benlib::steam::clone()
{
  auto obj = std::make_unique<benlib::steam>();
  obj->gravity = this->gravity;
  return std::move(obj);
}

std::string benlib::steam::class_name() const
{
  return "steam";
}

uint64_t benlib::steam::get_id() const
{
  return 4;
}
