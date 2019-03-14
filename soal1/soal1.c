#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main(){
	long int i=0;
	int ret;
	char tail[]="_grey.png";
	struct dirent *de;

    DIR *dr = opendir("/home/hp/sisop2/");
    
    while ((de = readdir(dr)) != NULL)
{
	i=strlen(de->d_name);
	char tempat1[100]="/home/hp/sisop2/";
    char tempat2[100]="/home/hp/sisop2/pictures/";
	char temporary[100]="";

	if(de->d_name[i-1]=='g' && 
		de->d_name[i-2]=='n' && 
		de->d_name[i-3]=='p' &&
		de->d_name[i-4]=='.')
		{
	for(i=0;
		i<strlen(de->d_name)-4;
		i++)
		{
		temporary[i]=de->d_name[i];
	}

	strcat(tempat1,de->d_name);
	strcat(temporary,tail);
	strcat(tempat2,temporary);
	rename (tempat1, tempat2);

	}
}
	return 0;
}
