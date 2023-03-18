cmake_minimum_required(VERSION 3.24)
project(hypothesis_testing)

set(CMAKE_CXX_STANDARD 20)

add_executable(hypothesis_testing main.cpp read_data/csv_data_reader.h statistics/tuple_summer.h)
