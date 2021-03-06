#include "sandbox.hpp"

benlib::sendbox::sendbox() {}

benlib::sendbox::sendbox(const uint64_t width, const uint64_t height)
{
  this->width = width;
  this->height = height;

  grid.reserve(GetWidth() * GetHeight());
  for (uint64_t i = 0; i < width * height; i++) {
    grid.emplace_back(std::make_unique<benlib::air>());
  }

  grid.reserve(GetWidth() * GetHeight());

  // Get get_id() from cell
  // std::cout << data->at(0).get()->get_id() << std::endl;

  map_type[benlib::air().get_id()] = new benlib::air();
  map_type[benlib::water().get_id()] = new benlib::water();
  map_type[benlib::fire().get_id()] = new benlib::fire();
  map_type[benlib::sand().get_id()] = new benlib::sand();
  map_type[benlib::steam().get_id()] = new benlib::steam();
  map_type[benlib::glass().get_id()] = new benlib::glass();
  map_type[benlib::plant().get_id()] = new benlib::plant();
}

/*
benlib::sendbox::sendbox(benlib::cell** _grid,
                 const uint64_t width,
                 const uint64_t height)
{
  std::vector<benlib::cell> new_grid(width * height, 0);
  for (uint64_t i = 0; i < width; i++) {
    std::copy(_grid[i], _grid[i] + height, new_grid.begin() + i * height);
  }
  std::vector<uint64_t> dim = {width, height};
  this->grid2D = benlib::multi_array<benlib::cell>(dim, new_grid);
}

benlib::sendbox::sendbox(const std::vector<benlib::cell>& _grid1D,
                 const uint64_t width,
                 const uint64_t height)
{
  std::vector<uint64_t> v = {width, height};
  this->grid2D = benlib::multi_array<benlib::cell>(v);
  this->grid2D.SetGrid(_grid1D);
}

benlib::sendbox::sendbox(const std::vector<std::vector<benlib::cell>>& _grid)
{
  // Convert to 1D vector.
  std::vector<benlib::cell> new_grid;
  for (auto& i : _grid) {
    new_grid.insert(new_grid.end(), i.begin(), i.end());
  }
  std::vector<uint64_t> dim = {_grid.size(), _grid[0].size()};
  this->grid2D = benlib::multi_array<benlib::cell>(dim, new_grid);
  this->grid2D.SetGrid(new_grid);
}
*/

benlib::sendbox::~sendbox() {}

uint64_t benlib::sendbox::GetWidth()
{
  return this->width;
}

uint64_t benlib::sendbox::GetHeight()
{
  return this->height;
}

void benlib::sendbox::Resize(const uint64_t width, const uint64_t height)
{
  // If old grid is same size as new grid, do nothing
  if (width == GetWidth() && height == GetHeight())
    return;
  grid.resize(width * height);
}

void benlib::sendbox::Reset()
{
  grid.clear();
  for (uint64_t i = 0; i < GetWidth() * GetHeight(); i++) {
    auto cell = std::make_unique<benlib::air>();
    grid.emplace_back(std::move(cell));
  }
}

uint64_t benlib::sendbox::GetCells()
{
  return GetWidth() * GetHeight();
}

uint64_t benlib::sendbox::GetGenerations()
{
  return generations;
}

void benlib::sendbox::SetGenerations(const uint64_t _generations)
{
  this->generations = _generations;
}

std::vector<std::unique_ptr<benlib::cell>>* benlib::sendbox::GetGrid()
{
  return &grid;
}

void benlib::sendbox::SetGrid(std::vector<benlib::cell*>* _grid) {}

void benlib::sendbox::SetCell(const uint64_t x, const uint64_t y, benlib::cell* cell)
{
  grid[x * GetHeight() + y] = std::unique_ptr<benlib::cell>(cell);
}

void benlib::sendbox::SetCell(const uint64_t x, const uint64_t y, const uint64_t id_map)
{
  auto it = map_type.find(id_map);

  if (it != map_type.end()) {
    auto cell = it->second->create();
    grid[x * GetHeight() + y] = std::move(cell);
    // auto _cell = GetCell(x, y);
    // std::cout << "Class: " << _cell->class_name() << std::endl;
  } else {
    grid[x * GetHeight() + y] = std::make_unique<benlib::air>();
  }
}

benlib::cell* benlib::sendbox::GetCell(const uint64_t x, const uint64_t y)
{
  return grid[x * GetHeight() + y].get();
  // data->at(x * GetHeight() + y).get();
  //  return (*data)[x * GetHeight() + y].get();
}

void benlib::sendbox::Print()
{
  for (uint64_t x = 0; x < GetWidth(); x++) {
    for (uint64_t y = 0; y < GetHeight(); y++) {
      std::cout << grid[x * GetHeight() + y]->get_id() << " ";

      if (y == GetHeight() - 1) {
        std::cout << "\n";
      }
    }
  }
  std::cout << std::endl;
}

