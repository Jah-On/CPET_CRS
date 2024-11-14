CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
PROJECT(CPET_CRS)

# Set C++ stuff
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Include ImGui
include_directories(external/imgui)

# Include project headers
include_directories(include)

file(GLOB SRC src/*.cpp)

add_executable(CPET_CRS ${SRC})
