cmake_minimum_required(VERSION 3.10)
project(ImageViewer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED CONFIG)

include_directories(
	${SDL_include_dirs}
	include
)

add_executable(ImageViewer
	src/main.c
	src/file_utils.c
	src/ppm.c
	src/window.c
)

target_link_libraries(ImageViewer 
	PRIVATE SDL2::SDL2
)
