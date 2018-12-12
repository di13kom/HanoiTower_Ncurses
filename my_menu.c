#include <curses.h>
#include <stdlib.h>
#include <menu.h>
#include "usrmenu.h"
#include "demo.h"
#include "game.h"

char *choise[]={
	"play game",
	"demo",
	"help",
	"Exit",
	(char *)NULL,
};

void func(int *chp);
void Out(WINDOW *main_win, MENU *my_menu, ITEM **items);
void PutText(WINDOW *wind);
int PrintAbout();
int main()
{
	//void (*func)(WINDOW *main_win, MENU *my_menu, ITEM **items);
	WINDOW *main_win;
	MENU *my_menu;
	ITEM **items;
	int i,y,x,ch,chp=1;
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	init_pair(1,COLOR_RED,COLOR_BLACK);

	items=(ITEM **)malloc(sizeof(ITEM*)*5);
	for(i=0;i<5;i++)
	{
		items[i]=new_item(choise[i]," ");
	}
	set_item_userptr(items[0],game);
	set_item_userptr(items[1],demo);
	//func=Out;
	set_item_userptr(items[2],PrintAbout);
	set_item_userptr(items[3],func);
	my_menu=new_menu((ITEM **)items);
	main_win=newwin(25,50,LINES/2-12,COLS/2-25);

	getmaxyx(main_win,y,x);
	set_menu_win(my_menu,main_win);
	set_menu_sub(my_menu,derwin(main_win,5,25,y-6,x/2-10));
	box(main_win,0,0);
	mvwvline(main_win,1,10,ACS_VLINE,y-2);
	mvwvline(main_win,1,x-11,ACS_VLINE,y-2);
	PutText(main_win);	
	//wbkgd(stdscr,COLOR_PAIR(1));
	//wbkgd(main_win,COLOR_PAIR(1));
	set_menu_mark(my_menu,">");
	//set_menu_fore(my_menu,COLOR_PAIR(1));
	post_menu(my_menu);
	refresh();
	wrefresh(main_win);
	
	//while((ch=getch())!=KEY_F(1)&&chp)
	while(chp)
	{
		ch=getch();
		switch(ch)
		{
			case KEY_UP:
				menu_driver(my_menu,REQ_UP_ITEM);
			break;	
			case KEY_DOWN:
				menu_driver(my_menu,REQ_DOWN_ITEM);
			break;
			case 10:
			{	
				//def_prog_mode();
				ITEM *cur;
				//void (*p)(char *);
				void (*p)(int *);

				cur = current_item(my_menu);
				p = item_userptr(cur);
				//p((char *)item_name(cur));
				p(&chp);
				pos_menu_cursor(my_menu);
				//clear();
				doupdate();
				redrawwin(stdscr);
				refresh();
				redrawwin(main_win);
				//reset_prog_mode();
				break;
			}
			break;
		}
		wrefresh(main_win);
	}
		
	Out(main_win,my_menu,items);
	/*unpost_menu(my_menu);
	free_menu(my_menu);
	for(i=0;i<5;i++)
	{
		free_item(items[i]);	
	}
	delwin(main_win);
	endwin();*/
	return 0;
}

void Out(WINDOW *main_win, MENU *my_menu, ITEM **items)
{
	int i;
	unpost_menu(my_menu);
	free_menu(my_menu);
	for(i=0;i<5;i++)
	{
		free_item(items[i]);	
	}
	delwin(main_win);
	endwin();
}

void func(int* chp)
{
	//int chp;
	//printw("hello");
	*chp=0;
	//return chp;
}

