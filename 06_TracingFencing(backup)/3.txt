#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc<3)
	{
		printf("program argument error\n");
		return -1;
	}
	FILE* infile = fopen(argv[1], "r");
	if(infile==NULL) {perror("infile fopen error:"); return -2;}
	FILE* outfile = fopen(argv[2], "w");
	if(outfile==NULL) {perror("outfile fopen error"); return -3;}
	int cnt = 1, ec = 0;
	char c = fgetc(infile);
	while(1)
	{
		if(c<0)
		{
			int ret = -4;
			char cnts[10];
			sprintf(cnts, "%d", cnt);
			char errstr[30] = "fgetc error | count=";
			strcat(errstr,cnts);
			perror(errstr);
			ec = fclose(infile);
			if(ec!=0) {perror("infile fclose(in fgetc err) error"); ret--;}
			ec = fclose(outfile);
			if(ec!=0) {perror("outfile fclose(in fgetc err) error"); ret--;}
			ec = remove(argv[2]);
			if(ec!=0) {perror("remove outfile (in fgetc err) error"); ret--;}
			return ret; // -4/-5/-6/-7
		}
		ec = fputc(c,outfile);
		if(ec<0)
		{
			int ret = -8;
			char cnts[10];
			sprintf(cnts, "%d", cnt);
			char errstr[30] = "fputc error | count=";
			strcat(errstr,cnts);
			perror(errstr);
			ec = fclose(infile);
			if(ec!=0) {perror("infile fclose(in fputc err) error"); ret--;}
			ec = fclose(outfile);
			if(ec!=0) {perror("outfile fclose(in fputc err) error"); ret--;}
			ec = remove(argv[2]);
			if(ec!=0) {perror("remove outfile (in fputc err) error"); ret--;}
			return ret; // -8/-9/-10/-11
		}
		cnt++;
		c = fgetc(infile);
		if(feof(infile)) break;
	}
	ec = fclose(infile);
	if(ec!=0) 
	{
		int ret = -12;
		perror("infile fclose error (end)");
		ec = fclose(outfile);
		if(ec!=0) {perror("... and outfile fclose error (end)"); ret--;}
		ec = remove(argv[2]);
		if(ec!=0) {perror("remove outfile (in infile fclose err) error"); ret--;}
		return ret; // -12/-13/-14
	}
	ec = fclose(outfile);
	if(ec!=0)
	{
		int ret = -15;
		perror("outfile fclose error (end)");
		ec = remove(argv[2]);
		if(ec!=0) {perror("remove outfile (outfile fclose err) error"); ret--;}
		return ret; // -15/-16
	}
	ec = remove(argv[1]);
	if(ec!=0) {perror("remove infile (end) error"); return -17;}
	return 0;
}
