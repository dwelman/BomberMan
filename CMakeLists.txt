# CMake entry point
cmake_minimum_required (VERSION 3.5)
set(PROJECT_NAME "Bomberman")
project (${PROJECT_NAME})

set(TARGSRC "targsrc/")
set(SOURCE
	${TARGSRC}main.cpp
)

set(INCLUDE "include/")
set(HEADERS
	${INCLUDE}main.hpp
)

set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${INCLUDE})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})