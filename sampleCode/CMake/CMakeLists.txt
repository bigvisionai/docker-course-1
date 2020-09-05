# SPECIFY THE MINIMUM VERSION OF CMAKE REQUIRED
cmake_minimum_required(VERSION 2.8.12)

# SPECIFY YOUR PROJECT NAME
PROJECT(sampleCode)

# Find OpenCV in the system
find_package(OpenCV REQUIRED PATHS "/usr/local/lib/cmake/opencv4")


# INCLUDE OPENCV DIRECTORIES
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(main main.cpp)

# This command links the libraries to the executable file
target_link_libraries(main ${OpenCV_LIBS})
set_property(TARGET main PROPERTY CXX_STANDARD 14)
