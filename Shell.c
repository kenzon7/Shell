
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>



int main() {
	int state = 1;
	int loops = 0;
	char ch[500];
	char array[21][500];

	//input loop

	while (state == 1) {
		scanf("%s", ch);
		strcpy(array[loops],ch);
		int exit = strcmp(ch,"exit");
		if (exit == 0) state = 0;
		loops ++;
	}

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
	

	for(int i = 0; i < loops; i++) { printf("%s ",array[i]); }
	return 0;
}