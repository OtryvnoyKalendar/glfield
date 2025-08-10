cmake_minimum_required(VERSION 3.15)

set(PRINT_FOUND_SOURCES false)
set(PRINT_FOUND_INCLUDE_DIRECTORIES false)

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
		set_compilers(i686-w64-mingw32-gcc i686-w64-mingw32-g++)
		set_bin_dir(windows-32bit)
	else()
		set_compilers(x86_64-w64-mingw32-gcc x86_64-w64-mingw32-g++)
		set_bin_dir(windows-64bit)
	endif()
elseif(WIN32)
	message("Сборка на Windows")
	message(WARNING "Cборка с mingw32-g++ не проверялась и может не работать")
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

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

if(WIN_CROSS OR WIN32)
	set(FILE_EXTENSION ".exe")
else()
	set(FILE_EXTENSION ".unix")
endif()
project("glfield${FILE_EXTENSION}")

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

if(MSVC)
    add_compile_options(/W4 /permissive- /std:c++17 /O2)
else()
    add_compile_options(-Wall -Wextra -pedantic -std=c++17 -O2)
endif()

if(WIN_CROSS)
	add_compile_definitions(
		SFML_STATIC
		UNICODE _UNICODE
	)
endif()

set(CODE_DIRECTORIES "CommonCode" "src")

set(INCLUDE_DIRS)
foreach(dir IN LISTS CODE_DIRECTORIES)
    file(GLOB_RECURSE HEADER_FILES "${dir}/*.h" "${dir}/*.hpp")
    foreach(header_file IN LISTS HEADER_FILES)
        get_filename_component(header_dir "${header_file}" DIRECTORY)
        list(FIND INCLUDE_DIRS "${header_dir}" index)
        if(index EQUAL -1)
            list(APPEND INCLUDE_DIRS "${header_dir}")
        endif()
    endforeach()
endforeach()
if(PRINT_FOUND_INCLUDE_DIRECTORIES)
	message("Include directories with headers: ${INCLUDE_DIRS}")
endif()
include_directories(${INCLUDE_DIRS})

set(ALL_SOURCES)
foreach(dir IN LISTS CODE_DIRECTORIES)
    file(GLOB_RECURSE SOURCES "${dir}/*.cpp")
	if(PRINT_FOUND_SOURCES)
		message("Found sources: ${SOURCES}")
	endif()
    list(APPEND ALL_SOURCES ${SOURCES})
endforeach()

add_executable(${PROJECT_NAME} ${ALL_SOURCES})

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
		SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System
	)
endif()

