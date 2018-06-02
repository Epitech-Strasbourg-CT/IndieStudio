cmake_minimum_required(VERSION 3.5.1)
project(bomberman)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


add_executable(bomberman
        #src/prout.cpp)
        src/main.cpp
        src/Singletons/StateMachine.cpp
        include/Singletons/StateMachine.hpp
        src/Game/EntityOperator.cpp
        src/Abstracts/AState.cpp
        include/Abstracts/AState.hpp
        include/Game/IEntity.hpp
        src/Singletons/IrrManager.cpp
        include/Singletons/IrrManager.hpp
        src/Singletons/IrrManager.cpp
        include/Singletons/IrrManager.hpp
        src/States/SplashState.cpp
        include/Time.hpp
        src/Time.cpp
        src/Singletons/IrrManager.cpp
        include/States/SplashState.hpp
        src/Singletons/AssetsPool.cpp
        include/Singletons/AssetsPool.hpp
        src/Singletons/EventReceiver.cpp
        include/Singletons/EventReceiver.hpp
        src/States/MenuState.cpp
        include/States/MenuState.hpp
        src/States/BackgroundState.cpp
        include/States/BackgroundState.hpp
        src/Abstracts/AStateShare.cpp
        include/Abstracts/AStateShare.hpp
        src/States/GameState.cpp
        include/States/GameState.hpp)

file(
        COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/bin")


set(IRRLICHT_SOURCE_DIR ./libs/irrlicht)
find_package(Irrlicht REQUIRED)
target_link_libraries(bomberman ${IRRLICHT_LIBRARY})
target_include_directories(bomberman PRIVATE ${IRRLICHT_INCLUDE_DIR})

if(WIN32)
    add_custom_command(TARGET bomberman PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ../libs/irrlicht/bin/Win64-VisualStudio/Irrlicht.dll
            ../bin/Irrlicht.dll)
endif()
