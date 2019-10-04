cmake_minimum_required(VERSION 3.12.2)

project (threading)
set (CMAKE_CXX_STANDARD 11)

add_library(deps
  SHARED
    src/threading.cpp
)

target_include_directories( deps 
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

add_executable(producer_consumer src/main.cpp)
target_link_libraries( producer_consumer
  PUBLIC
    deps
)
