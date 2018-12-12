#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "usrmenu.h"



int game()
{
	initscr();
	clear();
	int i,pp,ch,k,r,hdw,start,zize,steps=0,HPOS;
	cbreak();
	start_color();
	WINDOW *win[3],*ww;
	WINordo *topwin,*sectower,*thrtower;
	DrWinStr top ,*buff;
	HPOS=DEV-DEV/2;
	int WIDTH=(DEV-HPOS)*2;
	//int wdw=WIDTH-2;
	keypad(stdscr,TRUE);
	//noecho();
	echo();
	curs_set(0);
	k=my_menu();
	noecho();
	hdw=HEIGHT/9;
	refresh();
	for(i=0;i<3;i++)
	{
		win[i]=makwin(WIDTH,HPOS+DEV*i);
	}

	topwin=Xmalloc();
	sectower=Xmalloc();
	thrtower=Xmalloc();
	
	topwin->current_window=win[0];
	sectower->current_window=win[1];
	thrtower->current_window=win[2];

	topwin->next=sectower;
	sectower->next=thrtower;
	thrtower->next=topwin;


	pp=getmaxy(topwin->current_window);
	refresh();
	
	for(i=0;i<3;i++)
	{
		topwin->stack=XXmalloc();
		topwin->stack->topwindow=NULL;
		topwin->stack->starty=pp-1;
		topwin->stack->startx=0;
		topwin->stack->sizex=0;
		topwin->stack->sizey=0;
		topwin->stack->col_pair=0;
		topwin->stack->next=NULL;
		topwin=topwin->next;
	}
	for (i=1;i<k+1;i++)
	{
		buff=topwin->stack;
		topwin->stack=XXmalloc();
		topwin->stack->topwindow=DerivWin(topwin->current_window,hdw,WIDTH-i*2,pp-1-hdw*i,i,i+1);
		topwin->stack->starty=pp-1-hdw*i;
		topwin->stack->startx=i;
		topwin->stack->sizex=WIDTH-i*2;
		topwin->stack->sizey=hdw;
		topwin->stack->col_pair=(i+1);
		topwin->stack->next=buff;
	}
	start=(int)&topwin->current_window;
	zize=(int)topwin->stack->sizex;
	refresh();
	mvprintw(0,0,"control keys:\nLEFT,RIGHT- change tower,\nUP- take a ring,\nDOWN- put a ring.");
	wrefresh(topwin->current_window);

	
	//syncok(stdscr,TRUE);
	buff=NULL;
		top.topwindow=NULL;
		top.starty=pp-1;
		top.startx=0;
		top.sizex=0;
		top.sizey=0;
		top.col_pair=0;
		top.next=NULL;
	//arrow print
		mvwaddch(topwin->current_window,1,WIDTH/2,ACS_DARROW|COLOR_PAIR(1)|A_REVERSE);
		for(r=-1;r<2;r++)
		{mvwaddch(topwin->current_window,0,WIDTH/2+r,ACS_VLINE|COLOR_PAIR(1)|A_REVERSE);}
		wrefresh(topwin->current_window);
	//arrow print
	while((ch=getch())!=KEY_F(1))
	{
		PrintWarnMess("                                          ");
		switch (ch)
		{
			case KEY_UP:
				
				if(top.sizex)PrintWarnMess("**at first put a ring**");
				//if(top.sizex)mvprintw(VPOS+HEIGHT,COLS/2,"at first put a ring");
				else if(topwin->stack->topwindow==NULL)PrintWarnMess("**nothing to take**");
				//else if(topwin->stack->topwindow==NULL)mvprintw(VPOS+HEIGHT,COLS/2,"nothing to take");
				else 
				{
					top=*topwin->stack;
					buff=topwin->stack;
					Delderwin(topwin->stack->topwindow);
					//free(topwin->stack);
					if(topwin->stack->next != NULL)topwin->stack=topwin->stack->next;
						else
						{
							topwin->stack->topwindow=NULL;
							topwin->stack->starty=pp-1;
							topwin->stack->startx=0;
							topwin->stack->sizex=0;
							topwin->stack->sizey=0;
							topwin->stack->col_pair=0;
							topwin->stack->next=NULL;
							//topwin=topwin->next;
						}
				wrefresh(topwin->current_window);
				}
				free(buff);
				buff=NULL;
			break;
				
			case 261:
				
				topwin=topwin->next;
				//if(m)
				//{
					mvwaddch(topwin->next->next->current_window,1,WIDTH/2,ACS_VLINE);
					for(r=-1;r<2;r++)
					{mvwaddch(topwin->next->next->current_window,0,WIDTH/2+r,ACS_HLINE);}
					wrefresh(topwin->next->next->current_window);
				//}
				mvwaddch(topwin->current_window,1,WIDTH/2,ACS_DARROW|COLOR_PAIR(1)|A_REVERSE);
				for(r=-1;r<2;r++)
				{mvwaddch(topwin->current_window,0,WIDTH/2+r,ACS_VLINE|COLOR_PAIR(1)|A_REVERSE);}
				wrefresh(topwin->current_window);

				//m++;
			
			break;

			case 260:
				
				topwin=topwin->next->next;
				//if(m)
				//{
					mvwaddch(topwin->next->current_window,1,WIDTH/2,ACS_VLINE);
					for(r=-1;r<2;r++)
					{mvwaddch(topwin->next->current_window,0,WIDTH/2+r,ACS_HLINE);}
					wrefresh(topwin->next->current_window);
				//}
				mvwaddch(topwin->current_window,1,WIDTH/2,ACS_DARROW|COLOR_PAIR(1)|A_REVERSE);
				for(r=-1;r<2;r++)
				{mvwaddch(topwin->current_window,0,WIDTH/2+r,ACS_VLINE|COLOR_PAIR(1)|A_REVERSE);}
				wrefresh(topwin->current_window);

				//m++;
			
			break;
			case KEY_DOWN:

			if(top.sizex)
			{
				if(topwin->stack->sizey)
				{
					//buff=topwin->stack;
					//topwin->stack->next=topwin->stack;
					//topwin->stack->next=buff;
					if(topwin->stack->startx<top.startx)
					{
						//topwin->stack->topwindow=DerivWin(topwin->current_window,topwin->stack->next->starty-hdw,topwin->stack->next->startx-1,top.sizey,top.sizex,top.col_pair);
					buff=topwin->stack;
					topwin->stack=XXmalloc();
					topwin->stack->next=buff;
					topwin->stack->topwindow=DerivWin(topwin->current_window,top.sizey,top.sizex,topwin->stack->next->starty-hdw,WIDTH/2-top.sizex/2,top.col_pair);
					topwin->stack->starty=topwin->stack->next->starty-hdw;
					topwin->stack->startx=WIDTH/2-top.sizex/2;
					topwin->stack->sizey=top.sizey;
					topwin->stack->sizex=top.sizex;
					topwin->stack->col_pair=top.col_pair;
					//topwin->stack->next=buff;
					buff=NULL;
					
					top.topwindow=NULL;
					top.starty=pp-1;
					top.startx=0;
					top.sizex=0;
					top.sizey=0;
					top.col_pair=0;
					top.next=NULL;
					}
					else {PrintWarnMess("**Imposible movement**");break;}
				}else 
				{
					buff=topwin->stack;
					topwin->stack=XXmalloc();
					topwin->stack->topwindow=DerivWin(topwin->current_window,top.sizey,top.sizex,pp-1-hdw,WIDTH/2-top.sizex/2,top.col_pair);
					topwin->stack->starty=pp-1-hdw;
					topwin->stack->startx=WIDTH/2-top.sizex/2;
					topwin->stack->sizey=top.sizey;
					topwin->stack->sizex=top.sizex;
					topwin->stack->col_pair=top.col_pair;
					topwin->stack->next=buff;
					buff=NULL;

					top.topwindow=NULL;
					top.starty=pp-1;
					top.startx=0;
					top.sizex=0;
					top.sizey=0;
					top.col_pair=0;
					top.next=NULL;
				}
				steps++;
				wrefresh(topwin->stack->topwindow);
			}else PrintWarnMess("**take a ring**");
			break;
		}
		if((start!=(int)&topwin->current_window)&&(!topwin->next->stack->topwindow)&&(!topwin->next->next->stack->topwindow)&&((int)topwin->stack->sizex==zize)&&(!top.topwindow))
		{
			ww=newwin(4,28,VPOS/*-4*/,COLS/2-14);
			box(ww,0,0);
			wbkgd(ww,COLOR_PAIR(9)|A_REVERSE);
			mvwprintw(ww,0,4,"Congratulation!!!!!!");
			mvwprintw(ww,1,2,"you've won,for %d steps",steps);
			mvwprintw(ww,2,3,"press any key. to exit.");
			wrefresh(ww);
			getch();
			wclear(ww);
			werase(ww);
			delwin(ww);
			break;
		}
	}

	mvprintw(0,0,"             \n                         \n                \n                 ");
	PurgeTowers(topwin);
	//erase();
	//clear();

	endwin();
	return 0;
}
