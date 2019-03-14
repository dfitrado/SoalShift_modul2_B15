#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {

    struct stat info;
    stat("/home/wildangbudhi/Documents/SoalShift_modul2_B15/NO2/hatiku/elen.ku", &info);  // Error check omitted
    struct passwd *pw = getpwuid(info.st_uid);
    struct group  *gr = getgrgid(info.st_gid);

    if(!strcmp(pw->pw_name, "www-data") && !strcmp(gr->gr_name, "www-data")){
      chmod("/home/wildangbudhi/Documents/SoalShift_modul2_B15/NO2/hatiku/elen.ku",(__mode_t) atoi("0777"));
      remove("/home/wildangbudhi/Documents/SoalShift_modul2_B15/NO2/hatiku/elen.ku");
    }

    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}