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
#include "sand.hpp"
#include "vector/multi_array.hpp"
#include "vector/vector.hpp"
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
class Gol
{
public:
  Gol();
  // Constructor.
  Gol(const uint64_t width, const uint64_t height);
  /*
  // Constructor.
  Gol(benlib::cell** _grid, const uint64_t width, const uint64_t height);
  // Constructor.
  Gol(const std::vector<std::vector<benlib::cell>>& _grid);
  // Constructor.
  Gol(const std::vector<benlib::cell>& _grid1D,
      const uint64_t width,
      const uint64_t height);
  */
  // Destructor.
  ~Gol();
  // Get the width of the game of life.
  uint64_t GetWidth();
  // Get the height of the game of life.
  uint64_t GetHeight();
  // Get the number of living cells.
  uint64_t GetLivingCells();
  // Get the number of dead cells.
  uint64_t GetDeadCells();
  // Get the number of cells.
  uint64_t GetCells();
  // Get the number of generations.
  uint64_t GetGenerations();
  // Set the number of generations.
  void SetGenerations(const uint64_t generations);
  // Set the cell at the given coordinates to be alive.
  void SetCell(const uint64_t x, const uint64_t y, const benlib::cell& alive);
  void SetCell(const uint64_t x, const uint64_t y, const uint64_t id);
  // Set row
  void SetRow(const uint64_t row, const std::vector<benlib::cell>& rowData);
  // Get the cell at the given coordinates.
  benlib::cell GetCell(const uint64_t x, const uint64_t y);
  // Get the row at the given coordinates.
  std::vector<benlib::cell> GetRow(const uint64_t y);
  // Get grid.
  std::vector<benlib::cell> GetGrid();
  // Set grid.
  void SetGrid(const std::vector<benlib::cell>& _grid);

  void Circle(const uint64_t x, const uint64_t y, const uint64_t r, const benlib::cell& alive);
  void Circle(const uint64_t x, const uint64_t y, const uint64_t r, const uint64_t id);
  // Get neighbors.
  uint64_t GetNeighborsCount(const std::vector<benlib::cell>& _grid,
                             const uint64_t width,
                             const uint64_t height,
                             const uint64_t x,
                             const uint64_t y,
                             const benlib::cell value);
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
  void Fill(const benlib::cell& value);
  // Reset the game of life.
  void Reset();

  // Overload operator== to compare a game of life.
  bool operator==(const Gol& gol) const;
  // Overload operator= to copy a game of life.
  Gol& operator=(const Gol& gol);
  // Overload operator!= to compare a game of life.
  bool operator!=(const Gol& gol) const;
  // Overload operator(x, y) to get the cell at the given coordinates.
  benlib::cell operator()(const uint64_t x, const uint64_t y);

  // Save the game of life to a file.
  // void Serialize(const std::string& filename);
  // Load the game of life from a file.
  // void Deserialize(const std::string& filename);

protected:
  // The number of generations.
  uint64_t generations = 0;
  // The game of life grid.
  benlib::multi_array<benlib::cell> grid2D;
  inline static std::map<uint64_t, cell*> map_type;
};
}  // namespace benlib
#endif  // BENLIB_GOL_HPP_
