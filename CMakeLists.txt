cmake_minimum_required(VERSION 3.16)

# -----------------------------------------------------------------------------
# Project
# -----------------------------------------------------------------------------
project(Illuvatar
        VERSION 0.0.1
        HOMEPAGE_URL "https://github.com/Xisabla/Illuvatar"
        LANGUAGES CXX)

message(STATUS "Building project ${PROJECT_NAME} v${PROJECT_VERSION}")

# -----------------------------------------------------------------------------
# Compiler and build config
# -----------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif ()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Set code DEBUG mode if build type is Debug
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Debug mode enabled")
    add_compile_definitions(DEBUG)
endif ()


set(CMAKE_CXX_STANDARD 20)

# -----------------------------------------------------------------------------
# Project files
# -----------------------------------------------------------------------------
# Source files
set(SOURCES
        include/enums/Direction.h src/enums/Direction.cpp
        include/enums/DirectionUtils.h src/enums/DirectionUtils.cpp
        include/enums/Faction.h src/enums/Faction.cpp
        include/enums/RollResult.h src/enums/RollResult.cpp
        include/enums/ThingAtPoint.h src/enums/ThingAtPoint.cpp
        include/characters/BadMinion.h src/characters/BadMinion.cpp
        include/characters/Character.h src/characters/Character.cpp
        include/characters/Dragon.h
        include/characters/Eldar.h
        include/characters/GoodMinion.h src/characters/GoodMinion.cpp
        include/characters/Master.h src/characters/Master.cpp
        include/characters/Minion.h src/characters/Minion.cpp
        include/characters/Vala.h
        include/characters/Werewolf.h
        include/core/Game.h src/core/Game.cpp
        include/gui/MainWindow.h src/gui/MainWindow.cpp
        include/gui/QGameMap.h src/gui/QGameMap.cpp
        include/gui/QGameSidebar.h src/gui/QGameSidebar.cpp
        include/gui/QGameWrapper.h src/gui/QGameWrapper.cpp
        include/map/Domain.h src/map/Domain.cpp
        include/map/Map.h src/map/Map.cpp
        include/map/Tile.h src/map/Tile.cpp
        include/map/pathFinder.h src/map/pathFinder.cpp
        include/templates/Singleton.h
        include/unirand.h src/unirand.cpp
        include/superTypes
        src/core/main.cpp)

# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------
# Qt
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Qt AutoMoc
QT5_WRAP_CPP(MOC_FILES
        include/gui/QGameSidebar.h)
set(CMAKE AUTO_MOC ON)

# -----------------------------------------------------------------------------
# Build and linking instructions
# -----------------------------------------------------------------------------
add_executable(Illuvatar ${SOURCES} ${MOC_FILES})

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(Illuvatar Qt5::Core Qt5::Gui Qt5::Widgets)
