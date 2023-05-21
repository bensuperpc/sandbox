#include "sandbox.hpp"

benlib::sendbox::sendbox() {}

benlib::sendbox::sendbox(const uint64_t _width, const uint64_t _height) {
    this->width = _width;
    this->height = _height;

    grid.resize(GetWidth() * GetHeight());
    std::fill(grid.begin(), grid.end(), Cell::air);
}

benlib::sendbox::~sendbox() {}

uint64_t benlib::sendbox::GetWidth() const noexcept { return this->width; }

uint64_t benlib::sendbox::GetHeight() const noexcept { return this->height; }

void benlib::sendbox::Resize(const uint64_t width, const uint64_t height) {
    // If old grid is same size as new grid, do nothing
    if (width == GetWidth() && height == GetHeight())
        return;
    grid.resize(width * height);
}

void benlib::sendbox::Reset() { std::fill(grid.begin(), grid.end(), Cell::air); }

uint64_t benlib::sendbox::GetCells() const noexcept { return GetWidth() * GetHeight(); }

uint64_t benlib::sendbox::GetGenerations() const noexcept { return generations; }

void benlib::sendbox::SetGenerations(const uint64_t _generations) { this->generations = _generations; }

void benlib::sendbox::SetCell(const uint64_t x, const uint64_t y, const Cell id) { grid[x * GetHeight() + y] = id; }

Cell &benlib::sendbox::GetCell(const uint64_t x, const uint64_t y) { return grid[x * GetHeight() + y]; }

void benlib::sendbox::Print() {
    /*
    for (uint64_t x = 0; x < GetWidth(); x++) {
      for (uint64_t y = 0; y < GetHeight(); y++) {
        std::cout << grid[x * GetHeight() + y] << " ";

        if (y == GetHeight() - 1) {
          std::cout << "\n";
        }
      }
    }
    std::cout << std::endl;
    */
}

void benlib::sendbox::Update() {
    generations++;

    // clone the grid
    gridB = grid;

#if defined(_OPENMP)
#pragma omp parallel for collapse(2) schedule(auto)
#endif
    for (uint64_t x = 0; x < GetWidth(); x++) {
        for (uint64_t y = 0; y < GetHeight(); y++) {
            for (int32_t i = -1; i < 2; i++) {
                for (int32_t j = -1; j < 2; j++) {
                    // If is not the center cell
                    if (i == 0 && j == 0) {
                        continue;
                    }

                    // Avoid underflow of the grid
                    if ((x + i < 0) || (y + j < 0)) {
                        continue;
                    }
                    // Avoid overflow of grid
                    if (x + i >= GetWidth() || y + j >= GetHeight()) {
                        continue;
                    }

                    const Cell &neighbor = gridB[(x + i) * GetHeight() + y + j];
                    Cell &cell = GetCell(x, y);

                    // If is air, do nothing
                    if (cell == Cell::air) {
                        continue;
                    }

                    // If same class, do nothing
                    if (cell == neighbor) {
                        continue;
                    }

                    // If water + fire -> steam
                    if (cell == Cell::water && neighbor == Cell::fire) {
                        cell = Cell::steam;
                        continue;
                    }

                    // If sand + fire -> glass
                    if (cell == Cell::sand && neighbor == Cell::fire) {
                        cell = Cell::glass;
                        continue;
                    }

                    // If water + plant -> plant
                    if (cell == Cell::water && neighbor == Cell::plant) {
                        cell = Cell::plant;
                        continue;
                    }

                    // If plant + fire -> fire
                    if (cell == Cell::plant && neighbor == Cell::fire) {
                        cell = Cell::fire;
                        continue;
                    }
                }
            }
        }
    }
}

void benlib::sendbox::Clear() {
    grid.clear();
    // grid2D.ShrinkToFit();
}

void benlib::sendbox::RandomFill() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (uint64_t x = 0; x < GetWidth(); x++) {
        for (uint64_t y = 0; y < GetHeight(); y++) {
            SetCell(x, y, dis(gen) == 0 ? Cell::air : Cell::sand);
        }
    }
}