int PrintAbout()
{
	FILE *abfile;
	WINDOW *win_ab;
	char buff[48];
	int y,x,i;
	//initscr();
	clear();
	win_ab=newwin(25,50,LINES/2-12,COLS/2-25);
	box(win_ab,0,0);
	keypad(win_ab,TRUE);
	curs_set(0);
	refresh();
	abfile=fopen("about.txt","r");
	getmaxyx(win_ab,y,x);
	wattron(win_ab,COLOR_PAIR(1));
	mvwprintw(win_ab,y-2,2,"Press any key to exit");
	//mvwprintw(win_ab,y-2,2,"намке");
	wattroff(win_ab,COLOR_PAIR(1));
	if(!abfile)
	{
		wattron(win_ab,COLOR_PAIR(1));
		mvwprintw(win_ab,y/2,x/2-10,"about.txt not exist");
		wrefresh(win_ab);
		getch();
		wattroff(win_ab,COLOR_PAIR(1));
		return 0;
	}
	//wmove(win_ab,3,1);
	i=1;
	//while(!feof(abfile))
	while(1)
	{
		fgets(buff,48,abfile);	
		if(feof(abfile))break;
		mvwprintw(win_ab,i,2,"%s",buff);
		i++;
	}
	mvwprintw(win_ab,i,2,"_______________________");
	box(win_ab,0,0);
	keypad(win_ab,TRUE);
	wrefresh(win_ab);
	redrawwin(win_ab);
	getch();
	fclose(abfile);
	delwin(win_ab);
	//endwin();
	return 0;

}
void PutText(WINDOW *wind)
{
	//attr_set
	wattron(wind,A_BOLD);
	//letter t
	mvwaddch(wind,1,13,ACS_BLOCK);
	mvwaddch(wind,1,14,ACS_BLOCK);
	mvwaddch(wind,1,15,ACS_BLOCK);
	mvwaddch(wind,2,14,ACS_BLOCK);
	mvwaddch(wind,3,14,ACS_BLOCK);
	//letter o
	mvwaddch(wind,1,17,ACS_BLOCK);
	mvwaddch(wind,1,18,ACS_BLOCK);
	mvwaddch(wind,1,19,ACS_BLOCK);
	mvwaddch(wind,2,17,ACS_BLOCK);
	mvwaddch(wind,2,19,ACS_BLOCK);
	mvwaddch(wind,3,17,ACS_BLOCK);
	mvwaddch(wind,3,18,ACS_BLOCK);
	mvwaddch(wind,3,19,ACS_BLOCK);
	//letter w
	mvwaddch(wind,1,21,ACS_BLOCK);
	mvwaddch(wind,1,24,ACS_BLOCK);
	mvwaddch(wind,1,27,ACS_BLOCK);
	mvwaddch(wind,2,22,ACS_BLOCK);
	mvwaddch(wind,2,24,ACS_BLOCK);
	mvwaddch(wind,2,26,ACS_BLOCK);
	mvwaddch(wind,3,23,ACS_BLOCK);
	mvwaddch(wind,3,25,ACS_BLOCK);
	//letter e
	mvwaddch(wind,1,29,ACS_BLOCK);
	mvwaddch(wind,1,30,ACS_BLOCK);
	mvwaddch(wind,1,31,ACS_BLOCK);
	mvwaddch(wind,2,29,ACS_BLOCK);
	mvwaddch(wind,2,30,ACS_BLOCK);
	mvwaddch(wind,3,29,ACS_BLOCK);
	mvwaddch(wind,3,30,ACS_BLOCK);
	mvwaddch(wind,3,31,ACS_BLOCK);
	//letter r
	mvwaddch(wind,1,33,ACS_BLOCK);
	mvwaddch(wind,1,34,ACS_BLOCK);
	mvwaddch(wind,1,35,ACS_BLOCK);
	mvwaddch(wind,2,33,ACS_BLOCK);
	//mvwaddch(wind,2,35,ACS_BLOCK);
	mvwaddch(wind,2,34,ACS_BLOCK);
	mvwaddch(wind,3,33,ACS_BLOCK);
	mvwaddch(wind,3,35,ACS_BLOCK);
	
	//2-th line
	//letter o
	mvwaddch(wind,5,19,ACS_BLOCK);
	mvwaddch(wind,5,20,ACS_BLOCK);
	mvwaddch(wind,5,21,ACS_BLOCK);
	mvwaddch(wind,6,19,ACS_BLOCK);
	mvwaddch(wind,6,21,ACS_BLOCK);
	mvwaddch(wind,7,19,ACS_BLOCK);
	mvwaddch(wind,7,20,ACS_BLOCK);
	mvwaddch(wind,7,21,ACS_BLOCK);
	//letter f
	mvwaddch(wind,5,27,ACS_BLOCK);
	mvwaddch(wind,5,28,ACS_BLOCK);
	mvwaddch(wind,5,29,ACS_BLOCK);
	mvwaddch(wind,6,27,ACS_BLOCK);
	mvwaddch(wind,6,28,ACS_BLOCK);
	mvwaddch(wind,7,27,ACS_BLOCK);
	
	//3-th line
	//letter h
	mvwaddch(wind,9,15,ACS_BLOCK);
	//mvwaddch(wind,9,10,ACS_BLOCK);
	mvwaddch(wind,9,17,ACS_BLOCK);
	mvwaddch(wind,10,15,ACS_BLOCK);
	mvwaddch(wind,10,16,ACS_BLOCK);
	mvwaddch(wind,10,17,ACS_BLOCK);
	mvwaddch(wind,11,15,ACS_BLOCK);
	mvwaddch(wind,11,17,ACS_BLOCK);
	//letter a
	//mvwaddch(wind,9,5,ACS_BLOCK);
	mvwaddch(wind,9,20,ACS_BLOCK);
	//mvwaddch(wind,9,7,ACS_BLOCK);
	mvwaddch(wind,10,19,ACS_BLOCK);
	mvwaddch(wind,10,20,ACS_BLOCK);
	mvwaddch(wind,10,21,ACS_BLOCK);
	mvwaddch(wind,11,19,ACS_BLOCK);
	//mvwaddch(wind,11,6,ACS_BLOCK);
	mvwaddch(wind,11,21,ACS_BLOCK);
	//letter n
	mvwaddch(wind,9,23,ACS_BLOCK);
	mvwaddch(wind,9,24,ACS_BLOCK);
	mvwaddch(wind,9,25,ACS_BLOCK);
	mvwaddch(wind,10,23,ACS_BLOCK);
	mvwaddch(wind,10,25,ACS_BLOCK);
	//mvwaddch(wind,10,14,ACS_BLOCK);
	mvwaddch(wind,11,23,ACS_BLOCK);
	mvwaddch(wind,11,25,ACS_BLOCK);
	//letter o
	mvwaddch(wind,9,27,ACS_BLOCK);
	mvwaddch(wind,9,28,ACS_BLOCK);
	mvwaddch(wind,9,29,ACS_BLOCK);
	mvwaddch(wind,10,27,ACS_BLOCK);
	mvwaddch(wind,10,29,ACS_BLOCK);
	mvwaddch(wind,11,27,ACS_BLOCK);
	mvwaddch(wind,11,28,ACS_BLOCK);
	mvwaddch(wind,11,29,ACS_BLOCK);
	//letter i
	mvwaddch(wind,9,31,ACS_BLOCK);
	mvwaddch(wind,10,31,ACS_BLOCK);
	mvwaddch(wind,11,31,ACS_BLOCK);
	//mvwaddch(wind,10,21,ACS_BLOCK);
	//mvwaddch(wind,10,22,ACS_BLOCK);
	//mvwaddch(wind,10,23,ACS_BLOCK);
	//mvwaddch(wind,11,21,ACS_BLOCK);
	//mvwaddch(wind,11,23,ACS_BLOCK);
	wattroff(wind,A_BOLD|A_REVERSE);
}
