#include "rhash.h" /* LibRHash interface */
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "config.h"

#ifndef RDLN
#define RDLN 0
#endif

void handle_str_rhash_helper(const char* msg, char alg, char prnf)
{
	if(alg == '0') return;
	
	char digest[64];
	char output[130];
	
	rhash_library_init(); /* initialize static data */
	
	int res = rhash_msg((alg=='s')?RHASH_SHA1:((alg=='m')?RHASH_MD5:RHASH_TTH), msg, strlen(msg), digest);
	if(res < 0)
	{
		fprintf(stderr, "rhasher (string): message digest calculation error\n");
		return;
	}
	
	/* convert binary digest to print_format string */
	rhash_print_bytes(output, digest, rhash_get_digest_size((alg=='s')?RHASH_SHA1:((alg=='m')?RHASH_MD5:RHASH_TTH)),
		(prnf=='h')?RHPR_HEX:RHPR_BASE64);
	
	printf("%s\n", output);
}
void handle_file_rhash_helper(const char* filepath, char alg, char prnf)
{
	if(alg == '0') return;
	
	char digest[64];
	char output[130];
	
	rhash_library_init(); /* initialize static data */
	
	int res = rhash_file((alg=='s')?RHASH_SHA1:((alg=='m')?RHASH_MD5:RHASH_TTH), filepath, digest);
	if(res < 0)
	{
		fprintf(stderr, "rhasher (file): LibRHash error: %s: %s\n", filepath, strerror(errno));
		return;
	}
	
	/* convert binary digest to print_format string */
	rhash_print_bytes(output, digest, rhash_get_digest_size((alg=='s')?RHASH_SHA1:((alg=='m')?RHASH_MD5:RHASH_TTH)),
		(prnf=='h')?RHPR_HEX:RHPR_BASE64);
	
	printf("%s\n", output);
}

int main(int argc, char *argv[])
{
	ssize_t flag = 0;
	char * line = NULL;
	if(RDLN)
	{
		while((line = readline("")))
		{
			char* tok = strtok(line," \n");
			char format = (tok[0]>='A'&&tok[0]<='Z')?'h':'b';
			for(int i=0;i<strlen(tok);i++) tok[i] = (tok[i]<='Z'&&tok[i]>='A')?tok[i]-'A'+'a':tok[i];
			char al = '0';
			if(strcmp(tok,"sha1")==0) al = 's';
			else if(strcmp(tok,"md5")==0) al = 'm';
			else if(strcmp(tok,"tth")==0) al = 't';
			else
			{
				fprintf(stderr, "rhasher: can't recognize algorithm\n");
				continue;
			}
			tok = strtok(NULL," \n");
			if(!tok)
			{
				fprintf(stderr, "rhasher: wrong useage\n");
				continue;
			}
			if(tok[0] == '\"') handle_file_rhash_helper(tok+1,al,format);
			else handle_str_rhash_helper(tok,al,format);
		}
	}
	else
	{
		while((flag = getline(&line, NULL, stdin)) != -1)
		{
			char* tok = strtok(line," \n");
			char format = (tok[0]>='A'&&tok[0]<='Z')?'h':'b';
			for(int i=0;i<strlen(tok);i++) tok[i] = (tok[i]<='Z'&&tok[i]>='A')?tok[i]-'A'+'a':tok[i];
			char al = '0';
			if(strcmp(tok,"sha1")==0) al = 's';
			else if(strcmp(tok,"md5")==0) al = 'm';
			else if(strcmp(tok,"tth")==0) al = 't';
			else
			{
				fprintf(stderr, "rhasher: can't recognize algorithm\n");
				continue;
			}
			tok = strtok(NULL," \n");
			if(!tok)
			{
				fprintf(stderr, "rhasher: wrong useage\n");
				continue;
			}
			if(tok[0] == '\"') handle_file_rhash_helper(tok+1,al,format);
			else handle_str_rhash_helper(tok,al,format);
		}
	}
	
	return 0;
}
