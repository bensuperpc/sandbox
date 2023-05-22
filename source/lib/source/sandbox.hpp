#ifndef BENLIB_GOL_HPP_
#define BENLIB_GOL_HPP_

#include <algorithm> // std::fill, std::generate
#include <cstdint>   // std::uint64_t
#include <fstream>   // std::ifstream, std::ofstream
#include <iostream>  // std::cout, std::endl
#include <random>    // std::mt19937, std::uniform_int_distribution
#include <string>    // std::string
#include <vector>    // std::vector

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#if __has_include("omp.h")
#include <omp.h>
#else
#if _MSC_VER && !__INTEL_COMPILER
#pragma message("Can t find omp.h, please install OpenMP")
#else
#warning Can t find omp.h, please install OpenMP.
#endif
#endif
#endif

enum class Cell : uint8_t { air = 0, fire = 1, glass = 2, plant = 3, sand = 4, steam = 5, water = 6 };

namespace benlib {
// A class for representing a game of life.
class Sandbox {
  public:
    Sandbox();
    // Constructor.
    Sandbox(const uint64_t width, const uint64_t height);

    // Destructor.
    ~Sandbox();
    // Get the width of the game of life.
    uint64_t GetWidth() const noexcept;
    // Get the height of the game of life.
    uint64_t GetHeight() const noexcept;
    // Get the number of cells.
    uint64_t GetCells() const noexcept;
    // Get the number of generations.
    uint64_t GetGenerations() const noexcept;

    // Set the number of generations.
    void SetGenerations(const uint64_t generations);
    // Set the cell at the given coordinates to be alive.
    void SetCell(const uint64_t x, const uint64_t y, const Cell id);
    // Get the cell at the given coordinates.
    Cell &GetCell(const uint64_t x, const uint64_t y);

    void SetCircle(const uint64_t x, const uint64_t y, const uint64_t r, const Cell id);
    void SetRectangle(const uint64_t x, const uint64_t y, const uint64_t w, const uint64_t h, const Cell id);
    
    // Update the game of life.
    void Update();

    // Print the game of life.
    void Print();
    // Clear the game of life.
    void Clear();
    // Resize the game of life.
    void Resize(const uint64_t width, const uint64_t height);

    // Randomly populate the game of life.
    void RandomFill();

    // Populate the game of life with value in benlib::cellean
    void Fill(const Cell value);
    // Reset the game of life.
    void Reset();

    // Overload operator== to compare a game of life.
    bool operator==(const Sandbox &gol) const;
    // Overload operator= to copy a game of life.
    Sandbox &operator=(const Sandbox &gol);
    // Overload operator!= to compare a game of life.
    bool operator!=(const Sandbox &gol) const;

    // Save the game of life to a file.
    // void Serialize(const std::string& filename);
    // Load the game of life from a file.
    // void Deserialize(const std::string& filename);

  protected:
    // The number of generations.
    uint64_t generations = 0;

    // The game of life grid.
    std::vector<Cell> grid;
    std::vector<Cell> gridB;

    uint64_t width = 0;
    uint64_t height = 0;
};
} // namespace benlib
#endif // BENLIB_GOL_HPP_
