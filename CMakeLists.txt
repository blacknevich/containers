cmake_minimum_required(VERSION 3.21)
project(containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(containers main.cpp ft_map.hpp Map_iterator.hpp Node_struct.hpp ft_vector.hpp Reverse_iterator.hpp Iterator_traits.hpp Random_access_iterator.hpp)

add_definitions("-Wall -Wextra -Werror --std=c++98")

add_compile_options(-gdwarf-4)
