cmake_minimum_required(VERSION 3.5)

project(GameOfLife)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt4 REQUIRED)
add_executable(game_of_life
	board.cpp board.h
	field.cpp field.h
	window.cpp window.h
	main.cpp
)
target_link_libraries(game_of_life
	Qt4::QtGui
	Qt4::QtDBus
)
