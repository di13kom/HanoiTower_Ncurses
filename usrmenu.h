#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#ifndef _MENU_H
#define _MENU_H

#define HEIGHT LINES/1.3
#define VPOS (LINES/2)/3

#define DEV COLS/4
//#define HPOS DEV-DEV/2
//#define	hdw HEIGHT/9
typedef struct _DRWIN_
{
	WINDOW *topwindow;
	int starty;
	int startx;
	int sizey;
	int sizex;
	int col_pair;
	struct _DRWIN_ *next;
}DrWinStr;

typedef struct _WINORD_
{
	WINDOW *current_window;
       	struct _WINORD_ *next;
	struct _DRWIN_ *stack;
}WINordo;


void menu();
int my_menu();


WINDOW *DerivWin(WINDOW *name,int hdw,int wdw,int starty,int startx,int col_pair);
void Delderwin(WINDOW *name);
WINordo *Xmalloc(void);
DrWinStr *XXmalloc(void);
WINDOW* makwin(int WIDTH,int yhpos);
void destwin(WINDOW *name);
void PurgeTowers(WINordo *topwin);
void PrintWarnMess(char * mess);
#endif
