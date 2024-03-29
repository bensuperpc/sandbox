# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(GTA_SA_cheat_finderTests LANGUAGES C CXX)

# ---- Tests ----

function(add_test_fn TEST_NAME)
  add_executable("${TEST_NAME}" "source/${TEST_NAME}.cpp")
  target_link_libraries("${TEST_NAME}" PRIVATE sandbox_lib gtest_main)
  #target_include_directories("${TEST_NAME}" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source)

  if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
    target_link_libraries("${TEST_NAME}" PRIVATE OpenMP::OpenMP_CXX)
  endif()

  add_test(NAME "${TEST_NAME}" COMMAND $<TARGET_FILE:${TEST_NAME}>)
  #target_compile_features("${TEST_NAME}" PRIVATE cxx_std_20)
endfunction()

function(add_bench_fn BENCH_NAME)
  add_executable("${BENCH_NAME}" "source/${BENCH_NAME}.cpp")
  target_link_libraries("${BENCH_NAME}" PRIVATE sandbox_lib benchmark::benchmark_main)

  if (OpenMP_FOUND OR OpenMP_CXX_FOUND)
    target_link_libraries("${BENCH_NAME}" PRIVATE OpenMP::OpenMP_CXX)
  endif()

  if(NOT CMAKE_BUILD_TYPE MATCHES Debug AND NOT CMAKE_BUILD_TYPE MATCHES Coverage)
    add_test(NAME "${BENCH_NAME}" COMMAND $<TARGET_FILE:${BENCH_NAME}>)
  elseif()
    message(STATUS "Disable ${BENCH_NAME}, Performance benchmark test only run on Release/RelWithDebInfo/MinSizeRel")
  endif()
  #target_compile_features("${TEST_NAME}" PRIVATE cxx_std_20)
endfunction()

if(NOT WIN32)
include(../cmake/lib/gtest.cmake)
include(../cmake/lib/benchmark.cmake)
  # Add tests
  add_test_fn(sandbox_test)

  # Add bench
  add_bench_fn(sandbox_bench)
endif()


# ---- End-of-file commands ----

add_folders(Test)
