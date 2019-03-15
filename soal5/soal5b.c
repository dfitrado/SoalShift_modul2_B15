#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(){
    char out[7]={0};
    FILE *cmd = popen("pidof /home/hp/Documents/sisop2/soal5/soal5a", "r");
    fgets(out, 7, cmd);
    pid_t pid = strtoul(out, NULL, 10);
    pclose(cmd);

    if(!kill(pid, SIGKILL))
        printf("Process with pid of %d is successfully killed\n", pid);

    return 0;
}
