cmake_minimum_required(VERSION 3.0)

project(Hanoi_Tower)
#packages
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED) 

include_directories(${CURSES_LIBRARIES})

set(Sources demo.c game.c my_menu.c usrmenu.c)
set(Headers demo.h game.h usrmenu.h )

file(GLOB files_to_copy about.txt)
file(COPY ${files_to_copy} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Hanoi_Tower ${Sources} ${Headers})
if(CURSES_HAVE_NCURSES_H)
	target_include_directories(Hanoi_Tower PRIVATE ${CURSES_INCLUDE_DIR})
	#else(CURSES_HAVE_NCURSES_NCURSES_H)
else()
	target_include_directories(Hanoi_Tower PRIVATE ${CURSES_INCLUDE_DIR}/ncurses)
endif(CURSES_HAVE_NCURSES_H)
target_link_libraries(Hanoi_Tower ${CURSES_LIBRARIES} menu)
