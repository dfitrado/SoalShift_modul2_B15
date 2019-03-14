#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <dirent.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/hp/sisop2/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
long int i=0;
  while(1) 
{
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


    sleep(10);
  }

  exit(EXIT_SUCCESS);
}
