# CMake entry point
cmake_minimum_required (VERSION 3.5)
set(PROJECT_NAME "Bomberman")
project (${PROJECT_NAME})

set (PLATFORM ${CMAKE_SYSTEM_NAME})

message("Detected Platform ${PLATFORM}")

set(ARCH x86)
#SDL
set(SDL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/SDL2/include)
set(SDL_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/SDL2/lib/${ARCH})
set(SDL_LIB ${SDL_LIB_DIR}/SDL2.lib)

#SDL_Image
set(SDL_IMAGE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/SDL2_image/include)
set(SDL_IMAGE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/SDL2_image/lib/${ARCH})
set(SDL_IMAGE_LIB ${SDL_IMAGE_LIB_DIR}/SDL2_image.lib)

#SDL_TTF
set(SDL_TTF_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/SDL2_ttf/include)
set(SDL_TTF_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/SDL2_ttf/lib/${ARCH})
set(SDL_TTF_LIB ${SDL_TTF_LIB_DIR}/SDL2_ttf.lib)

#SDL_Mixer
set(SDL_MIXER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/SDL2_Mixer/include)
set(SDL_MIXER_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/SDL2_Mixer/lib/${ARCH})
set(SDL_MIXER_LIB ${SDL_MIXER_LIB_DIR}/SDL2_Mixer.lib)

#GLEW
set(GLEW_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/glew/include)
set(GLEW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/${PLATFORM}/glew/lib/Release/${ARCH})
set(GLEW_LIB ${GLEW_LIB_DIR}/glew32.lib)

#OPENGL
if (WIN32)
find_package(OpenGL)
endif()

#GLM
set(GLM_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

set(TARGSRC "targsrc/")

set(SOURCE
	${TARGSRC}main.cpp
	${TARGSRC}GUI.cpp
	${TARGSRC}UIElement.cpp
	${TARGSRC}UIGroup.cpp
)

set(INCLUDE "include/")
set(HEADERS
	${INCLUDE}main.hpp
	${INCLUDE}UIElement.hpp
	${INCLUDE}UIGroup.hpp
)

set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${INCLUDE} ${SDL_INCLUDE} ${SDL_IMAGE_INCLUDE} ${SDL_TTF_INCLUDE} ${SDL_MIXER_INCLUDE} ${GLEW_INCLUDE} ${GLM_INCLUDE})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${SDL_LIB} ${SDL_TTF_LIB} ${SDL_IMAGE_LIB} ${GLEW_LIB} ${SDL_MIXER_LIB} ${OPENGL_gl_LIBRARY})

if (WIN32)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD				# Adds a post-build event to copy SDL dll to bin dir
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 					
        "${SDL_LIB_DIR}/SDL2.dll"	#input-file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
		
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different					
        "${SDL_TTF_LIB_DIR}/SDL2_ttf.dll" "${SDL_TTF_LIB_DIR}/libfreetype-6.dll" "${SDL_TTF_LIB_DIR}/zlib1.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
		
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 					
        "${SDL_IMAGE_LIB_DIR}/SDL2_image.dll" "${SDL_IMAGE_LIB_DIR}/libjpeg-9.dll" "${SDL_IMAGE_LIB_DIR}/libpng16-16.dll" "${SDL_IMAGE_LIB_DIR}/libtiff-5.dll" "${SDL_IMAGE_LIB_DIR}/libwebp-4.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 					
        "${SDL_MIXER_LIB_DIR}/SDL2_mixer.dll" "${SDL_MIXER_LIB_DIR}/libFLAC-8.dll" "${SDL_MIXER_LIB_DIR}/libmodplug-1.dll" "${SDL_MIXER_LIB_DIR}/libogg-0.dll" 
		"${SDL_MIXER_LIB_DIR}/libvorbis-0.dll" "${SDL_MIXER_LIB_DIR}/libvorbisfile-3.dll" "${SDL_MIXER_LIB_DIR}/smpeg2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
		
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD				# Adds a post-build event to copy SDL dll to bin dir
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 					
        "${GLEW_LIB_DIR}/glew32.dll"	#input-file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()