#include <cstdint>  // uint32_t, uint64_t
#include <random>  // std::mt19937
#include <vector>  // std::vector

#include <benchmark/benchmark.h>

#include "vector/multi_array.hpp"  // benlib::multi_array
#include "vector/utils.hpp"  // _KB, _MB, _GB, _TB

static void multi_array_set_value_uint32_t_2D(benchmark::State& state)
{
  const auto width = static_cast<uint64_t>(state.range(0));
  const auto height = static_cast<uint64_t>(state.range(0));
  std::vector<uint64_t> v = {width, height};
  auto grid = benlib::multi_array<uint32_t>(v);
  grid.fill(0);
  benchmark::DoNotOptimize(grid);

  for (auto _ : state) {
    for (uint64_t i = 0; i < width * height; ++i) {
      grid.set_value(i, 42);
    }
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(state.iterations() * width * height);
  state.SetBytesProcessed(state.iterations() * width * height * sizeof(uint32_t));
}
BENCHMARK(multi_array_set_value_uint32_t_2D)
    ->Name("multi_array_set_value_uint32_t_2D")
    ->RangeMultiplier(8)
    ->Range(8, 4_KB);