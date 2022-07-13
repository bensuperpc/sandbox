cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  vector
  GIT_REPOSITORY https://github.com/bensuperpc/vector.git
  GIT_TAG 5ec7665dd91442195882f85bbbd3afffaa206db0) # 13-07-2022

FetchContent_MakeAvailable(vector)
