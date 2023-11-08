#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>
#include <libgen.h>
#include <locale.h>
#include "config.h"

#define _(STRING) gettext(STRING)
//~ #define LOCALE_PATH "../08_I18n"

int main(int argc, char* argv[])
{
	char *dir;
	dir = dirname(realpath(argv[0], NULL));
	setlocale (LC_ALL, "");
	//~ bindtextdomain ("numMagician", LOCALE_PATH);
	//~ textdomain ("numMagician");
	bindtextdomain (PACKAGE, LOCALE_PATH);
	textdomain (PACKAGE);
	
	printf(_("Now please think of an integer between 1 and 100 and tell nobody.\n"));
	int ub = 101, lb = 0, cnt = 1, foo = 0, scErr = 0;
	char* r = (char*)calloc(100,sizeof(char));
	while(1)
	{
		if(ub-lb==1) foo++;
		printf(_("Is that number %d?[y/n]\n"), (int)((ub+lb)/2));
		scErr = scanf("%s", r);
		if(r[0]=='y')
		{
			printf(ngettext("Within %d times! Miraculous me!\n"), cnt);
			printf(_("I'm a number magician! I know all secret of numbers!\n"));
			r[0] = '1';
			break;
		}
		else if (r[0]=='n')
		{
			if(ub==lb||(int)((ub+lb)/2)==100||foo==2) 
			{
				printf(_("You are fooling me! I'm angry! Spell on you!\n"));
				r[0] = '2';
				break;
			}
			cnt++;
			printf(_("It's larger or smaller than %d?[l/s]\n"), (int)((ub+lb)/2));
			scErr = scanf("%s", r);
			if(r[0]=='l') lb = (int)((ub+lb)/2);
			else if(r[0]=='s') ub = (int)((ub+lb)/2);
			else r[0] = '0';
			//~ printf(">>>>>>>>>>>>>>>>>>>>>>>>>%d                                    %d\n", ub,lb);
		}
		else r[0] = '0';
		
		if(r[0]=='0') printf(_("Be in awe! I'll ask you again, don't say irrelevant things\n"));
	}
	
	if(r[0]=='1') printf(_("See you next time!\n"));
	else if(r[0]=='2') printf(_(":-(\n"));
	
	return 0;
}
