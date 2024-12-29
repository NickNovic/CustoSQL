cmake_minimum_required(VERSION 3.10)
project(CustoSQL)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add subdirectories for Domain/PrimitiveTypes
add_subdirectory(src/Domain/PrimitiveTypes)

# Main executable
add_executable(CustoSQL src/main.cpp)

# Link the PrimitiveTypes library
target_link_libraries(CustoSQL PrimitiveTypes)