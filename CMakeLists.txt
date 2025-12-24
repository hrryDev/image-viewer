cmake_minimum_required(VERSION 3.10)
project(ImageViewer C)

find_package(SDL2 REQUIRED)

include_directories(
	$(SDL_include_dirs)
	include
)

add_executable(ImageViewer src/main.c)

target_link_libraries(sdl
	PRIVATE SDL2::SDL2
)
