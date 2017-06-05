#include <stdio.h>
#include <stdlib.h>

#include <string.h>


#define Command 228
#define String 256



int main(int argc, char *argv[])
{
	char *List[Command];
	int i, loc = 0, inbrackets, counter = 0, g = 0;;
	int z = String;
	char *tape;
	FILE *f;


	f = fopen("data.txt", "r");
	for (i = 0; i < Command; i++)
		List[i] = (char*)malloc(sizeof(char) *String);
	tape = (char*)malloc(sizeof(char) *z);
	for (i = 0; i < String; i++)
		tape[i] = 0;
	/*Выделим память под команды и заполним ленту нулями*/
	i = 0;

	while (fscanf(f, "%s", List[i]) == 1)
		i++;
	counter = i;
	for (i = 0; i < counter; i++)
		printf("%s\n", List[i]);
	/*Считаем командочки и выведем их*/

	i = 0;
	while (g < counter) {
		if (loc >= String) {
			z += String;
			tape = realloc(tape, sizeof(char) * z);
			printf("tape reallocated \n");
		}
		else if (loc < 0) {
			z += String;
			tape = realloc(tape, sizeof(char) *z);
			memcpy(tape, tape + String, String);
			printf("tape reallocated \n");
			loc += String;
		}
		/*Если лента вылезает за границы*/
		if (strstr("movr", List[g]))loc++;
		else if (strstr("movl", List[g]))loc--;
		else if (strstr("inc", List[g])) {
			if (tape[loc] == 255) { printf("Overflow\n"); tape[loc] = 0; }
			else tape[loc] = tape[loc] + 1;
		}
		else if (strstr("dec", List[g])) {
			if (tape[loc] == 0)tape[loc] = 0; else tape[loc] = tape[loc] - 1;
		}
		else if (strstr("print", List[g]))printf("%d\n", tape[loc]);
		else if (strstr("get", List[g]))scanf("%d", &tape[loc]);
		else if (strstr("begin", List[g])) {
			if (tape[loc] == 0) {
				while (!strstr("end", List[g]))g++;
			}
			else inbrackets = g;
		}
		else if (strstr("end", List[g])) {
			if (tape[loc] != 0)g = inbrackets;
		}

		g++;


	}
	fclose(f);
	return 0;
}
