cmake_minimum_required(VERSION 3.14)
project(MyCppProject LANGUAGES CXX)

# Enable testing support
include(CTest)
enable_testing()

# Set global C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use Homebrew-installed GTest
 find_package(GTest REQUIRED PATHS /opt/homebrew/opt/googletest)

# Add each module
# Dynamically add all subdirectories with CMakeLists.txt
file(GLOB CHILD_CMAKELISTS RELATIVE ${CMAKE_SOURCE_DIR} */CMakeLists.txt)

foreach(module_cmake ${CHILD_CMAKELISTS})
  get_filename_component(module_dir ${module_cmake} DIRECTORY)
  message(STATUS "🔧 Adding module: ${module_dir}")
  add_subdirectory(${module_dir})
endforeach()

