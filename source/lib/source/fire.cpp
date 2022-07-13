#include "fire.hpp"

benlib::fire::fire()
{
  id = 2;
}

benlib::fire::~fire() {}

std::unique_ptr<benlib::cell> benlib::fire::create()
{
  return std::move(std::make_unique<fire>());
}

std::string benlib::fire::class_name() const
{
  return "fire";
}
