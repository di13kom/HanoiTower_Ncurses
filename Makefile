CFLAGS= -Wall -O2
#export	CFLAGS 

my_menu:libusrmenu.a  my_menu.c
	cc $(CFLAGS)  -static my_menu.c -L. -o $@ -lusrmenu -lmenu -lncurses -ltermcap -lgpm
libusrmenu.a:usrmenu.o game.o demo.o
	ar rcs  libusrmenu.a game.o demo.o usrmenu.o 
usrmenu.o:usrmenu.c
	cc $(CFLAGS) -c usrmenu.c -o $@ #-lncurses -ltermcap -fPIC  
game.o:game.c
	cc $(CFLAGS) -c game.c -o $@  #-lncurses -ltermcap -fPIC
demo.o:demo.c
	cc $(CFLAGS) -c demo.c -o $@  #-lncurses -ltermcap -fPIC
purge:
	rm demo.o  game.o libusrmenu.a usrmenu.o my_menu
clean:
	rm demo.o  game.o libusrmenu.a usrmenu.o 
