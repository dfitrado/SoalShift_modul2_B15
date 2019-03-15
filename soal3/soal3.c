#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t child_id1, child_id2, child_id3;
	int pipeEnds1[2], pipeEnds2[2];

	pipe(pipeEnds1);
	pipe(pipeEnds2);

	// Process1
	child_id1 = fork();
	
	if (child_id1 < 0) exit(EXIT_FAILURE);

	if (child_id1 == 0) {
		char *zip[] = {"unzip", "/home/wildangbudhi/Documents/SoalShift_modul2_B15/NO3/campur2.zip", NULL};
		execvp(zip[0], zip);
	} else {
		while(wait(NULL) > 0); //wait until Process1 end
		
		// Process2
		child_id2 = fork();

		if (child_id2 < 0) exit(EXIT_FAILURE);

		if(child_id2 == 0){
			dup2(pipeEnds1[1], STDOUT_FILENO); // connect pipeEnds1 Write to STDOUT Process2
			close(pipeEnds1[1]); // close pipeEnds1 Write that connected to File Table 4
			close(pipeEnds1[0]); // close pipeEnds1 Read that connected to File Table 3

			char *ls[] = {"ls", "/home/wildangbudhi/Documents/SoalShift_modul2_B15/NO3/campur2", NULL};
			execvp(ls[0], ls);
		}		
		else{
			while(wait(NULL) > 0); //wait until Process2 end

			// Process3
			child_id3 = fork();

			if (child_id3 < 0) exit(EXIT_FAILURE);

			if(child_id3 == 0){
				dup2(pipeEnds1[0], STDIN_FILENO); // connect pipeEnds1 Read to STDIN Process3
				dup2(pipeEnds2[1], STDOUT_FILENO); // connect pipeEnds2 Write to STDOUT Process3
				close(pipeEnds2[0]); 
				close(pipeEnds2[1]);
				close(pipeEnds1[0]);
				close(pipeEnds1[1]);

				char *grep[] = {"grep", ".txt$", NULL};
				execvp(grep[0], grep);
			}
			else{

				char hasil[1000];
				close(pipeEnds2[1]);
				close(pipeEnds1[0]);
				close(pipeEnds1[1]);
				read(pipeEnds2[0], hasil, sizeof(hasil));

				FILE *f1 = fopen("/home/wildangbudhi/Documents/SoalShift_modul2_B15/NO3/daftar.txt", "w");
				fputs(hasil, f1);
				fclose(f1);
			}

		}

	}

	return 0;
}