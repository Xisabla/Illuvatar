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
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Set code DEBUG mode if build type is Debug
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	message(STATUS "Debug mode enabled")
	add_compile_definitions(DEBUG)
endif()


set(CMAKE_CXX_STANDARD 20)

# -----------------------------------------------------------------------------
# Project files
# -----------------------------------------------------------------------------
# Source files
set(SOURCES
		include/map/map.h src/map/map.cpp
		include/core/main_window.h src/core/main_window.cpp
		src/core/main.cpp)

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
