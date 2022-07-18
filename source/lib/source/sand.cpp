#include "sand.hpp"

benlib::sand::sand()
{
  gravity = true;
}

benlib::sand::~sand() {}

std::unique_ptr<benlib::cell> benlib::sand::create()
{
  return std::make_unique<benlib::sand>();
}

std::unique_ptr<benlib::cell> benlib::sand::clone()
{
  auto obj = std::make_unique<benlib::sand>();
  obj->gravity = this->gravity;
  return std::move(obj);
}

std::string benlib::sand::class_name() const
{
  return "sand";
}

uint64_t benlib::sand::get_id() const
{
  return 3;
}
