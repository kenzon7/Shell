
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


char *array[22];
char raw[] = "/bin/ls -i -s < file.txt";
char *cmd, *file, *tok;
int loops = 0, mode = 0;
FILE *fp;
int pipedes[2];


//input function 

void inptloop(char **a) {
	int loops = 0;
	char ch[500];		
	char *tok;
	fgets(ch, 500, stdin);
	ch[strcspn(ch, "\n")] = 0;
	tok = strtok(ch," ");
	while ( tok != NULL) {
		a[loops++] = tok;
		tok = strtok(NULL," ");
	}

	a[loops++] = NULL;
}

char s[500];

int main() {

	while (1) {

		if (strstr(raw, ">>") != NULL) { mode = 3; printf(">>\n");}
		else if (strstr(raw, ">") != NULL) { printf(">\n"); mode = 2;}
		else if (strstr(raw, "<") != NULL){ mode = 1;  printf("<\n");}
		else mode = 0;	

		cmd = strtok(raw, ">><");
		file = strtok(NULL, ">><");
		cmd[strcspn(cmd, "\n")] = 0;
		// printf("%s:%s\n", cmd, file);

		switch (mode) {
			case 3:fp = fopen(file, "a"); break;
			case 2:fp = fopen(file, "w"); break;
			case 1:fp = fopen(file, "r"); fgets( raw, 1000, fp ); break;
			default: fp = NULL;
		}

		printf("%s",raw);
		tok = strtok(cmd," ");
		while ( tok != NULL) {
			array[loops++] = tok;
			tok = strtok(NULL," ");
		}



		//Input loop

		// inptloop(array);	

		//Exit check

		int ex = strcmp(array[0],"exit");
		if (ex == 0)  break;	
		
		//Exec & fork 

		if (pipe(pipedes) == -1) { perror("pipe"); exit(EXIT_FAILURE);}
		
		pid_t frk = fork();

		if (frk == 0) {
			if (mode > 1) {
				dup2 (pipedes[1], STDOUT_FILENO);
    			close(pipedes[0]);
    			close(pipedes[1]); 
			}
			execvp(array[0], array); 
			exit(0);
		}

		if( mode > 1) {
			close(pipedes[1]);
			read(pipedes[0], s, sizeof(s));
			fputs(s,fp);
			fclose(fp);
		}

		wait(NULL);	
		break;
	}
	return 0;
}