#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1){
    DIR *gambar;
    struct dirent *entry;
    gambar = opendir(".");
    if (gambar != NULL){
        while(entry = readdir(gambar)){
            int len = strlen(entry->d_name);
            char *s = &entry->d_name[len - 4];
            char *namafile;
            if (strcmp(s, ".png") == 0){
                memcpy(namafile, entry->d_name, strlen(entry->d_name) - 4);
                char *grey = malloc(strlen("_grey") + strlen(entry->d_name) + 1 + strlen("/home/hp/modul2/gambar/"));
                strcpy(grey, "/home/hp/modul2/gambar/");
                strcat(grey, namafile);
                strcat(grey, "_grey.png");
                rename(entry->d_name, grey);
            }
        }
    }
    (void) closedir (gambar);
  }
  exit(EXIT_SUCCESS);
}
