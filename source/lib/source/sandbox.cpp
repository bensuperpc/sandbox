#include "sandbox.hpp"

benlib::Gol::Gol() {}

benlib::Gol::Gol(const uint64_t width, const uint64_t height)
{
  std::vector<uint64_t> v = {width, height};
  this->grid2D.set_dim(v);
  auto data = this->grid2D.data();
  data->reserve(GetWidth() * GetHeight());
  for (uint64_t i = 0; i < width * height; i++) {
    data->emplace_back(std::make_unique<benlib::air>());
  }

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
benlib::Gol::Gol(benlib::cell** _grid,
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

benlib::Gol::Gol(const std::vector<benlib::cell>& _grid1D,
                 const uint64_t width,
                 const uint64_t height)
{
  std::vector<uint64_t> v = {width, height};
  this->grid2D = benlib::multi_array<benlib::cell>(v);
  this->grid2D.SetGrid(_grid1D);
}

benlib::Gol::Gol(const std::vector<std::vector<benlib::cell>>& _grid)
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

benlib::Gol::~Gol() {}

uint64_t benlib::Gol::GetWidth()
{
  return (*grid2D.data_dim())[0];
}

uint64_t benlib::Gol::GetHeight()
{
  return (*grid2D.data_dim())[1];
}

void benlib::Gol::Resize(const uint64_t width, const uint64_t height)
{
  // If old grid is same size as new grid, do nothing
  if (width == GetWidth() && height == GetHeight())
    return;
  std::vector<uint64_t> v = {width, height};
  grid2D.resize(v);
}

void benlib::Gol::Reset()
{
  grid2D.clear();

  auto data = this->grid2D.data();
  for (uint64_t i = 0; i < GetWidth() * GetHeight(); i++) {
    auto cell = std::make_unique<benlib::air>();
    data->emplace_back(std::move(cell));
  }
}

uint64_t benlib::Gol::GetCells()
{
  return GetWidth() * GetHeight();
}

uint64_t benlib::Gol::GetGenerations()
{
  return generations;
}

void benlib::Gol::SetGenerations(const uint64_t _generations)
{
  this->generations = _generations;
}

benlib::multi_array<std::unique_ptr<benlib::cell>>* benlib::Gol::GetGrid()
{
  return &grid2D;
}

void benlib::Gol::SetGrid(std::vector<benlib::cell*>* _grid)
{
  for (uint64_t i = 0; i < GetWidth(); i++) {
    for (uint64_t j = 0; j < GetHeight(); j++) {
      grid2D.data()->at(i * GetHeight() + j) =
          std::move(std::make_unique<benlib::cell>(*_grid->at(i * GetHeight() + j)));
    }
  }
}

void benlib::Gol::SetCell(const uint64_t x, const uint64_t y, benlib::cell* cell)
{
  grid2D.set_value(x * GetHeight() + y, std::move(std::unique_ptr<benlib::cell>(cell)));
}

void benlib::Gol::SetCell(const uint64_t x, const uint64_t y, const uint64_t id_map)
{
  auto it = map_type.find(id_map);

  if (it != map_type.end()) {
    auto cell = it->second->create();
    grid2D.set_value(x * GetHeight() + y, std::move(cell));
    auto _cell = GetCell(x, y);
    // std::cout << "Class: " << _cell->class_name() << std::endl;
  } else {
    grid2D.set_value(x * GetHeight() + y, std::move(std::make_unique<benlib::air>()));
  }
}

benlib::cell* benlib::Gol::GetCell(const uint64_t x, const uint64_t y)
{
  auto data = this->grid2D.data();
  return data->at(x * GetHeight() + y).get();
  // return (*data)[x * GetHeight() + y].get();
}

void benlib::Gol::Print()
{
  auto data = this->grid2D.data();
  for (uint64_t x = 0; x < GetWidth(); x++) {
    for (uint64_t y = 0; y < GetHeight(); y++) {
      uint64_t coord = x * GetHeight() + y;
      std::cout << data->at(coord)->class_name() << " ";

      if (y == GetHeight() - 1) {
        std::cout << "\n";
      }
    }
  }
  std::cout << std::endl;
}

uint64_t benlib::Gol::GetNeighborsCount(const std::vector<benlib::cell>& _grid,
                                        const uint64_t width,
                                        const uint64_t height,
                                        const uint64_t x,
                                        const uint64_t y,
                                        const benlib::cell value)
{
  uint64_t countCell = 0;
  /*
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
  */
  return countCell;
}

void benlib::Gol::Update()
{
  generations++;
  // clone the grid
  benlib::multi_array<std::unique_ptr<benlib::cell>> new_grid;

  std::vector<uint64_t> v = {GetWidth(), GetHeight()};
  new_grid.set_dim(v);

  auto data = new_grid.data();
  data->reserve(GetWidth() * GetHeight());

  for (uint64_t i = 0; i < GetWidth(); i++) {
    for (uint64_t j = 0; j < GetHeight(); j++) {
      data->emplace_back(this->grid2D.data()->at(i * GetHeight() + j)->clone());
    }
  }

#if defined(_OPENMP)
#  pragma omp parallel for collapse(2) schedule(auto)
#endif
  for (uint64_t x = 0; x < GetWidth(); x++) {
    for (uint64_t y = 0; y < GetHeight(); y++) {
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
          if (x + i >= GetWidth() || y + j >= GetHeight()) {
            continue;
          }

          // Update ptr
          // const auto neighbor = GetCell(x + i, y + j);
          const auto neighbor = new_grid.data()->at((x + i) * GetHeight() + y + j).get();
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

void benlib::Gol::Clear()
{
  grid2D.clear();
  // grid2D.ShrinkToFit();
}

void benlib::Gol::RandomFill()
{
  auto* grid = grid2D.data();
  // random<benlib::cell>((*grid), 0, 7);
}

void benlib::Gol::Fill(const uint64_t value)
{
  for (uint64_t x = 0; x < GetWidth(); x++) {
    for (uint64_t y = 0; y < GetHeight(); y++) {
      SetCell(x, y, value);
    }
  }
}

bool benlib::Gol::operator==(const benlib::Gol& other) const
{
  // return grid2D == other.grid2D;
}

bool benlib::Gol::operator!=(const benlib::Gol& other) const
{
  // return grid2D != other.grid2D;
}

benlib::Gol& benlib::Gol::operator=(const benlib::Gol& other)
{
  // if (this == &other)
  //     return *this;
  // grid2D = other.grid2D;
  // return *this;
}

void benlib::Gol::Circle(const uint64_t x, const uint64_t y, const uint64_t r, const uint64_t id)
{
  std::cout << "Circle(" << x << ", " << y << ", " << r << ", " << id << ")" << std::endl;

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
}

benlib::cell* benlib::Gol::operator()(const uint64_t x, const uint64_t y)
{
  uint64_t coord = x * GetHeight() + y;
  auto data = this->grid2D.data();
  return data->at(coord).get();
}

/*
void benlib::Gol::Deserialize(const std::string& filename)
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

void benlib::Gol::Serialize(const std::string& filename)
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
