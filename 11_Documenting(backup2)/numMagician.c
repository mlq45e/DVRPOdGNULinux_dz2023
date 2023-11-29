#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>
#include <libgen.h>
#include <locale.h>
#include <string.h>

#define _(STRING) gettext(STRING)

const char * rmnm[] = {"N","I","II","III","IV","V","VI","VII","VIII","IX",
	"X","XI","XII","XIII","XIV","XV","XVI","XVII","XVIII","XIX","XX","XXI",
	"XXII","XXIII","XXIV","XXV","XXVI","XXVII","XXVIII","XXIX","XXX","XXXI",
	"XXXII","XXXIII","XXXIV","XXXV","XXXVI","XXXVII","XXXVIII","XXXIX","XL",
	"XLI","XLII","XLIII","XLIV","XLV","XLVI","XLVII","XLVIII","XLIX","L","LI",
	"LII","LIII","LIV","LV","LVI","LVII","LVIII","LIX","LX","LXI","LXII",
	"LXIII","LXIV","LXV","LXVI","LXVII","LXVIII","LXIX","LXX","LXXI","LXXII",
	"LXXIII","LXXIV","LXXV","LXXVI","LXXVII","LXXVIII","LXXIX","LXXX","LXXXI",
	"LXXXII","LXXXIII","LXXXIV","LXXXV","LXXXVI","LXXXVII","LXXXVIII","LXXXIX",
	"XC","XCI","XCII","XCIII","XCIV","XCV","XCVI","XCVII","XCVIII","XCIX","C"};

int main(int argc, char* argv[])
{
	setlocale (LC_ALL, "");
	bindtextdomain ("numMagician", getenv("PWD"));
	textdomain ("numMagician");
	
	int rFlag = 0;
	
	if(argc>2||(argc==2&&argv[0][0]=='.'))
	{
		if(strlen(argv[argc-1])==6&&argv[argc-1][0]=='-'
			&&argv[argc-1][1]=='-'&&argv[argc-1][2]=='h'
			&&argv[argc-1][3]=='e'&&argv[argc-1][4]=='l'
			&&argv[argc-1][5]=='p')
		{
			printf(_("What is number magician? "));
			printf(_("It's an interesting programme. "));
			printf(_("You can play a number guess game here.\n"));
			printf(_("Optional: -r to use Roman numbers.\n"));
			printf(_("\t\t\t...what is Roman Number? "));
			printf(_("I can't include a whole wikipedia page in --help. :) "));
			printf(_("So, find out yourselves.\n"));
			return 0;
		}
		else if(strlen(argv[argc-1])==2&&argv[argc-1][0]=='-'
			&&argv[argc-1][1]=='r')
		{
			rFlag = 1;
		}
		else
		{
			printf("TRY: ./numMagician --help\n");
			return 0;
		}
	}

	if(rFlag) printf(_("Now please think of an integer between I and C and tell nobody.\n"));//
	else printf(_("Now please think of an integer between 1 and 100 and tell nobody.\n"));
	int ub = 101, lb = 0, cnt = 1, foo = 0, scErr = 0;
	char* r = (char*)calloc(100,sizeof(char));
	while(1)
	{
		if(ub-lb==1) foo++;
		
		if(!rFlag) printf(_("Is that number %d?[y/n]\n"), (int)((ub+lb)/2));
		else printf(_("Is that number %s?[y/n]\n"), rmnm[(int)((ub+lb)/2)]);//
		
		scErr = scanf("%s", r);
		if(r[0]=='y')
		{
			if(rFlag) printf(ngettext("Within %s time! Miraculous me!\n",//
				"Within %s times! Miraculous me!\n", cnt), rmnm[cnt]);
			else printf(ngettext("Within %d time! Miraculous me!\n",
				"Within %d times! Miraculous me!\n", cnt), cnt);
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
			if(rFlag) printf(_("It's larger or smaller than %s?[l/s]\n"), rmnm[(int)((ub+lb)/2)]);
			else printf(_("It's larger or smaller than %d?[l/s]\n"), (int)((ub+lb)/2));
			scErr = scanf("%s", r);
			if(r[0]=='l') lb = (int)((ub+lb)/2);
			else if(r[0]=='s') ub = (int)((ub+lb)/2);
			else r[0] = '0';
		}
		else r[0] = '0';
		
		if(r[0]=='0') printf(_("Be in awe! I'll ask you again, don't say irrelevant things\n"));
	}
	
	if(r[0]=='1') printf(_("See you next time!\n"));
	else if(r[0]=='2') printf(_(":-(\n"));
	
	return 0;
}
