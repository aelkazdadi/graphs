cmake_minimum_required (VERSION 2.6)
project (Graph)
include_directories(~/RO/include)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O9")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(source ${source}
    src/graph.c
    src/size.c
    src/clean.c
)

add_executable(edgelist src/edgelist.c src/graph.c)
add_executable(size src/size.c src/graph.c)
add_executable(clean_data src/clean.c src/graph.c)
