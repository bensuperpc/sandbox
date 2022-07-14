#include "fire.hpp"

benlib::fire::fire() {}

benlib::fire::~fire() {}

std::unique_ptr<benlib::cell> benlib::fire::create()
{
  return std::move(std::make_unique<benlib::fire>());
}

std::unique_ptr<benlib::cell> benlib::fire::clone()
{
  auto obj = std::make_unique<benlib::fire>();
  obj->gravity = this->gravity;
  return std::move(obj);
}

std::string benlib::fire::class_name() const
{
  return "fire";
}

const uint64_t benlib::fire::get_id() const
{
  return 2;
}
