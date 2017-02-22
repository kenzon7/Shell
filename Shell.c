
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


char *array[22];

//input function 

void inptloop(char *a[22]) {
	int loops = 0;
	char ch[500];
	char *tok;
	fgets(ch, 500, stdin);
	tok = strtok(ch," ");
	while ( tok != NULL) {
		a[loops++] = tok;
		tok = strtok(NULL," ");
	}
	printf("Input done");
}

int main() {

	// while (1) {

		pid_t frk = fork();

		// inptloop(array);

		printf("My PID:%d", getpid());

		// int ex = strcmp(array[0],"exit\n");
		// if (ex == 0)  break;

		// array[0] = "/bin/ls";

		if (frk == 0) { 

			printf("Child PID:%d \n", getpid());
			sleep(5);
			// execvp(array[0], array);
			exit(0);
		}

		wait(NULL);		

		// }
	return 0;
}