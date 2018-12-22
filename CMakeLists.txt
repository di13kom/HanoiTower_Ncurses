cmake_minimum_required(VERSION 3.0)

project(Hanoi_Tower)
#packages
set(CURSES_NEED_NCURSES TRUE)
find_package(CURSES REQUIRED MODULE) 
#find_library(NCURSES ncurses) 
find_library(TERMCAP termcap)
find_library(GPM gpm)
find_library(MENU menu) 

message(${CURSES_INCLUDE_DIR})
message(${CURSES_LIBRARY})
message(${CURSES_LIBRARIES})

set(Sources demo.c game.c my_menu.c usrmenu.c)
set(Headers demo.h game.h usrmenu.h )

add_executable(Hanoi_Tower ${Sources} ${Headers})
if(CURSES_HAVE_NCURSES_H)
	target_include_directories(Hanoi_Tower PRIVATE ${CURSES_INCLUDE_DIR})
	#else(CURSES_HAVE_NCURSES_NCURSES_H)
else()
	target_include_directories(Hanoi_Tower PRIVATE ${CURSES_INCLUDE_DIR}/ncurses)
endif(CURSES_HAVE_NCURSES_H)
	target_link_libraries(Hanoi_Tower ncurses termcap gpm menu)
