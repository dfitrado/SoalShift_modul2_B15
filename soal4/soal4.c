#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>

void crDaemon();

int main(){
  pid_t child;
  int status;
  char dir[55];
  char *uname;
  uname = getlogin();
  sprintf(dir, "/home/hp/Documents/makanan", uname);

  char file[100];
  sprintf(file, "hp/makan_enak.txt", dir);
  int ct = 1;
  crDaemon();

  while(1){
    sleep(5);
    struct stat filestat;
    stat(file, &filestat);

    time_t fileAccessed = filestat.st_atime;

    if(difftime(time(NULL), fileAccessed) <= 30){
      char newfile[100];
      sprintf(newfile, "hp/makan_sehat%d.txt", dir, ct);

      child = fork();
      if(child == 0){
        char *argv[] = {"cp", file, newfile, NULL};
        execv("/bin/cp", argv);
      } while ((wait(&status)) > 0); 
	  kill(child, SIGKILL);
      ct++;
    }
  }

  exit(EXIT_SUCCESS);
}

void crDaemon(){
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

  if ((chdir("/")) < 0){
    exit(EXIT_FAIL);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
}
