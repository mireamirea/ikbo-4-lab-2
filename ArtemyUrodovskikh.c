#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000
#define T 256
unsigned char *tape, *lpos, *rpos;
int i, c, tp, beginin, t = T;
typedef char* position;

int get(position); /* возвращает байт данных */

int main(int argc, char const *argv[])
{
	FILE *fp;
	fp = fopen("input.txt", "r");		
	char *commands[N], value;

	for (i = 0; i < N; i++)
		commands[i] = (char*) malloc (sizeof(char) * N); 
	/* лента */
	tape = (char*) malloc(sizeof(char) * t);
	for (i = 0; i < T; i++)
		tape[i] = 0;

/*	lpos = tape;
	rpos = tape + sizeof(char) * T;
*/
	/* запись команд */
	i = 0;
	while(fscanf(fp, "%s", commands[i]) == 1)
		i++;

	for (i = 0; i < T; i++)
		printf("%d ", tape[i]);

	c = i, i = 0;
	while (i < c) {
		if (strstr("movl", commands[i]))
			tp--;
		else if (strstr("movr", commands[i]))
			tp++;
		else if (strstr("inc", commands[i])) {
			if (tape[tp] == 255) {
				printf("warning overflow\n");
				tape[tp] = 0;
			} else 
				++(tape[tp]);
		} else if (strstr("dec", commands[i]))
			--(tape[tp]);
		else if (strstr("print", commands[i]))
			printf("%d", tape[tp]);
		else if (strstr("printc", commands[i]))
			printf("%c", tape[tp]);
		else if (strstr("get", commands[i]))
			scanf("%c", tape[tp]);
		else if (strstr("begin", commands[i]))
			if (tape[tp] == 0)
				while (!strstr("end", commands[i]))
					i++;
			else
				beginin = i;
		else if (strstr("end", commands[i]) && tape[tp] != 0)
			i = beginin;

		if (tp >= T) {
			t += T;
			tape = realloc(tape, sizeof(char) * t);
			printf("tape size increased\ncurrent state:\n");
			for (i = 0; i < t; i++)
				printf("%5d %d ", i, tape[i]);
		} else if (tp < 0) {
			t += T;
			tape = realloc(tape, sizeof(char) * t);
			memcpy(tape, tape+T, sizeof(char) * T);
			printf("tape size increased\ncurrent state:\n");
			for (i = 0; i < t; i++)
				printf("%d ", tape[i]);
			tp+=T;
		}


		i++;

	}

	fclose(fp);
	return 0;
}