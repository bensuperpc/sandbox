#include "water.hpp"

benlib::water::water()
{
  gravity = true;
  id = 1;
}

benlib::water::~water() {}

std::unique_ptr<benlib::cell> benlib::water::create()
{
  return std::move(std::make_unique<water>());
}

std::string benlib::water::class_name() const
{
  return "water";
}
