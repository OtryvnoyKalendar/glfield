cmake_minimum_required(VERSION 3.15)

set(PRINT_FOUND_SOURCES 0) # true / flase

set(WIN_CROSS 1) # true / flase
set(WIN_32BIT 0) # true / flase

if(WIN_CROSS)
	message("Сборка на Linux под Windows")
	if(WIN_32BIT)
		message("Нужно поменять dll файлы на те, что лежат в win32, если раньше вы использовали 64-битную сборку")
		set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
		set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
	else()
		set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
		set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
	endif()
elseif(WIN32)
	message("Сборка на Windows")
	message("Cборка с mingw32-g++ не проверялась и может не работать")
	set(CMAKE_C_COMPILER mingw32-gcc)
	set(CMAKE_CXX_COMPILER mingw32-g++)
elseif(APPLE)
	message("Сборка на macOS")
	set(CMAKE_C_COMPILER clang)
	set(CMAKE_CXX_COMPILER clang++)
elseif(UNIX)
	message("Сборка на Linux")
	set(CMAKE_C_COMPILER gcc)
	set(CMAKE_CXX_COMPILER g++)
else()
	message(FATAL_ERROR "Неизвестная операционная система")
endif()

project(glfield)

add_compile_options(
	-Wall -Wextra -pedantic -std=c++17
)

set(COMMON_CODE_DIR "./CommonCode")

include_directories(src/game)
include_directories(src/)
include_directories("${COMMON_CODE_DIR}/include")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

file(GLOB COMMON_SOURCES "${COMMON_CODE_DIR}/src/*.cpp")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/**/*.cpp")

add_executable(${PROJECT_NAME} src/main.cpp ${COMMON_SOURCES} ${SOURCES})
if(PRINT_FOUND_SOURCES)
	message("PROJECT_SOURCE_DIR: ${SOURCES} ${COMMON_SOURCES}")
endif()

if(WIN_CROSS)
	add_compile_options(
		-DSFML_STATIC
		-static
		-static-libgcc -static-libstdc++
	)
	target_link_libraries(${PROJECT_NAME}
		sfml-graphics sfml-window sfml-system
		opengl32 winmm gdi32 glu32 winpthread freetype
		
		sfml-audio
		OpenAL32 vorbis FLAC

		sfml-network
	)
elseif(WIN32)
	add_compile_options(
		-static-libgcc -static-libstdc++
	)
	target_link_libraries(${PROJECT_NAME}
		mingw32 opengl32 glu32 winmm
		gcc_s_dw2-1
		sfml-graphics sfml-window sfml-system sfml-audio sfml-network
		sfml-main
	)
else()
	target_link_libraries(${PROJECT_NAME}
		GL GLU
		sfml-graphics sfml-window sfml-system sfml-audio sfml-network
	)
endif()

