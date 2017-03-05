
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


char *array[22];

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

int main() {

	while (1) {

		//Input loop

		inptloop(array);	

		//Exit check

		int ex = strcmp(array[0],"exit");
		if (ex == 0)  break;	
		
		//Exec & fork 
		
		pid_t frk = fork();

		if (frk == 0) { 
			execvp(array[0], array); 
			exit(0);
		}

		wait(NULL);		

		}
	return 0;
}