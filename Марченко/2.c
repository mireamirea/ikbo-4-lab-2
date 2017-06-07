#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int loc = 0;
int *tape;
int sizeOfLenta = 1;




int movr(void){
    if (loc == (sizeOfLenta - 1)){
        int* temp;
        sizeOfLenta++;
        loc++;
        temp = (int*) realloc (tape, sizeof(int) * sizeOfLenta);
        if(temp != NULL){
            temp[sizeOfLenta-1] = 0;
            tape = temp;
        }
        else
            return 1;
    }
    else loc++;
return 0;
}

int movl(void){
    if (loc == 0){
        int i;
        int* temp;
        sizeOfLenta++;
        temp = (int*) realloc (tape, sizeof(int) * sizeOfLenta);
        if(temp != NULL){
            for (i = sizeOfLenta - 1; i != 0; i--)
                temp[i]=temp[i-1];
            temp[0] = 0;
            tape = temp;
        }
        else
            return 1;
    }
    else loc--;
return 0;
}

int inc (void) {
    if(tape[loc] < 255)
        tape[loc]++;
    else
        tape[loc] = 0;
return 0;
}

int dec (void) {
    if(tape[loc] > 0)
        tape[loc]--;
    else
        tape[loc] = 255;
return 0;
}

int doCommands (char** a, int first, int last){
    int i, tmp = 0;
    for (i = first; i < last; i++){
        if (strcmp(a[i], "movr") == 0)
            movr();
        else if (strcmp(a[i], "movl") == 0)
            movl();
        else if (strcmp(a[i], "inc") == 0)
            inc();
        else if (strcmp(a[i], "dec") == 0)
            dec();
        else if (strcmp(a[i], "print") == 0)
            printf("\n%d", tape[loc]);
        else if (strcmp(a[i], "get") == 0){
                printf("\nEnter symbol:");
            tape[loc] = getchar();
        }
        else if (strcmp(a[i], "printc") == 0)
            printf("\n%c", tape[loc]);
        else if (strcmp(a[i], "begin") == 0)
             tmp=i+1;
        else if (strcmp(a[i], "end") == 0)
            {
                while (tape[loc] != 0)
                    doCommands(a, tmp, i);
            }
        else
            printf("\nerror %s",a[i]);
    }

return 0;
}

char* delSpace (char* s){
    char* a;
    int i, j;
    a = (char*) malloc (sizeof(char)*200);
    for(i = j = 0; s[i] != '\0'; i++)
        if(isalnum(s[i]))
            a[j++] = s[i];
    a[j] = '\0';
    return a;
}

int main(){
    int num = 0, i = 0;
    char s[255];
    char **commands;
    char *fname = NULL;

    FILE *f;
    f = fopen("test.txt", "r");
    while (f == NULL){
        printf(" Error opening file\n Enter a new filename");
        scanf("%s", fname);
        f=fopen(fname, "r");
    }

    commands=(char **) malloc (sizeof(char*));
    while(fgets(s, 255, f)){

        if(s[0] != '*'){
            commands[num]=(char *) malloc (100*sizeof(char));
            commands[num] = delSpace(s);


            commands = (char**) realloc (commands,(num+2)*sizeof(char*));
            num++;
        }
    }
    fclose(f);

    tape = (int*) malloc (sizeof(int));
    tape[loc]=0;
    doCommands(commands, 0, num);

    for(i = 0; i < num; i++)
        free(commands[num]);
    free(commands);
    printf("\nLenta : ");
    for(i = 0; i < sizeOfLenta; i++)
        printf("  %d", tape[i]);
    return 0;
}
