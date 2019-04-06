cmake_minimum_required (VERSION 2.6)
project (Graph)
include_directories(include)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(source ${source}
    src/graph.c
    src/degree.c
    src/timer.c
)

file(COPY src/ex6.py DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/pagerank.py DESTINATION ${CMAKE_BINARY_DIR})

add_executable(load_structures src/load_structures.c ${source})
add_executable(size src/size.c ${source})
add_executable(clean_data src/clean.c ${source})
add_executable(ex4 src/ex4.c ${source})
add_executable(ex5 src/ex5.c ${source})
add_executable(bfs src/bfs.c ${source})
add_executable(triangles src/triangles.c ${source})
add_executable(pagerank src/pagerank.c ${source})
add_executable(core src/coredecomposition.c ${source})
target_link_libraries(pagerank m)
