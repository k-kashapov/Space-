cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(spp)

# set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CXX_STANDARD C++20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -ggdb3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ggdb3 -Ofast")

set(HEADERS include/entities.hpp include/linalg.hpp include/models.hpp)
set(SOURCES src/entities.cpp src/linalg.cpp src/models.cpp ${HEADERS})
add_executable(game main.cpp ${SOURCES})
target_include_directories(game PUBLIC include)
target_link_libraries(game PRIVATE sfml-system sfml-graphics sfml-window)

add_custom_target(launch
    COMMAND game
    DEPENDS game font
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(font
    COMMAND cp ${CMAKE_SOURCE_DIR}/tecnica/Fonts/ttf/Tecnica-55.ttf ${CMAKE_BINARY_DIR}
    DEPENDS font
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