/*
uint64_t benlib::sendbox::GetNeighborsCount(const std::vector<benlib::cell>& _grid,
                                        const uint64_t width,
                                        const uint64_t height,
                                        const uint64_t x,
                                        const uint64_t y,
                                        const benlib::cell value)
{
  uint64_t countCell = 0;

  for (int8_t i = -1; i < 2; i++) {
    for (int8_t j = -1; j < 2; j++) {
      // If is not the center cell
      if (i == 0 && j == 0) {
        continue;
      }

      // Avoid underflow of the grid
      if ((x == 0 && i == -1) || (y == 0 && j == -1)) {
        continue;
      }

      // Avoid overflow of grid
      if (x + i >= width || y + j >= height) {
        continue;
      }

      // Count living neighbors
      if (_grid[(x + i) * height + y + j] == value) {
        ++countCell;
      }
    }
  }

  return countCell;
}
*/

void benlib::sendbox::Update()
{
  generations++;
  // clone the grid

  gridB.clear();
  gridB.reserve(GetWidth() * GetHeight());

  for (uint64_t i = 0; i < GetWidth(); i++) {
    for (uint64_t j = 0; j < GetHeight(); j++) {
      // gridB.emplace_back(this->grid2D.data()->at(i * GetHeight() + j)->clone());
      gridB.emplace_back(grid[i * GetHeight() + j]->clone());
    }
  }

#if defined(_OPENMP)
#  pragma omp parallel for collapse(2) schedule(auto)
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
          if ((x == 0 && i == -1) || (y == 0 && j == -1)) {
            continue;
          }
          // Avoid overflow of grid
          if (x + i >= GetWidth() || y + j >= GetHeight()) {
            continue;
          }

          // Update ptr
          // const auto neighbor = GetCell(x + i, y + j);
          // const auto neighbor = new_grid.data()->at((x + i) * GetHeight() + y + j).get();
          const auto neighbor = gridB[(x + i) * GetHeight() + y + j].get();
          const auto cell = GetCell(x, y);

          // If same class, do nothing
          if (cell->get_id() == neighbor->get_id()) {
            continue;
          }

          // If is air, do nothing
          if (cell->get_id() == 0) {
            continue;
          }

          // If water + fire -> steam
          if (cell->get_id() == 1 && neighbor->get_id() == 2) {
            SetCell(x, y, new benlib::steam());
            continue;
          }

          // If sand + fire -> glass
          if (cell->get_id() == 3 && neighbor->get_id() == 2) {
            SetCell(x, y, new benlib::glass());
            continue;
          }

          // If water + plant -> plant
          if (cell->get_id() == 1 && neighbor->get_id() == 6) {
            SetCell(x, y, new benlib::plant());
            continue;
          }

          // If plant + fire -> fire
          if (cell->get_id() == 6 && neighbor->get_id() == 2) {
            SetCell(x, y, new benlib::fire());
            continue;
          }
        }
      }
    }
  }
}

void benlib::sendbox::Clear()
{
  grid.clear();
  // grid2D.ShrinkToFit();
}

void benlib::sendbox::RandomFill()
{
  // auto* grid = grid2D.data();
  //  random<benlib::cell>((*grid), 0, 7);
}

void benlib::sendbox::Fill(const uint64_t value)
{
  for (uint64_t x = 0; x < GetWidth(); x++) {
    for (uint64_t y = 0; y < GetHeight(); y++) {
      SetCell(x, y, value);
    }
  }
}

bool benlib::sendbox::operator==(const benlib::sendbox& other) const
{
  // return grid2D == other.grid2D;
}

bool benlib::sendbox::operator!=(const benlib::sendbox& other) const
{
  // return grid2D != other.grid2D;
}

benlib::sendbox& benlib::sendbox::operator=(const benlib::sendbox& other)
{
  // if (this == &other)
  //     return *this;
  // grid2D = other.grid2D;
  // return *this;
}

void benlib::sendbox::Circle(const uint64_t x, const uint64_t y, const uint64_t r, const uint64_t id)
{
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

void benlib::sendbox::Rectangle(
    const uint64_t x, const uint64_t y, const uint64_t w, const uint64_t h, const uint64_t id)
{
  // std::cout << "Rectangle(" << x << ", " << y << ", " << w << ", " << h << ", " << id << ")" << std::endl;
#if defined(_OPENMP)
#  pragma omp parallel for collapse(2) schedule(auto)
#endif
  for (uint64_t i = 0; i < w; i++) {
    for (uint64_t j = 0; j < h; j++) {
      if (x + i >= 0 && x + i < GetWidth() && y + j >= 0 && y + j < GetHeight()) {
        SetCell(x + i, y + j, id);
      }
    }
  }
}

benlib::cell* benlib::sendbox::operator()(const uint64_t x, const uint64_t y)
{
  return grid[x * GetHeight() + y].get();
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
