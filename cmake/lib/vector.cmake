cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  vector
  GIT_REPOSITORY https://github.com/bensuperpc/vector.git
  GIT_TAG 22f83c890984604d5160b68e5b6626fd1f94c591) # 11-07-2022

FetchContent_MakeAvailable(vector)
