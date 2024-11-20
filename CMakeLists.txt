CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
PROJECT(CPET_CRS)

# Set C++ stuff
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Include OGL
find_library(OpenGL_LIBRARY OpenGL )

# Include GLFW
SET(GLFW_BUILD_X11 0)
include_directories(external/glfw/include)
add_subdirectory(external/glfw)

# Include ImGui
include_directories(external/imgui external/imgui/backends)
file(GLOB IMGUI external/imgui/*.cpp)
add_library(imgui ${IMGUI})

# Include project headers
include_directories(include)

file(GLOB SRC src/*.cpp)

add_executable(CPET_CRS ${SRC})
# target_link_libraries(CPET_CRS OpenGL::OpenGL)
target_link_libraries(CPET_CRS glfw)
target_link_libraries(CPET_CRS imgui)
