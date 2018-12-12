#include <stdio.h>
#include <ncurses.h>
#include "usrmenu.h"

void menu()
{
	WINDOW *menuwin;
	initscr();
	start_color();
	init_pair(1,COLOR_RED,COLOR_GREEN);
	//init_pair(2,COLOR_WHITE,COLOR_BLUE);
	refresh();
	menuwin=newwin(15,30,15,5);
	wbkgd(menuwin,COLOR_PAIR(1));
	box(menuwin,0,0);
	mvwaddstr(menuwin,5,5,"hello");
	refresh();
	wrefresh(menuwin);
	//getch();
	getch();
	mvwaddstr(menuwin,5,5,"     ");
	wborder(menuwin,' ',' ',' ',' ',' ',' ',' ',' ');
	refresh();
	wrefresh(menuwin);
	delwin(menuwin);
	endwin();
	//return 0;
}

int my_menu()
{
	int num;
	WINDOW *lw;
	cbreak();
	lw=newwin(5,29,LINES/2,COLS/2-15);
	keypad(lw,TRUE);
	wattron(lw,COLOR_PAIR(1)|A_BOLD|A_REVERSE);
	//mvwchgat(lw,1,1,-1,COLOR_PAIR(1)|A_BOLD|A_REVERSE);
	box(lw,0,0);
	//wborder(lw, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	mvwprintw(lw,1,1,"   type the amout of rings ");
	mvwprintw(lw,2,1,"        from 3 to 8:       ");
	wattroff(lw,COLOR_PAIR(1)|A_BOLD|A_REVERSE);
	curs_set(0);
	do 
	{
		mvwprintw(lw,3,12,"        ");
		mvwscanw(lw,3,12,"%d",&num);
	}
	while (num>8||num<3);
	//getch();
	wrefresh(lw);
	wborder(lw, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(lw);
	delwin(lw);
	refresh();
	return num;
}




WINDOW* makwin(int WIDTH,int yhpos)
{
	WINDOW *winname;
	winname=newwin(HEIGHT,WIDTH,VPOS,yhpos);
	mvwvline(winname,0,WIDTH/2,ACS_VLINE,HEIGHT);
	box(winname,0,0);
	wrefresh(winname);
	return winname;
}

WINordo *Xmalloc(void)
{
	WINordo*  tt;
	tt=(WINordo *)malloc(sizeof(WINordo ));
	if(tt==NULL)printf("exhuasted memory");
				
	return tt;
}
DrWinStr *XXmalloc(void)
{
	DrWinStr*  tt2;
	tt2=(DrWinStr*)malloc(sizeof(DrWinStr));
	if(tt2==NULL)printf("exhuasted memory");
				
	return tt2;
}

void Delderwin(WINDOW *name)
{
	wbkgd(name,COLOR_PAIR(2));
	wborder(name,' ',' ',' ',' ',' ',' ',' ',' ');
	wrefresh(name);
	delwin(name);
	//refresh();
	//wrefresh(topwin->next->next->next->current_window);
}
WINDOW *DerivWin(WINDOW *name,int hdw,int wdw,int starty,int startx,int col_pair)
{
	WINDOW *drwn;
	refresh();
	drwn=derwin(name,hdw,wdw,starty,startx);
	box(drwn,0,0);
	init_pair(1, COLOR_RED,     COLOR_BLACK);
	init_pair(2, COLOR_GREEN,   COLOR_BLACK);
	init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
	init_pair(4, COLOR_BLUE,    COLOR_BLACK);
	init_pair(5, COLOR_CYAN,    COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	//init_pair(7, COLOR_BLACK,   COLOR_WHITE);
	init_pair(7, COLOR_GREEN,   COLOR_RED);
	init_pair(8, COLOR_WHITE,   COLOR_BLACK);
	init_pair(9, COLOR_RED,     COLOR_WHITE);
	wbkgd(drwn,COLOR_PAIR(col_pair)|A_REVERSE);
	wrefresh(drwn);
	return drwn;
}

void PurgeTowers(WINordo *topwin)
{
	
	DrWinStr *buff;
	WINordo *dbuff;
	int i;
	for (i=0;i<3;i++)
	{
		while(topwin->stack->next!=NULL)
		{

			buff=topwin->stack;
			Delderwin(topwin->stack->topwindow);
			topwin->stack=topwin->stack->next;
			free(buff);
		}
		topwin=topwin->next;
	}
	for(i=0;i<3;i++)
	{
		buff=topwin->stack;
		topwin=topwin->next;
		free(buff);
	}
	for(i=0;i<3;i++)
	{
		dbuff=topwin;
		delwin(topwin->current_window);
		topwin=topwin->next;
		free(dbuff);
	}

}
void PrintWarnMess(char * mess)
{
	attron(COLOR_PAIR(1)|A_BOLD);
	mvprintw(VPOS+HEIGHT,COLS/2-30,mess);
	attroff(COLOR_PAIR(1)|A_BOLD);
}
