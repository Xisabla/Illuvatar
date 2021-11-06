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
        include/core/MainWindow.h src/core/MainWindow.cpp
        include/enums/Result.h
        include/enums/Faction.h src/enums/Faction.cpp
        include/enums/Direction.h src/enums/Direction.cpp
        include/enums/ThingAtPoint.h src/enums/ThingAtPoint.cpp
        include/geometry/Point.h src/geometry/Point.cpp
        include/geometry/Rectangle.h src/geometry/Rectangle.cpp
        include/map/DirectionUtils.h src/map/DirectionUtils.cpp
        include/map/Generators.h src/map/Generators.cpp
        include/map/Map.h src/map/Map.cpp
        include/map/PathFinder.h src/map/PathFinder.cpp
        include/map/Tile.h src/map/Tile.cpp
        include/map/TileSet.h src/map/TileSet.cpp
        include/players/Alliance.h src/players/Alliance.cpp
        include/players/Character.h src/players/Character.cpp
        include/players/Dragon.h src/players/Dragon.cpp
        include/players/Eldar.h src/players/Eldar.cpp
        include/players/Horde.h src/players/Horde.cpp
        include/players/Master.h src/players/Master.cpp
        include/players/Minion.h src/players/Minion.cpp
        include/players/Vala.h src/players/Vala.cpp
        include/players/Werewolf.h src/players/Werewolf.cpp
        include/qt/QGameMap.h src/qt/QGameMap.cpp
        include/unirand.h src/unirand.cpp
        include/superTypes.h
        include/wip.h
        src/core/main.cpp
        )

# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------
# Qt
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# -----------------------------------------------------------------------------
# Build and linking instructions
# -----------------------------------------------------------------------------
add_executable(Illuvatar ${SOURCES})

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(Illuvatar Qt5::Core Qt5::Gui Qt5::Widgets)
