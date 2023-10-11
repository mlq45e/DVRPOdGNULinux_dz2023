#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(argc==1)
	{
		printf("help - range:\nrange(stop)\nrange(start, stop[, step])\nProduces a sequence of integers from start (inclusive) to stop (exclusive) by step.\n\
range(i, j) produces i, i+1, i+2, ..., j-1. Start defaults to 0, and stop is omitted!\nWhen step is given, it specifies the increment (or decrement).\n");
	}
	else if(argc==2)
	{
		int i=0;
		for(i=0;i<atof(argv[1]);i++) printf("%d\n", i);
	}
	else if(argc==3)
	{
		int i=0;
		for(i=atoi(argv[1]);i<atoi(argv[2]);i++)
			printf("%d\n", i);
	}
	else if(argc==4)
	{
		int i=0;
		for(i=atoi(argv[1]);i<atoi(argv[2]);i+=atoi(argv[3]))
			printf("%d\n", i);
	}
	return 0;
}
