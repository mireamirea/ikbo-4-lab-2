#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int dei(char st[255]);

int main(int argc, char **argv) {

	FILE *fp;
	char name[255];
	int x, i = 0, size=256, sizenew, g, j, temp=0, iter=0;
	char *a = NULL, tempa, tempb;

	char *lent;

	lent = (char*)calloc(size , sizeof(char));

	fp = fopen("instruction.txt", "r");
	if (fp==NULL) return 1;

	while (fgets(name, sizeof(name), fp)) {

		
/*		system("cls");*/
		for (g = 0; g < i + 5; g++) printf("%c", lent[g]);
		printf("\n");
		for (g = 0; g < i; g++) printf(" ");
		printf("^\n");


		x = dei(name);


		switch (x) {
/*------------------------------------------------------------------------------------------------*/
		case 0:
			if (i == 0) {
				printf("Left border reached\nExpansion is not possible\n");
/*				_sleep(3000);*/
			}
			else
				i--;
			break;
/*------------------------------------------------------------------------------------------------*/
		case 1:
			if (i == size - 1) {
				sizenew += size;
				a = (char*)realloc(lent, sizenew * sizeof(char));
				if (a == NULL) {
					printf("Unable to expand the ribbon\n");
					sizenew -= size;
/*					_sleep(3000);*/
					break;
				}
				else {
					lent = a;
					for (g = sizenew - size; g < sizenew; g++) lent[g] = 0;
				}
			}
			i++;
			break;
/*------------------------------------------------------------------------------------------------*/
		case 2:
			if (lent[i] == 255) {
				printf("Overflow\nCell is reset to zero\n");
				lent[i] = 0;
/*				_sleep(3000);*/
			}
			else {
				lent[i]++;
/*				_sleep(100);*/
			}
			break;
/*------------------------------------------------------------------------------------------------*/
		case 3:
			if (lent[i] == 0) {
				printf("The cell has a minimum value\n");
/*				_sleep(3000);*/
			}
			else {
				lent[i]--;
/*				_sleep(100);*/
			}
			break;
/*------------------------------------------------------------------------------------------------*/
		case 4:
			printf("The value in the current cell: %d\n", (int)lent[i]);
/*			_sleep(3000);*/
			break;
/*------------------------------------------------------------------------------------------------*/
		case 5:
			printf("Enter the current cell symbol\n");
			scanf("%c", &tempa);
			if((int)tempa!=10) scanf("%c", &tempb);
			while ((int)tempa < 0 || (int)tempa>255) {
				printf("Invalid character\nTry another character\n");
				scanf("%c", &tempa);
				if ((int)tempa != 10) scanf("%c", &tempb);
			}
			lent[i] = tempa;
			break;
/*------------------------------------------------------------------------------------------------*/
		case 6:
			printf("The character in the current cell: %c\n", lent[i]);
/*			_sleep(3000);*/
			break;
/*------------------------------------------------------------------------------------------------*/
		case 7:
			temp = 1;
			iter = ftell(fp);
		if (lent[i]==0){
			while (j != 8) {
				fgets(name, sizeof(name), fp);
				iter++;
				j = dei(name);
				if (j == 0) {
					printf("The instruction does not include the command \"end\"\n");
					fseek(fp, iter, SEEK_SET);				
/*					_sleep(3000);*/
				}
			}
		}
			break;
/*------------------------------------------------------------------------------------------------*/
		case 8:
			if (temp == 1) {
				if (lent[i] != 0) {
					fseek(fp, iter, SEEK_SET);
				}
			}
			else {
				printf("In the instruction there is no command \"begin\"\n");
/*				_sleep(3000);*/
			}
			break;
/*------------------------------------------------------------------------------------------------*/
		case 9:
			printf("Commentary:\n");
			while (name[0] == ' ' || name[0] == '\t') {
				for (j = 1; j < 255; j++) name[j - 1] = name[j];
			}
			printf("%s\n", name);
/*			_sleep(3000);*/
			break;
		}
		printf("--------------------------------------------\n");

	}

	fclose(fp);
	getchar();
	return 0;
}

int dei(char st[255]) {
	char s0[] ="movl";
	char s1[] ="movr";
	char s2[] ="inc";
	char s3[] ="dec";
	char s4[] ="print";
	char s5[] ="get";
	char s6[] ="printc";
	char s7[] = "begin";
	char s8[] = "end";
	char s9[] = "*";
	

	if (strstr(st, s0) != NULL) { return 0; };
	if (strstr(st, s1) != NULL) { return 1; };
	if (strstr(st, s2) != NULL) { return 2; };
	if (strstr(st, s3) != NULL) { return 3; };
	if (strstr(st, s6) != NULL) { return 6; };
	if (strstr(st, s5) != NULL) { return 5; };
	if (strstr(st, s4) != NULL) { return 4; };
	if (strstr(st, s7) != NULL) { return 7; };
	if (strstr(st, s8) != NULL) { return 8; };
	if (strstr(st, s9) != NULL) { return 9; };
	return EOF;
}
/*printf("GG\n");*/
