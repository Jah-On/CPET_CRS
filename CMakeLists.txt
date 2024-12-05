CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
PROJECT(CPET_CRS)

# Set C++ stuff
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Include OGL
find_package(OpenGL REQUIRED COMPONENTS OpenGL)

# Include GLFW
include_directories(external/glfw/include)
add_subdirectory(external/glfw)
SET(GLFW_BUILD_WAYLAND TRUE)
SET(GLFW_BUILD_X11     FALSE)

# Include ImGui
include_directories(/usr/include/freetype2)
include_directories(external/imgui external/imgui/backends)
file(GLOB IMGUI
	external/imgui/*.cpp
	external/imgui/backends/imgui_impl_opengl3.cpp
	external/imgui/backends/imgui_impl_glfw.cpp
	external/imgui/misc/cpp/imgui_stdlib.cpp
)
add_library(imgui ${IMGUI})

# Include project headers
include_directories(include)

file(GLOB SRC src/*.cpp src/GUI/*.cpp)

add_executable(CPET_CRS ${SRC})
target_link_libraries(CPET_CRS GL glfw imgui)
