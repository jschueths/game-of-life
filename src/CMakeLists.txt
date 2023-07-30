cmake_minimum_required(VERSION 3.17)

add_executable(game_of_life
	board.cpp board.hpp
	field.cpp field.hpp
	window.cpp window.hpp
	main.cpp
)
target_link_libraries(game_of_life
	Qt6::Widgets
)

