cmake_minimum_required(VERSION 3.21)
project(containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(containers main.cpp ft_vector.hpp Reverse_iterator.hpp)

add_definitions("-Wall -Wextra -Werror --std=c++98")