void benlib::sendbox::Fill(const Cell value) {
    for (uint64_t x = 0; x < GetWidth(); x++) {
        for (uint64_t y = 0; y < GetHeight(); y++) {
            SetCell(x, y, value);
        }
    }
}

bool benlib::sendbox::operator==(const benlib::sendbox &other) const {
    // return grid2D == other.grid2D;
}

bool benlib::sendbox::operator!=(const benlib::sendbox &other) const {
    // return grid2D != other.grid2D;
}

benlib::sendbox &benlib::sendbox::operator=(const benlib::sendbox &other) {
    // if (this == &other)
    //     return *this;
    // grid2D = other.grid2D;
    // return *this;
}

void benlib::sendbox::SetCircle(const uint64_t x, const uint64_t y, const uint64_t r, const Cell id) {
    // std::cout << "Circle(" << x << ", " << y << ", " << r << ", " << id << ")" << std::endl;
    /*
    #if defined(_OPENMP)
    #  pragma omp parallel for collapse(2) schedule(auto)
    #endif
      for (uint64_t i = 0; i < GetWidth(); i++) {
        for (uint64_t j = 0; j < GetHeight(); j++) {
          if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r) {
            SetCell(i, j, id);
          }
        }
      }
      */
    // From : https://stackoverflow.com/a/59211338/10152334
    const int64_t center_x = static_cast<int64_t>(x);
    const int64_t center_y = static_cast<int64_t>(y);
    const int64_t radius = static_cast<int64_t>(r);

    for (int64_t _x = -radius; _x < radius; _x++) {
        const int64_t hh = static_cast<int64_t>(std::sqrt(radius * radius - _x * _x));
        const int64_t rx = center_x + _x;
        const int64_t ph = center_y + hh;
        std::cout << "(" << rx << ", " << ph << ")" << std::endl;

        for (int64_t _y = center_y - hh; _y < ph; _y++) {
            if (rx >= 0 && rx < GetWidth() && _y >= 0 && _y < GetHeight()) {
                SetCell(rx, _y, id);
            }
        }
    }
}

void benlib::sendbox::SetRectangle(const uint64_t x, const uint64_t y, const uint64_t w, const uint64_t h, const Cell id) {
    // std::cout << "Rectangle(" << x << ", " << y << ", " << w << ", " << h << ", " << id << ")" << std::endl;
#if defined(_OPENMP)
#pragma omp parallel for collapse(2) schedule(auto)
#endif
    for (uint64_t i = 0; i < w; i++) {
        for (uint64_t j = 0; j < h; j++) {
            if (x + i >= 0 && x + i < GetWidth() && y + j >= 0 && y + j < GetHeight()) {
                SetCell(x + i, y + j, id);
            }
        }
    }
}

/*
void benlib::sendbox::Deserialize(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "Could not open file " << filename << std::endl;
    return;
  }

  std::string line;
  std::vector<std::vector<benlib::cell>> _grid {};
  while (std::getline(file, line)) {
    // std::cout << line << std::endl;
    std::vector<benlib::cell> row {};
    for (char c : line) {
      if (c == '0') {
        row.push_back(1);
      } else if (c == '.') {
        row.push_back(0);
      } else if (c == '\n') {
      } else {
        // std::cout << "Unknown character: " << c << std::endl;
      }
    }
    _grid.push_back(row);
  }
  file.close();

  std::vector<benlib::cell> new_grid;
  for (auto& i : _grid) {
    new_grid.insert(new_grid.end(), i.begin(), i.end());
  }
  std::vector<uint64_t> dim = {_grid.size(), _grid[0].size()};
  this->grid2D = benlib::multi_array<benlib::cell>(dim, new_grid);
  this->grid2D.SetGrid(new_grid);
}

void benlib::sendbox::Serialize(const std::string& filename)
{
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cout << "Could not open file " << filename << std::endl;
    return;
  }

  for (uint64_t x = 0; x < GetWidth(); x++) {
    for (uint64_t y = 0; y < GetHeight(); y++) {
      if (grid2D.get_value(x * GetHeight() + y)) {
        file << "0";
      } else {
        file << ".";
      }
    }
    file << "\n";
  }
  file.close();
}
*/
