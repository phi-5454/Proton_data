cmake_minimum_required(VERSION 3.10)
project(proton_pruning)

find_package(ROOT)

# For .clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_executable(proton_pruning src/main.cpp)
target_link_libraries(proton_pruning ROOT::RIO ROOT::Hist ROOT::Gpad ROOT::Tree ROOT::TreePlayer ROOT::Core ROOT::Gui ROOT::ROOTDataFrame)
target_include_directories(proton_pruning PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src")
