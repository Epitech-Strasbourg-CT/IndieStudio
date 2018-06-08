cmake_minimum_required(VERSION 3.5.1)
project(bomberman)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS "-W -Wall -Wextra -g ")

# region src
add_executable(bomberman
        src/main.cpp
        src/Singletons/StateMachine.cpp
        include/Singletons/StateMachine.hpp
        src/Game/AEntity.cpp
        src/Abstracts/AState.cpp
        include/Abstracts/AState.hpp
        include/Game/AEntity.hpp
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
        src/States/SettingsState.cpp
        include/States/SettingsState.hpp
        src/States/BackgroundState.cpp
        include/States/BackgroundState.hpp
        src/Abstracts/AStateShare.cpp
        include/Abstracts/AStateShare.hpp
        src/States/GameState.cpp
        include/States/GameState.hpp
        src/Game/EntitiesMap.cpp
        include/Game/EntitiesMap.hpp
        src/Game/EntityFactory.cpp
        include/Game/EntityFactory.hpp
        src/Game/SaveManager.cpp
        include/Game/SaveManager.hpp

        include/Game/ATrackable.hpp
        include/Game/AMovable.hpp

        src/Game/Controllable.cpp
        include/Game/Controllable.hpp

        src/Game/AController.cpp
        include/Game/AController.hpp

        src/Game/BKeyboardController.cpp
        include/Game/BKeyboardController.hpp

        src/Game/BIAController.cpp
        include/Game/BIAController.hpp

        src/Game/Entities/PlayerEntity.cpp
        include/Game/Entities/PlayerEntity.hpp

        src/Game/Entities/PotEntity.cpp
        include/Game/Entities/PotEntity.hpp

        src/Game/Entities/BlockEntity.cpp
        include/Game/Entities/BlockEntity.hpp

        src/Game/Entities/BombEntity.cpp
        include/Game/Entities/BombEntity.hpp

        src/Game/Entities/FireEntity.cpp
        include/Game/Entities/FireEntity.hpp

        src/Game/Entities/BonusEntity.cpp
        include/Game/Entities/BonusEntity.hpp

        src/Game/SphericalCoordinate.cpp
        include/Game/SphericalCoordinate.hpp

        src/States/AIChooseState.cpp
        include/States/AIChooseState.hpp

        src/States/PauseState.cpp
        include/States/PauseState.hpp

        src/Game/Traveling.cpp
        include/Game/Traveling.hpp

        src/Abstracts/ABombDropper.cpp
        include/Abstracts/ABombDropper.hpp
        src/States/LoadState.cpp
        include/States/LoadState.hpp
        include/Game/Entities/AAnimatedEntity.cpp
        include/Game/Entities/AAnimatedEntity.hpp

        src/States/TransitionToGameState.cpp
        include/States/TransitionToGameState.hpp)

# endregion

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
endif(WIN32)

set(IRRKLANG_DIR ./libs/irrklang)
if(UNIX)
        add_custom_command(TARGET bomberman PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/libs/irrklang/bin/linux-gcc-64/ikpFlac.so
                ${PROJECT_SOURCE_DIR}/bin/ikpFlac.so)
        add_custom_command(TARGET bomberman PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/libs/irrklang/bin/linux-gcc-64/ikpMP3.so
                ${PROJECT_SOURCE_DIR}/bin/ikpMP3.so)
        set(IRRKLANG_LIBRARY ${PROJECT_SOURCE_DIR}/libs/irrklang/bin/linux-gcc-64/libIrrKlang.so)
endif(UNIX)
if(WIN32)
        add_custom_command(TARGET bomberman PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/libs/irrklang/bin/winx64-visualStudio/ikpFlac.dll
                ${PROJECT_SOURCE_DIR}/bin/ikpFlac.dll)
        add_custom_command(TARGET bomberman PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/libs/irrklang/bin/winx64-visualStudio/ikpMP3.dll
                ${PROJECT_SOURCE_DIR}/bin/ikpMP3.dll)
        add_custom_command(TARGET bomberman PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/libs/irrklang/bin/winx64-visualStudio/irrKlang.dll
                ${PROJECT_SOURCE_DIR}/bin/irrKlang.dll)
    set(IRRKLANG_LIBRARY ${PROJECT_SOURCE_DIR}/libs/irrklang/lib/Winx64-visualStudio/irrKlang.lib)
endif(WIN32)

target_link_libraries(bomberman ${IRRKLANG_LIBRARY})
target_include_directories(bomberman PRIVATE ${IRRKLANG_DIR}/include)