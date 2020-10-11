# CMakeLists.txt
cmake_minimum_required(VERSION 3.17)
project(LearnOpengl)


message(- PKG_INC_PATH:${PKG_INC_PATH})
message(- PKG_LIB_PATH:${PKG_LIB_PATH})
message(- PKG_CONFIG_PATH:${PKG_CONFIG_PATH})

#find_package(opengl CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_subdirectory(ch1)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE glfw)
target_link_libraries(main PRIVATE glad::glad)