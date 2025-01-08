cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(spp)

# set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG ")

set(HEADERS include/entities.hpp include/linalg.hpp)
set(SOURCES src/entities.cpp src/linalg.cpp ${HEADERS})
add_executable(game main.cpp ${SOURCES})
target_include_directories(game PUBLIC include)
target_link_libraries(game PRIVATE sfml-system sfml-graphics sfml-window)

add_custom_target(launch
    COMMAND game
    DEPENDS game
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
