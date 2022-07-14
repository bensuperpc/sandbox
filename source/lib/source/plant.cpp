#include "plant.hpp"

benlib::plant::plant() {}

benlib::plant::~plant() {}

std::unique_ptr<benlib::cell> benlib::plant::create()
{
  return std::move(std::make_unique<benlib::plant>());
}

std::unique_ptr<benlib::cell> benlib::plant::clone()
{
  auto obj = std::make_unique<benlib::plant>();
  obj->gravity = this->gravity;
  return std::move(obj);
}

std::string benlib::plant::class_name() const
{
  return "plant";
}

const uint64_t benlib::plant::get_id() const
{
  return 6;
}
