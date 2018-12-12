#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "usrmenu.h"



int demo()
{
	initscr();
	clear();
	int i,pp,k,ch,hdw,start,zize,parity,buff_size=0,buff_size2=0,HPOS;
	cbreak();
	start_color();
	WINDOW *win[3];
	WINordo *topwin,*sectower,*thrtower,*buff_topwin,*buff_topwin2,*recent;
	DrWinStr top ,*buff,*buff_stack;
	HPOS=DEV-DEV/2;
	int WIDTH=(DEV-HPOS)*2;
	//int wdw=WIDTH-2;
	keypad(stdscr,TRUE);
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
	//mvprintw(0,0,"control keys:\nLEFT,RIGHT- change tower,\nUP- take a ring,\nDOWN- put a ring.");
	wrefresh(topwin->current_window);

	//wait for 1 movement	
	timeout (600);
	getch();
	//(ch=getch())==KEY_F(1);
	buff=NULL;
		top.topwindow=NULL;
		top.starty=pp-1;
		top.startx=0;
		top.sizex=0;
		top.sizey=0;
		top.col_pair=0;
		top.next=NULL;

		parity=1;
		for(i=0;i<3;i++)
		{
			if(topwin->stack->sizex==zize)
			{
				//topwin=topwin->next;
				break;
			}
			else topwin=topwin->next;
		}
		buff_stack=topwin->stack;
		for(i=0;i<k;i++)
		{
			if((buff_stack->next->sizex)==(buff_stack->sizex)+2)
			{
				parity++;
				//continue;
			}
			else break;
			buff_stack=buff_stack->next;
		}
		
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
	//take small	
		if(parity%2)
	{
		topwin=topwin->next->next;
	}
	else
	{
		topwin=topwin->next;
	}
	
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
			//else {PrintWarnMess("**Imposible movement**");break;}
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
//end small ring	
	while(1)
	{
			//new list
		timeout (600);
		if((ch=getch())==KEY_F(1))break;
		//getch();




		buff_size2=0;
		buff_size=0;
		topwin=topwin->next;
		buff_topwin=topwin;
		if(topwin->stack->sizex!=0)
		{
			buff_size=topwin->stack->sizex;
		}
		topwin=topwin->next;
		buff_topwin2=topwin;
		if(topwin->stack->sizex)buff_size2=topwin->stack->sizex;

		if(((buff_size<buff_size2)&&buff_size)||(!buff_size2))topwin=buff_topwin;
		else topwin=buff_topwin2;
		//take 2
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
		//search for non small ring;
		topwin=topwin->next;
		if (topwin->stack->sizex==zize)topwin=topwin->next;
		recent=topwin;
		//put2
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
		timeout (600);
		if((ch=getch())==KEY_F(1))break;
		//getch();

		parity=1;
		for(i=0;i<3;i++)
		{
			if(topwin->stack->sizex==zize)
			{
				//topwin=topwin->next;
				break;
			}
			else topwin=topwin->next;
		}
		buff_stack=topwin->stack;
		for(i=0;i<k;i++)
		{
			if((buff_stack->next->sizex)==(buff_stack->sizex)+2)
			{
				parity++;
				//continue;
			}
			else break;
			buff_stack=buff_stack->next;
		}
		
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
	//take small	
		/*buff_size=0;
		buff_size2=0;
		topwin=topwin->next;
		buff_topwin=topwin;
		if(topwin->stack->sizex)buff_size=topwin->stack->sizex;

		topwin=topwin->next;
		buff_topwin2=topwin;
		if(topwin->stack->sizex)buff_size2=topwin->stack->sizex;

		//if((buff_size<buff_size2)&&buff_size)topwin=buff_topwin;
		//else topwin=buff_topwin2;*/
		if(parity%2)
	{
		//if((buff_size<buff_size2)||(!buff_size2))topwin=buff_topwin;
		topwin=recent;
	}
	else
	{
		topwin=topwin->next;
		if(topwin==recent)topwin=topwin->next;
		//topwin=buff_topwin2;
	}
	
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
//end small ring	
		//getch();
		if((start!=(int)&topwin->current_window)&&(!topwin->next->stack->topwindow)&&(!topwin->next->next->stack->topwindow)&&((int)topwin->stack->sizex==zize)&&(!top.topwindow))
		{
			PrintWarnMess("Congratulation!!!!!!       you've won,press any key to exit");
			timeout(-1);
			getch();
			PrintWarnMess("                                                           ");
			break;
		}
		//timeout (600);
		//if((ch=getch())==KEY_F(1))break;
	}

	mvprintw(0,0,"             \n                         \n                \n                 ");
	PurgeTowers(topwin);
	endwin();
	return 0;
}
