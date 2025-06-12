cmake_minimum_required(VERSION 3.15)

set(PRINT_FOUND_SOURCES false)

set(WIN_CROSS false)
set(WIN_32BIT false)

function(set_compilers c_compiler cxx_compiler)
    set(CMAKE_C_COMPILER "${c_compiler}" CACHE STRING "C compiler" FORCE)
    set(CMAKE_CXX_COMPILER "${cxx_compiler}" CACHE STRING "C++ compiler" FORCE)
endfunction()

function(set_bin_dir directory)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin/${directory}" CACHE STRING "Binary directory" FORCE)
	file(WRITE "cached_bin_dir.txt" "${directory}\n")
endfunction()

if(WIN_CROSS)
	message("Сборка на Linux под Windows")
	if(WIN_32BIT)
		message("Нужно поменять dll файлы на те, что лежат в win32, если раньше вы использовали 64-битную сборку")
		set_compilers(i686-w64-mingw32-gcc i686-w64-mingw32-g++)
		set_bin_dir(windows-32bit)
	else()
		set_compilers(x86_64-w64-mingw32-gcc x86_64-w64-mingw32-g++)
		set_bin_dir(windows-64bit)
	endif()
elseif(WIN32)
	message("Сборка на Windows")
	message("Cборка с mingw32-g++ не проверялась и может не работать")
	set_compilers(mingw32-gcc mingw32-g++)
	set_bin_dir(windows-64bit)
elseif(APPLE)
	message("Сборка на macOS")
	set_compilers(clang clang++)
	set_bin_dir(macos-64bit)
elseif(UNIX)
	message("Сборка на Linux")
	set_compilers(gcc g++)
	set_bin_dir(linux-64bit)
else()
	message(FATAL_ERROR "Неизвестная операционная система")
endif()


if(WIN_CROSS OR WIN32)
	set(FILE_EXTENSION ".exe")
else()
	set(FILE_EXTENSION ".unix")
endif()
project("glfield${FILE_EXTENSION}")

add_compile_options(
	-Wall -Wextra -pedantic -std=c++17 -O2
)

if(WIN_CROSS)
	add_compile_definitions(
		SFML_STATIC
		UNICODE _UNICODE
	)
endif()

set(COMMON_CODE_DIR "./CommonCode")

include_directories(src/game)
include_directories(src/)
include_directories("${COMMON_CODE_DIR}/include")

file(GLOB COMMON_SOURCES "${COMMON_CODE_DIR}/src/*.cpp")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/**/*.cpp")

add_executable(${PROJECT_NAME} src/main.cpp ${COMMON_SOURCES} ${SOURCES})
if(PRINT_FOUND_SOURCES)
	message("PROJECT_SOURCE_DIR: ${SOURCES} ${COMMON_SOURCES}")
endif()

if(WIN_CROSS)
	add_compile_options(
		-static
		-static-libgcc -static-libstdc++
	)
	target_link_libraries(${PROJECT_NAME}
		sfml-graphics sfml-window sfml-system
		opengl32 winmm gdi32 glu32 winpthread freetype
		
		sfml-audio
		OpenAL32 FLAC vorbisenc vorbisfile vorbis ogg

		sfml-network
		ws2_32
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

