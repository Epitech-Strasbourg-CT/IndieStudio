cmake_minimum_required(VERSION 3.2)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/packages)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(Irrlicht)
include_directories(${IRRLICHT_INCLUDE_DIR})
message(${IRRLICHT_INCLUDE_DIR})

set(SOURCES
        main.cpp)


file(
        COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(bomberman ${SOURCES})
target_link_libraries(bomberman Irrlicht)

