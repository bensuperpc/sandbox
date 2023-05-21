#include <array>
#include <string>
#include <string_view>
#include <vector>

#include <benchmark/benchmark.h>

#include "sandbox.hpp"

static void sandbox_bench(benchmark::State &state) {
    // Code inside this loop is measured repeatedly
    auto range = state.range(0);
    auto sandbox = benlib::sendbox(range, range);

    for (auto _ : state) {
        benchmark::DoNotOptimize(sandbox);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations());
    state.SetBytesProcessed(state.iterations() * sizeof(uint64_t));
}

BENCHMARK(sandbox_bench)->Name("sandbox_bench")->RangeMultiplier(10)->Range(10, 1000);

// Run the benchmark
// BENCHMARK_MAIN();
