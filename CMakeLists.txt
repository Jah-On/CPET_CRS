CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
PROJECT(CPET_CRS)

# Set C++ stuff
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Include GLFW
include_directories(external/glfw)

# Include ImGui
include_directories(external/imgui)

# Include OpenGL
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories ( /System/Library/Frameworks )
    find_library(OpenGL_LIBRARY OpenGL )
    set(EXTRA_LIBS ${OpenGL_LIBRARY})
    target_link_libraries(runs_client ${EXTRA_LIBS})
elseif (WIN32)
link_libraries(opengl32)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
link_libraries(GL)
endif()

# Include project headers
include_directories(include)

file(GLOB SRC src/*.cpp)

add_executable(CPET_CRS ${SRC})
