# CMakeLists.txt
cmake_minimum_required(VERSION 3.17)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${ProjectId})

file(GLOB HEADER_FILES *.h)
file(GLOB SRC_FILES *.cpp)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)