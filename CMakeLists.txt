cmake_minimum_required(VERSION 3.0.0)
project(graph-traversal VERSION 0.1.0)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")

# include(CTest)
# enable_testing()

add_executable(graph-traversal src/main.c src/node.c src/graph.c src/file_management.c src/neighbour.c src/coordinates.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
