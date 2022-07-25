#ifndef BENLIB_GOL_HPP_
#define BENLIB_GOL_HPP_

#include <algorithm>  // std::fill, std::generate
#include <fstream>  // std::ifstream, std::ofstream
#include <iostream>  // std::cout, std::endl
#include <random>  // std::mt19937, std::uniform_int_distribution
#include <string>  // std::string
#include <vector>  // std::vector

#include "air.hpp"
#include "fire.hpp"
#include "glass.hpp"
#include "plant.hpp"
#include "sand.hpp"
#include "steam.hpp"
#include "water.hpp"

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#  if __has_include("omp.h")
#    include <omp.h>
#  else
#    if _MSC_VER && !__INTEL_COMPILER
#      pragma message("Can t find omp.h, please install OpenMP")
#    else
#      warning Can t find omp.h, please install OpenMP.
#    endif
#  endif
#endif

namespace benlib
{
// A class for representing a game of life.
class sendbox
{
public:
  sendbox();
  // Constructor.
  sendbox(const uint64_t width, const uint64_t height);
  /*
  // Constructor.
  sendbox(benlib::cell** _grid, const uint64_t width, const uint64_t height);
  // Constructor.
  sendbox(const std::vector<std::vector<benlib::cell>>& _grid);
  // Constructor.
  sendbox(const std::vector<benlib::cell>& _grid1D,
      const uint64_t width,
      const uint64_t height);
  */
  // Destructor.
  ~sendbox();
  // Get the width of the game of life.
  uint64_t GetWidth();
  // Get the height of the game of life.
  uint64_t GetHeight();
  // Get the number of cells.
  uint64_t GetCells();
  // Get the number of generations.
  uint64_t GetGenerations();
  // Set the number of generations.
  void SetGenerations(const uint64_t generations);
  // Set the cell at the given coordinates to be alive.
  void SetCell(const uint64_t x, const uint64_t y, benlib::cell* alive);
  void SetCell(const uint64_t x, const uint64_t y, const uint64_t id);
  // Set row
  void SetRow(const uint64_t row, const std::vector<benlib::cell>& rowData);
  // Get the cell at the given coordinates.
  benlib::cell* GetCell(const uint64_t x, const uint64_t y);
  // Get the row at the given coordinates.
  std::vector<benlib::cell> GetRow(const uint64_t y);
  // Get grid.
  std::vector<std::unique_ptr<benlib::cell>>* GetGrid();
  // Set grid.
  void SetGrid(std::vector<benlib::cell*>* _grid);

  void Circle(const uint64_t x, const uint64_t y, const uint64_t r, const uint64_t id);
  void Rectangle(const uint64_t x, const uint64_t y, const uint64_t w, const uint64_t h, const uint64_t id);
  // Get neighbors.
  /*
  uint64_t GetNeighborsCount(const std::vector<benlib::cell>& _grid,
                             const uint64_t width,
                             const uint64_t height,
                             const uint64_t x,
                             const uint64_t y,
                             const benlib::cell value);
                             */
  // Update the game of life.
  void Update();

  void Update1D();
  // Print the game of life.
  void Print();
  // Clear the game of life.
  void Clear();
  // Resize the game of life.
  void Resize(const uint64_t width, const uint64_t height);

  // Randomly populate the game of life.
  void RandomFill();
  // Populate the game of life with value in benlib::cellean
  void Fill(const uint64_t value);
  // Reset the game of life.
  void Reset();

  // Overload operator== to compare a game of life.
  bool operator==(const sendbox& gol) const;
  // Overload operator= to copy a game of life.
  sendbox& operator=(const sendbox& gol);
  // Overload operator!= to compare a game of life.
  bool operator!=(const sendbox& gol) const;
  // Overload operator(x, y) to get the cell at the given coordinates.
  benlib::cell* operator()(const uint64_t x, const uint64_t y);

  // Save the game of life to a file.
  // void Serialize(const std::string& filename);
  // Load the game of life from a file.
  // void Deserialize(const std::string& filename);

protected:
  // The number of generations.
  uint64_t generations = 0;
  // The game of life grid.

  std::vector<std::unique_ptr<benlib::cell>> grid;
  std::vector<std::unique_ptr<benlib::cell>> gridB;

  uint64_t width = 0;
  uint64_t height = 0;

  inline static std::map<uint64_t, benlib::cell*> map_type;
};
}  // namespace benlib
#endif  // BENLIB_GOL_HPP_
