#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>

int main(){
  pid_t pid, sid;

  pid = fork();

  if (pid < 0){
    exit(EXIT_FAILURE);
    
  }

  if (pid > 0){
    exit(EXIT_SUCCESS);
    
  }

  umask(0);

  sid = setsid();

  if (sid < 0){
    exit(EXIT_FAILURE);
    
  }

  if ((chdir("/home/hp/sisop2/soal5/")) < 0){
    exit(EXIT_FAILURE);
    
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1){
   time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   
   char nama[50];
   char directory[50] = "/home/hp/log/";
   char *fileName = "log";
   char *extension = ".log";
   
   mkdir(directory, 0777);
   sprintf(nama, "%d:%d:%d-%d:%d/", tm.tm_mday, tm.tm_mon +1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
   printf("%s\n", nama);
   strcat(directory, nama);
   mkdir(directory, 00777);

   int k = 1, count;

   FILE *log, *syslog;
   char directoryName[100], ch;
   while(k<31){
     sprintf(directoryName, "%s%s%d%s", k, directory, fileName, extension);
     log = fopen(directoryName, "w");
     syslog = fopen("/var/log/syslog", "r");
     fseek(syslog, 0L, SEEK_END);
     count = ftell(syslog);
     fseek(syslog, 0L, SEEK_SET);
     
     while(count--){
       ch = fgetc(syslog);
       fputc(ch, log);
       
     }
     sleep(60);
     k++;
     fclose(log);
     fclose(syslog);
     
    }
  }
  exit(EXIT_SUCCESS);
  
}
