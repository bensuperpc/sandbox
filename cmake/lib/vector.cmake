cmake_minimum_required(VERSION 3.14.0)

include(FetchContent)

FetchContent_Declare(
  vector
  GIT_REPOSITORY https://github.com/bensuperpc/vector.git
  GIT_TAG ecdd19fb025bbd649b955d7b6820f9599b9340d8) # 18-07-2022

FetchContent_MakeAvailable(vector)
