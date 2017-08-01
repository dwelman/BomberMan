# CMake entry point
cmake_minimum_required (VERSION 3.5)
set(PROJECT_NAME "Bomberman")
project (${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-std=c++11")

set(cmake_build_type debug)

set (PLATFORM ${CMAKE_SYSTEM_NAME})

message("Detected Platform ${PLATFORM}")

set(ARCH x86)

#SDL
if (WIN32)
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
	set(GLEW_NAME glew32)
	message ("Found glew library at ${GLEW_LIB}")

	#OPENGL
	find_package(OpenGL)
else()
	set(BREW ~/.brew)
	set(BREW_INCLUDE ${BREW}/include)
	set(BREW_LIB ${BREW}/lib)

	#SDL
	set(SDL_INCLUDE ${BREW_INCLUDE}/SDL2)
	set(SDL_LIB_DIR ${BREW_LIB})
	set(SDL_LIB ${SDL_LIB_DIR}/libSDL2.a)
	message ("Found SDL2 library at ${SDL_LIB}")

	#SDL_ttf
	set(SDL_TTF_INCLUDE ${BREW_INCLUDE}/SDL2_ttf)
	set(SDL_TTF_LIB_DIR ${BREW_LIB})
	set(SDL_TTF_LIB ${SDL_LIB_DIR}/libSDL2_ttf.a)
	message ("Found SDL2_ttf library at ${SDL_TTF_LIB}")

	#SDL_image
	set(SDL_IMAGE_INCLUDE ${BREW_INCLUDE}/SDL2_image)
	set(SDL_IMAGE_LIB_DIR ${BREW_LIB})
	set(SDL_IMAGE_LIB ${SDL_IMAGE_LIB_DIR}/libSDL2_image.a)
	message ("Found SDL2_image library at ${SDL_IMAGE_LIB}")

	#SDL_mixer
	set(SDL_MIXER_INCLUDE ${BREW_INCLUDE}/SDL2_mixer)
	set(SDL_MIXER_LIB_DIR ${BREW_LIB})
	set(SDL_MIXER_LIB ${SDL_MIXER_LIB_DIR}/libSDL2_mixer.a)
	message ("Found SDL2_mixer library at ${SDL_MIXER_LIB}")

	#GLEW
	set(GLEW_INCLUDE ${BREW_INCLUDE}/)
	set(GLEW_LIB_DIR ${BREW_LIB})
	set(GLEW_LIB ${GLEW_LIB_DIR}/libGLEW.a)
	set(GLEW_NAME GLEW)
	message ("Found glew library at ${GLEW_LIB}")

	#OPENGL
	find_package(OpenGL)
	set(OPENGL_INCLUDE ${OPENGL_INCLUDE_DIR}/Headers)
	message ("Found OpenGL library at ${OPENGL_INCLUDE}")
	message ("Found OpenGL library at ${OPENGL_gl_LIBRARY}")

endif()

#GLM
set(GLM_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)

set(TARGSRC "targsrc/")
set(SOURCE
		${TARGSRC}main.cpp
		${TARGSRC}GUI.cpp
		${TARGSRC}RenderEngine.cpp
		${TARGSRC}MenuStateMachine.cpp
		${TARGSRC}ConfigEditor.cpp
		${TARGSRC}StateObject.cpp
		${TARGSRC}VBOIndexer.cpp
		${TARGSRC}GameManager.cpp
		${TARGSRC}Entity.cpp
		${TARGSRC}Vec3.cpp)

set(COMPSRC "targsrc/components/")
set(SOURCE_COMP
		${COMPSRC}Position.cpp
		${COMPSRC}Collision.cpp
		${COMPSRC}BaseComponent.cpp
		${COMPSRC}Movement.cpp
		${COMPSRC}Render.cpp)

set(INCLUDE "include/")
set(COMP_INCL "include/components/")
set(HEADERS
		${INCLUDE}main.hpp
		${INCLUDE}MenuStateMachine.hpp
		${INCLUDE}RenderEngine.hpp
		${INCLUDE}ConfigEditor.hpp
		${INCLUDE}VBOIndexer.hpp
		${INCLUDE}GameManager.hpp
		${INCLUDE}Entity.hpp
		${INCLUDE}Vec3.hpp)

set(COMP_INCL "include/components/")
set(HEADERS_COMP
		${COMP_INCL}Position.hpp
		${COMP_INCL}Collision.hpp
		${COMP_INCL}BaseComponent.hpp
		${COMP_INCL}Movement.hpp
		${COMP_INCL}Render.hpp)

set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${INCLUDE} ${SDL_INCLUDE} ${SDL_IMAGE_INCLUDE} ${SDL_TTF_INCLUDE} ${SDL_MIXER_INCLUDE} ${GLEW_INCLUDE} ${GLM_INCLUDE} ${OPENGL_INCLUDE})

link_directories(${SDL_LIB_DIR} ${SDL_TTF_LIB_DIR} ${SDL_IMAGE_LIB_DIR}  ${SDL_MIXER_LIB_DIR} ${GLEW_LIB_DIR})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS} ${SOURCE_COMP} ${HEADERS_COMP})

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_ttf SDL2_image ${GLEW_NAME} SDL2_mixer ${OPENGL_gl_LIBRARY})

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