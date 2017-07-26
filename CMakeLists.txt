# CMake entry point
cmake_minimum_required (VERSION 3.5)
set(PROJECT_NAME "Bomberman")
project (${PROJECT_NAME})


set(ARCH x86)
#SDL
set(SDL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include)
set(SDL_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/lib/${ARCH})
set(SDL_LIB ${SDL_LIB_DIR}/SDL2.lib)

#GLEW/OPENGL
set(GLEW_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include)
set(GLEW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib/Release/${ARCH})
set(GLEW_LIB ${GLEW_LIB_DIR}/glew32.lib)

if (WIN32)
find_package(OpenGL)

endif()
set(TARGSRC "targsrc/")

set(SOURCE
	${TARGSRC}main.cpp
	${TARGSRC}GUI.cpp
)

set(INCLUDE "include/")
set(HEADERS
	${INCLUDE}main.hpp
)

set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${INCLUDE} ${SDL_INCLUDE} ${GLEW_INCLUDE})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${SDL_LIB}  ${GLEW_LIB}  ${OPENGL_gl_LIBRARY})

if (WIN32)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD				# Adds a post-build event to copy SDL dll to bin dir
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 					
        "${SDL_LIB_DIR}/SDL2.dll"	#input-file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
		
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD				# Adds a post-build event to copy SDL dll to bin dir
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 					
        "${GLEW_LIB_DIR}/glew32.dll"	#input-file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()