#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define BAGSMAX 10

int esub_help1(char* ar[])
{
	regex_t rg;
	int rtn_ = regcomp(&rg, ar[1], REG_EXTENDED);
	if(rtn_)
	{
		size_t length = regerror(rtn_, &rg, NULL, 0);
		char* err = (char*)calloc(length,sizeof(char));
		regerror(rtn_, &rg, err, length);
		printf("[esub_help1]compile error: %s\n", err);
		return -3;
	}
	regmatch_t rgm;
	rtn_ = regexec(&rg, ar[3], 1, &rgm, 0);
	if(rtn_)
	{
		size_t length = regerror(rtn_, &rg, NULL, 0);
		char* err = (char*)calloc(length,sizeof(char));
		regerror(rtn_, &rg, err, length);
		printf("[esub_help1]execute error: %s\n", err);
		regfree(&rg);
		return -4;
	}
	int i = 0, j = 0;
	char* res = (char*)calloc(strlen(ar[3])+strlen(ar[2]),sizeof(char));
	while(i!=strlen(ar[3]))
	{
		if(i==rgm.rm_so)
		{
			while(j-i!=strlen(ar[2]))
			{
				res[j] = ar[2][j-i];
				j++;
			}
			i = rgm.rm_eo;
		}
		else
		{
			res[j] = ar[3][i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	printf("%s\n", res);
	return 0;
}
char* esub_takeOneRg(char* ar)
{
	char* res = (char*)calloc(strlen(ar),sizeof(char));
	int cnt_s = 0, i = 0, j = 0;
	while((ar[i]!=')'||cnt_s!=1)&&(ar[i]!='\0'))
	{
		if(ar[i]=='(') {cnt_s++; i++;}
		else if(ar[i]==')') {cnt_s--; i++;}
		else if((ar[i]=='\\')&&(ar[i+1]!='\0')&&((ar[i+1]=='(')||(ar[i+1]==')'))) {i++;}
		else {res[j] = ar[i]; j++; i++;}
	}
	return res;
}
int esub_helpMany(int expr, char* ar[])
{
	int subst[10] = {0,0,0,0,0,0,0,0,0,0};
	int i=0, j=0, k=0;
	while(ar[2][i]!='\0') {if(ar[2][i]=='\\'&&ar[2][i+1]>='0'&&ar[2][i+1]<='9') subst[ar[2][i+1]-'0']=i+1; i++;}
	if(subst[0]!=0) {printf("!!!wrong index 0 in substitution\n"); return -5;}
	for(i=9;i>1;i--) {if(subst[i]!=0&&subst[i-1]==0) {printf("!!!wrong index in substitution\n"); return -6;} if(subst[i]!=0) j++;}
	if(subst[1]!=0) j++;
	if(j!=expr) {printf("!!!can't match expressions and index\n"); return -7;}
	//
	char* ar1 = (char*)calloc(strlen(ar[1]),sizeof(char));
	i=1;
	j=0;
	while(ar[1][i]!='\0')
	{
		if(!((ar[1][i]=='('||ar[1][i]==')')&&ar[1][i-1]=='\\')) {ar1[j] = ar[1][i-1]; j++;}
		i++;
	}
	ar1[j] = ar[1][i-1];
	//
	regex_t* rg = (regex_t*)calloc(expr,sizeof(regex_t));
	j=0;
	for(i=0;i<expr;i++)
	{
		while(ar1[j]!='(') j++;
		char* onerg = esub_takeOneRg(ar1+j);
		j++;
		int rtn_ = regcomp(rg+i, onerg, REG_EXTENDED);
		if(rtn_)
		{
			size_t length = regerror(rtn_, rg+i, NULL, 0);
			char* err = (char*)calloc(length,sizeof(char));
			regerror(rtn_, rg+i, err, length);
			printf("[esub_helpMany]compile error: %s\n", err);
			return -8;
		}
	}
	regmatch_t* rgm = (regmatch_t*)calloc(expr*BAGSMAX, sizeof(regmatch_t));
	for(i=0;i<expr;i++)
	{
		int bgn = (i==0)?0:((rgm+(i-1)*BAGSMAX)->rm_eo);
		int rtn_ = regexec(rg+i, ar[3]+bgn, BAGSMAX, rgm+i*BAGSMAX, 0);
		if(rtn_)
		{
			size_t length = regerror(rtn_, rg+i, NULL, 0);
			char* err = (char*)calloc(length,sizeof(char));
			regerror(rtn_, rg+i, err, length);
			printf("[esub_helpMany]execute error: %s\n", err);
			for(i=0;i<expr;i++) regfree(rg+i);
			return -9;
		}
		(rgm+i*BAGSMAX)->rm_so += bgn;
		(rgm+i*BAGSMAX)->rm_eo += bgn;
	}
	//
	int wholelen = (strlen(ar[2])+strlen(ar[3]))*3;
	char* res = (char*)calloc(wholelen,sizeof(char));
	j=0;
	k=0;
	i=0;
	for(i=0;i<strlen(ar[2]);i++)
	{
		if(ar[2][i]=='\\'&&i!=strlen(ar[2])-1&&ar[2][i+1]>='1'&&ar[2][i+1]<='9')
		{
			for(j=(rgm+(ar[2][i+1]-'1')*BAGSMAX)->rm_so;j<(rgm+(ar[2][i+1]-'1')*BAGSMAX)->rm_eo;j++)
			{
				res[k] = ar[3][j];
				k++;
			}
			i++;
		}
		else
		{
			res[k] = ar[2][i];
			k++;
		}
	}
	int ht = strlen(ar[3]);
	for(i=0;i<expr;i++) {if(((rgm+i*BAGSMAX)->rm_so)<ht) {ht=((rgm+i*BAGSMAX)->rm_so);}}
	wholelen += ht;
	res = (char*)realloc(res,wholelen*sizeof(char));
	char* tmp = (char*)calloc(wholelen,sizeof(char));
	for(i=0;i<wholelen;i++) {if(i<ht) tmp[i] = ar[3][i]; else tmp[i] = res[i-ht];}
	for(i=0;i<wholelen;i++) res[i] = tmp[i];
	ht = 0;
	for(i=0;i<expr;i++) {if(((rgm+i*BAGSMAX)->rm_eo)>ht) ht=((rgm+i*BAGSMAX)->rm_eo);}
	wholelen = strlen(res);
	res = (char*)realloc(res,(wholelen+strlen(ar[3])-ht)*sizeof(char));
	for(i=wholelen;i<wholelen+strlen(ar[3])-ht+1;i++) res[i] = ar[3][i-wholelen+ht];
	res[wholelen+strlen(ar[3])-ht+1]='\0';
	printf("%s\n", res);
	//
	for(i=0;i<expr;i++) regfree(rg+i);
	return 0;
}

int main(int argc, char* argv[])
{
	if(argc<4) {printf("!!!too little parametres\n"); return -1;}
	int cnt_s = 0, cnt_e = 0, i = 0;
	for(i=0;argv[1][i]!='\0';i++)
	{
		if(argv[1][i]=='{') {argv[1][i]='('; cnt_s++;}
		else if(argv[1][i]=='}') {argv[1][i]=')'; cnt_s--; cnt_e++;}
		else if(argv[1][i]=='(') {cnt_s++;}
		else if(argv[1][i]==')') {cnt_s--; cnt_e++;}
		if(cnt_s<0) {printf("!!!parentheses error\n"); return -2;}
	}
	if(cnt_e<1) return esub_help1(argv);
	else return esub_helpMany(cnt_e, argv);
	
	return 0;
}
