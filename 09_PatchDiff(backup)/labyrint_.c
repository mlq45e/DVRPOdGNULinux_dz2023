#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int args, char* argv[])
{
	int size = 6;
	char wall = '#';
	char space = '.';
	//
	srand(time(NULL));
	//
	for(int i=0; i<2*size+1; i++) printf("%c", wall);
	printf("\n");
	for(int i=0; i<2*size+1; i++)
	{
		printf("%c",wall);
		//
		if(i%2)
		{
			for(int j=0; j<2*size-1; j++)
			{
				if(!(j%2)) printf("%c", space);
				else
				{
					if(rand()%2) printf("%c", space);
					else printf("%c", wall);
				}
			}
		}
		else
		{
			
		}
		//
		printf("%c\n",wall);
	}
	
	return 0;
}
	
