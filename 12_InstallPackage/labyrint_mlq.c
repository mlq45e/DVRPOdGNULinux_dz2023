#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int args, char* argv[])
{
	//prepare
	char wall = '#';
	char space = '.';
	//randomly generate
	srand(time(NULL));
	int size = rand()%21;
	int lbrnt[size][size];
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			/* 0 ---- ; 1  |
			          ;    |   */
			lbrnt[i][j] = rand()%2;
			//old design; connected body may be more than 1
			/*
			if(i==size-1&&j==size-1&&lbrnt[i][j-1]&&!lbrnt[i-1][j])
				if(lbrnt[i][j]) lbrnt[i][j-1] = 0;
				else lbrnt[i-1][j] = 1;
			else if(j==size-1&&lbrnt[i][j-1]) lbrnt[i][j] = 1;
			else if(i==size-1&&!lbrnt[i-1][j]) lbrnt[i][j] = 0;
			*/
			//use 1st way (described below) :-)
			if(j==size-1) lbrnt[i][j] = 1;
			if(i==size-1) lbrnt[i][j] = 0;
		}
	}
	//connected body strictly = 1; by the way, between every pair of rooms only 1 way
	/* this kind of labyrinth design is  very simple;
	 * every room is connected with room right or below;
	 * of course maybe from some rooms can't go to any other rooms;
	 * I just don't want to change the fundamental design method;
	 * there are 2 possible make-up way:
	 * connected all right and bottom rooms (which is simple and I use this way),
	 * or from the bottom(right) edge of inconnected part go up(left) 
	 * to the last connected room and make it connected with the room right(below)
	 * (which need the third sign to represent connected with both rooms right and below
	 * and I'm too lazy to use this way).
	 */
	//print labyrinth
	for(int i=0;i<2*size+1;i++) printf("%c", wall);
	printf("\n");
	for(int i=0;i<size;i++) 
	{
		printf("%c", wall);
		for(int j=0;j<size;j++)
		{
			printf("%c", space);
			printf("%c", (lbrnt[i][j]||(i==size-1&&j==size-1))?wall:space);
		}
		printf("\n");
		if(i!=size-1)
		{
			printf("%c", wall);
			for(int j=0;j<size;j++)
			{
				printf("%c", (lbrnt[i][j])?space:wall);
				printf("%c", wall);
			}
			printf("\n");
		}
	}
	for(int i=0;i<2*size+1;i++) printf("%c", wall);
	printf("\n");
	//
	return 0;
}
	
