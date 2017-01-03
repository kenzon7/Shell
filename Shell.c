
#include <stdio.h>
#include <string.h>

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

	for(int i = 0; i < loops; i++) { printf("%s",array[i]); }
	return 0;
}