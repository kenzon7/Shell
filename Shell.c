
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


char *array[22];
char cmd[] = "/bin/ls -i -s > file.txt";
char *pot1, *pot2;

char *c[] = {"/bin/ls","-i","-s"};

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

	// while (1) {

		// for(int i = 0; i < 500; i++) printf("%s", &cmd[i]);

		// pot1=strchr(cmd,">> ");
		pot1 = strstr(cmd, ">>");
		if (pot1 != NULL) printf("YO");
  		// while (pot1!=NULL) {
		// 	  pot1=strchr(pot1+1,'>');
  		// }

		//Input loop

		// inptloop(array);	

		//Exit check

		// int ex = strcmp(array[0],"exit");
		// if (ex == 0)  break;	
		
		//Exec & fork 
		
		pid_t frk = fork();

		if (frk == 0) { 
			// execvp(c[0], c); 
			exit(0);
		}

		wait(NULL);	
		// printf("%s",array[1]);
		// for(int i = 0; i <22; i++) {  array[i] = 0; }

		// }
	return 0;
}