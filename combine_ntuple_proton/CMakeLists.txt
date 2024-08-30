cmake_minimum_required(VERSION 3.10)
project(combine_ntuple_proton)
find_package(ROOT REQUIRED COMPONENTS RIO)

# For .clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_executable(combine_ntuple_proton src/main.cpp)
target_link_libraries(combine_ntuple_proton ROOT::RIO ROOT::Hist ROOT::Gpad ROOT::Tree ROOT::TreePlayer ROOT::Core ROOT::Gui ROOT::ROOTDataFrame)
target_include_directories(combine_ntuple_proton PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src")
