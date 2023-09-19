#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printText(FILE *f, WINDOW *w, 
	int winbeginline, int winlinecnt, int winbegincol, int wincolcnt,
	int fbegincol, int fbeginline
)
{
	//(win_arg &) f_arg : begin with 0
	//doesn't have re-print border
	werase(w);
	fseek(f, 0, SEEK_SET);
	int i = 0, j = 0, k = 0;
	while(fbeginline > 0)
	{
		char tmpchar = fgetc(f);
		if(tmpchar == '\n') fbeginline--;
	}
	for(i = winbeginline; i <= winlinecnt; i++)
	{
		char *tmpline = (char*)calloc(wincolcnt+1, sizeof(char));
		fgets(tmpline, wincolcnt, f);
		tmpline[wincolcnt] = '\0';
		tmpline[wincolcnt+1] = '\0';
		if(feof(f)) break;
		for(k = 0; k < wincolcnt; k++) if(tmpline[k] == '\0') break;
		if(k <= fbegincol)
		{
			tmpline = (char*)calloc(2, sizeof(char));
			tmpline[0] = '\n';
			//~ tmpline[1] = '\0';
		}
		else
		{
			fseek(f, sizeof(char)*(fbegincol-k), SEEK_CUR);
			fgets(tmpline, wincolcnt, f);
			tmpline[wincolcnt] = '\0';
			tmpline[wincolcnt+1] = '\0';
		}
		move(i, winbegincol);
		waddstr(w, tmpline);
	}
	wrefresh(w);
}

int main(int argc, char *argv[])
{
	//
	WINDOW *win, *bigWin, *borderWin;
	FILE *f;
	int keyrightCnt = 0, keydownCnt = 0, flinecount = 0;
	//
	if(argc < 2)
	{
		printf("Please press in file name\n");
		return 1;
	}
	f = fopen(argv[1], "r");
	if(f == NULL)
	{
		printf("Can't open file\n");
		return 2;
	}
	//
	while(!feof(f))
	{
		char tmpchar = fgetc(f);
		if(tmpchar == '\n') flinecount++;
	}
	fseek(f, 0, SEEK_SET);
	//
	initscr();
	noecho();
	cbreak();
	refresh();
	borderWin = newwin(LINES-1, COLS, 1, 0);
	bigWin = newwin(LINES, COLS, 0, 0);
	win = newwin(LINES-3, COLS-2, 2, 1);
	keypad(win, TRUE);
	keypad(borderWin, TRUE);
	keypad(bigWin, TRUE);
	wborder(borderWin, '|', '|', '-','-','+', '+', '+', '+');
	move(0,0);
	waddstr(bigWin, argv[1]);
	wrefresh(bigWin);
	wrefresh(borderWin);
	printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
	//
	int pkey;
	while((pkey = wgetch(win)) != 27)
	{
		switch(pkey)
		{
			case KEY_UP:
			{
				if(keydownCnt == 0) beep();
				else
				{
					keydownCnt--;
					printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
				}
			}break;
			case KEY_DOWN:
			{
				if(keydownCnt+2>=flinecount) beep();
				else
				{
					keydownCnt++;
					printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
				}
			}break;
			case 32:
			{
				if(keydownCnt+1>=flinecount) beep();
				else
				{
					keydownCnt++;
					printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
				}
			}break;
			case KEY_RIGHT:
			{
				keyrightCnt++;
				printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
			}break;
			case KEY_LEFT:
			{
				if(keyrightCnt == 0) beep();
				else
				{
					keyrightCnt--;
					printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
				}
			}break;
			case KEY_NPAGE:
			{
				if(keydownCnt + LINES - 4 >= flinecount) beep();
				else
				{
					keydownCnt = keydownCnt + LINES - 4;
					printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
				}
			}break;
			case KEY_PPAGE:
			{
				if(keydownCnt == 0) beep();
				else
				{
					keydownCnt = (keydownCnt - LINES + 4) >= 0 ? (keydownCnt - LINES + 4) : 0;
					printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
				}
			}break;
			case KEY_HOME:
			{
				keydownCnt = 0;
				printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
			}break;
			case KEY_END:
			{
				keydownCnt = flinecount-LINES+6;
				printText(f, win, 2, LINES-3, 1, COLS-2, keyrightCnt, keydownCnt);
			}break;
			default:
				//~ printf("%d\n", pkey);
			break;
		}
	}
    //
    endwin();
    fclose(f);
    //
	return 0;
}
