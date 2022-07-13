#include "sand.hpp"

benlib::sand::sand()
{
  gravity = true;
  id = 3;
}

benlib::sand::~sand() {}

std::unique_ptr<benlib::cell> benlib::sand::create()
{
  return std::move(std::make_unique<sand>());
}

std::string benlib::sand::class_name() const
{
  return "sand";
}
