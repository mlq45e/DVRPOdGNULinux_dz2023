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
		int iTmp=atoi(argv[1]);
		float fTmp=atof(argv[1]);
		float fN=atof(argv[2]);
		if(iTmp-fTmp!=0)
		{
			float i=fTmp;
			if(fN>=i) for(;i<fN;i+=1) printf("%f\n", i);
			else for(;i>fN;i-=1) printf("%f\n", i);
		}
		else
		{
			int i=iTmp;
			if(fN>=i) for(;i<fN;i++) printf("%d\n", i);
			else for(;i>fN;i--) printf("%d\n", i);
		}
	}
	else if(argc==4)
	{
		int iTmp=atoi(argv[3]);
		float fTmp=atof(argv[3]);
		float fN=atof(argv[2]);
		float i=atof(argv[1]);
		if(fTmp==0) printf("error: step is too small.\n");
		else if(iTmp-fTmp!=0)
		{
			float fH=fTmp;
			if(fH>0) for(;i<fN;i+=fH) printf("%f\n", i);
			else for(;i>fN;i+=fH) printf("%f\n", i);
		}
		else
		{
			int fH=iTmp;
			if(fH>0) for(;i<fN;i+=fH) printf("%d\n", (int)i);
			else for(;i>fN;i+=fH) printf("%d\n", (int)i);
		}
	}
	return 0;
}
