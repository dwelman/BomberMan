# CMake entry point
cmake_minimum_required (VERSION 3.5)
set(PROJECT_NAME "Bomberman")
project (${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-std=c++11")

set(CMAKE_BUILD_TYPE Debug)

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
	
	#CEGUI
	set(CEGUI_LIBS	CEGUIBase-0_Static
					CEGUICommonDialogs-0_Static 
					CEGUICoreWindowRendererSet_Static 
					CEGUIExpatParser_Static 
					CEGUIOpenGLRenderer-0_Static
					CEGUISILLYImageCodec_Static)
					
	set(CEGUI_LIBS_DYNAMIC	CEGUIBase-0_d
				CEGUICommonDialogs-0_d
				CEGUICoreWindowRendererSet_d
				CEGUIExpatParser_d
				CEGUIOpenGLRenderer-0_d
				CEGUISILLYImageCodec_d)
		

	message ("${CEGUI_LIBS_DYNAMIC}")	
	set(CEGUI_LIB_PATH	${CMAKE_CURRENT_SOURCE_DIR}/libs/Windows/cegui)
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

	set(CEGUI_LIBS_DYNAMIC	CEGUIBase-0.dylib
			CEGUICommonDialogs-0.dylib
			CEGUICoreWindowRendererSet.dylib
			CEGUIExpatParser.dylib
			CEGUIOpenGLRenderer-0.dylib
			CEGUISILLYImageCodec.dylib)

	set(CEGUI_LIB_PATH	${CMAKE_CURRENT_SOURCE_DIR}/libs/darwin/cegui)
	
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})
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
		${TARGSRC}Vec3.cpp
		${TARGSRC}UIElement.cpp
		${TARGSRC}GUIRenderer.cpp
		${TARGSRC}Clock.cpp		
		${TARGSRC}InjectInput.cpp
		${TARGSRC}Events.cpp
		${TARGSRC}RenderObject.cpp
		${TARGSRC}Setting.cpp
		${TARGSRC}Util.cpp
		${TARGSRC}GameObjectRenderInfo.cpp
		)

set(COMPSRC "targsrc/components/")
set(SOURCE_COMP
		${COMPSRC}Position.cpp
		${COMPSRC}Collision.cpp
		${COMPSRC}BaseComponent.cpp
		${COMPSRC}Movement.cpp
		${COMPSRC}Render.cpp
		${COMPSRC}PlayerController.cpp
		${COMPSRC}Bomb.cpp
		${COMPSRC}Explosion.cpp
		${COMPSRC}Tag.cpp
		${COMPSRC}Powerup.cpp
		)

set(SYSSOURCE "targsrc/systems/")
set(SOURCE_SYS
		${SYSSOURCE}CollisionSystem.cpp
		${SYSSOURCE}MovementSystem.cpp
		${SYSSOURCE}PlayerControllerSystem.cpp
		${SYSSOURCE}BombSystem.cpp
		${SYSSOURCE}TagSystem.cpp
		${SYSSOURCE}RenderSystem.cpp
		)

set(INCLUDE "include/")
set(HEADERS
		${INCLUDE}main.hpp
		${INCLUDE}MenuStateMachine.hpp
		${INCLUDE}RenderEngine.hpp
		${INCLUDE}ConfigEditor.hpp
		${INCLUDE}VBOIndexer.hpp
		${INCLUDE}GameManager.hpp
		${INCLUDE}Entity.hpp
		${INCLUDE}Vec3.hpp
		${INCLUDE}UIElement.hpp
		${INCLUDE}GUI.hpp
		${INCLUDE}GUIRenderer.hpp
		${INCLUDE}Clock.hpp
		${INCLUDE}RenderObject.hpp
		${INCLUDE}Settings.hpp
		${INCLUDE}Util.hpp
		${INCLUDE}GameObjectRenderInfo.hpp
		)

set(COMP_INCL "include/components/")
set(HEADERS_COMP
		${COMP_INCL}Position.hpp
		${COMP_INCL}Collision.hpp
		${COMP_INCL}BaseComponent.hpp
		${COMP_INCL}Movement.hpp
		${COMP_INCL}Render.hpp
		${COMP_INCL}PlayerController.hpp
		${COMP_INCL}Bomb.hpp
		${COMP_INCL}Tag.hpp
		${COMP_INCL}Explosion.hpp
		${COMP_INCL}Powerup.hpp
		)

set(SYS_INCL "include/systems/")
set(HEADERS_SYS
		${SYS_INCL}CollisionSystem.hpp
		${SYS_INCL}MovementSystem.hpp
		${SYS_INCL}PlayerControllerSystem.hpp
		${SYS_INCL}BombSystem.hpp
		${SYS_INCL}TagSystem.hpp
		${SYS_INCL}RenderSystem.hpp
		)

set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )

include_directories(${INCLUDE} ${SDL_INCLUDE} ${SDL_IMAGE_INCLUDE} ${SDL_TTF_INCLUDE} ${SDL_MIXER_INCLUDE} ${GLEW_INCLUDE} ${GLM_INCLUDE} ${OPENGL_INCLUDE})

link_directories(${SDL_LIB_DIR} ${SDL_TTF_LIB_DIR} ${SDL_IMAGE_LIB_DIR}  ${SDL_MIXER_LIB_DIR} ${GLEW_LIB_DIR} ${CEGUI_LIB_PATH})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS} ${SOURCE_COMP} ${SOURCE_SYS} ${HEADERS_COMP} ${HEADERS_SYS})

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_ttf SDL2_image ${GLEW_NAME} SDL2_mixer ${OPENGL_gl_LIBRARY} ${CEGUI_LIBS_DYNAMIC})

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

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${GLEW_LIB_DIR}/glew32.dll"
			$<TARGET_FILE_DIR:${PROJECT_NAME}>)
			
	#CEGUI + Dependancies
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CEGUI_LIB_PATH}/CEGUIBase-0_d.dll" "${CEGUI_LIB_PATH}/CEGUICommonDialogs-0_d.dll" "${CEGUI_LIB_PATH}/CEGUICoreWindowRendererSet_d.dll" 
		"${CEGUI_LIB_PATH}/CEGUIOpenGLRenderer-0_d.dll" "${CEGUI_LIB_PATH}/CEGUISILLYImageCodec_d.dll" "${CEGUI_LIB_PATH}/CEGUIExpatParser_d.dll"
		"${CEGUI_LIB_PATH}/freetype_d.dll" "${CEGUI_LIB_PATH}/glew_d.dll" "${CEGUI_LIB_PATH}/glfw_d.dll" "${CEGUI_LIB_PATH}/jpeg_d.dll" "${CEGUI_LIB_PATH}/libexpat_d.dll" 
		"${CEGUI_LIB_PATH}/libpng_d.dll" "${CEGUI_LIB_PATH}/pcre_d.dll" "${CEGUI_LIB_PATH}/SILLY_d.dll" "${CEGUI_LIB_PATH}/zlib_d.dll"
		#"${CEGUI_LIB_PATH}/freetype.dll" "${CEGUI_LIB_PATH}/glew.dll" "${CEGUI_LIB_PATH}/glfw.dll" "${CEGUI_LIB_PATH}/jpeg.dll" "${CEGUI_LIB_PATH}/libexpat.dll" 
		#"${CEGUI_LIB_PATH}/libpng.dll" "${CEGUI_LIB_PATH}/pcre.dll" "${CEGUI_LIB_PATH}/SILLY.dll" "${CEGUI_LIB_PATH}/zlib.dll"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
		
endif()