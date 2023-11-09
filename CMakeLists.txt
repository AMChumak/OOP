cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(game_life)

add_executable(game_life life.cpp)

add_subdirectory(client)
add_subdirectory(console_process_classes)
add_subdirectory(game_space_classes)
add_subdirectory(utils)
add_subdirectory(workers)

target_link_libraries(game_life PUBLIC game_client_lib console_processors_lib game_space_lib utils_lib workers_lib)

target_include_directories(game_life PUBLIC client console_process_classes game_space_classes utils workers)

