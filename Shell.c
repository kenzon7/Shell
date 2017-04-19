
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>


char *array[22];
char raw[] = "ls < file.txt";



//input function 

int inptloop(char **a) {
	int loops = 0;
	char ch[10000];		
	char *tok;

	fgets(ch, 500, stdin);
	ch[strcspn(ch, "\n")] = '\0';
	tok = strtok(ch," ");
	while ( tok != NULL) {
		a[loops++] = tok;
		tok = strtok(NULL," ");
	}

	a[++loops] = NULL;
	return loops-1;
}

int main() {

	while (1) {

		for (int i=0; i < 22; i++) array[i] = '\0';

		char *cmd, *file1, *file2, *tok;
		int loops = 0; 
		int mode1 = 0, mode2=0;
		int fp1, fp2;

		//Input loop

		loops = inptloop(array);

		// check for symbols

		for ( int i=0; i < loops; i++ ) {
			if (array[i] != NULL) {
				if (strcmp(array[i],">>") == 0) {
					if (mode1) {
						mode2 = 3;
						file2 = array[i+1];
						array[i] = NULL;
						array[i+1] = NULL;
					}
					else {
						mode1 = 3;
						file1 = array[i+1];
						array[i] = NULL; 						
						array[i+1] = NULL;
					}
				}
				else if (strcmp(array[i],">") == 0) {
					if (mode1) {
						mode2 = 2;
						file2 = array[i+1];
						array[i] = NULL; 						
						array[i+1] = NULL;
					}
					else {
						mode1 = 2;
						file1 = array[i+1];
						array[i] = NULL; 						
						array[i+1] = NULL;
					}
				}
				else if (strcmp(array[i],"<") == 0) {	
					if (mode1) {
						mode2 = 1;
						file2 = array[i+1];
						array[i] = NULL; 						
						array[i+1] = NULL;
					}
					else {
						mode1 = 1;
						file1 = array[i+1];
						array[i] = NULL; 						
						array[i+1] = NULL;
					}
				}
			}
		}

		printf("%d:%d:%d\n", loops, mode1, mode2);
		// for (int i=0; i < loops; i++) if (array[i] != NULL) printf("%s\n",array[i]); else printf("NULL");	
		

		// //Exit check

		if (strcmp(array[0],"exit") == 0)  break;	
		
		//Exec & fork 
		
		pid_t frk = fork();

		if (frk == 0) {
			switch (mode1) {
				case 3:
					fp1 = open(file1, O_RDWR|O_APPEND|O_CREAT,S_IRWXU);  
					dup2(fp1, 1);
					break;
				case 2:
					fp1 = open(file1, O_RDWR|O_CREAT,S_IRWXU); 
					dup2(fp1, 1);
					break;
				case 1:
					printf("Reading From file..");
					freopen(file1, "r", stdin); 
					break;
			}
			execvp(array[0], array); 			
			exit(0);
		}

		wait(NULL);	
	}
	return 0;
}