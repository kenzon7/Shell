
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void inptloop() {
	int state = 1;
	int loops = 0;
	char ch[500];
	char array[21][500];

	while (state == 1) {
		scanf("%s", ch);
		int exit = strcmp(ch,"exit");
		if (exit == 0) break;
		if (loops < 21) {
			strcpy(array[loops],ch);
			loops ++;
		}
	}
	for(int i = 0; i < loops; i++) { printf("%s ",array[i]); printf("%d \n",i); }	//for testing 
}

int main() {
	
	//input loop

	inptloop();

	//Child-parent process

	pid_t frk = fork();

	if (frk == 0) { 
		printf("Child");
		execl("/bin/echo","echo","Excuted echo",NULL);
		} 

	else if (frk > 0) {
		printf("Parent ");
		wait(NULL);

		}
	return 0;
}