#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int loc;
    int *tape;
    int size;
}machine;





machine movr(machine temp)
{
    int i;
    machine newTemp;
    if (temp.loc == (temp.size - 1)){
        newTemp.size=temp.size+1;
        newTemp.loc=temp.loc+1;
        newTemp.tape=(int*)malloc(sizeof(int) * newTemp.size);
        for(i=0;i<temp.size;i++)
        {
            newTemp.tape[i]=temp.tape[i];
        }
        newTemp.tape[newTemp.size-1] = 0;

    }
    else
    {
        newTemp=temp;
        newTemp.loc=temp.loc+1;
    }
    return newTemp;
}


machine movl(machine temp)
{
    int i;
    machine newTemp;
    if (temp.loc == 0)
    {
        newTemp.size=temp.size+1;
        newTemp.tape=(int*)malloc(sizeof(int) * newTemp.size);
        for (i=0;i<temp.size;i++)
            newTemp.tape[i+1]=temp.tape[i];
        newTemp.tape[0]=0;

    }
    else
    {
        newTemp=temp;
        newTemp.loc=temp.loc-1;
    }
return newTemp;
}

machine inc (machine temp) {
    machine newTemp;
    newTemp=temp;
    if(temp.tape[temp.loc] < 255)
        newTemp.tape[temp.loc]=temp.tape[temp.loc]+1;
    else
        newTemp.tape[temp.loc] = 0;
    return newTemp;
}

machine dec (machine temp) {
    machine newTemp;
    newTemp=temp;
    if(temp.tape[temp.loc] > 0)
        newTemp.tape[temp.loc]=temp.tape[temp.loc]-1;
    else
        newTemp.tape[temp.loc] = 255;
    return newTemp;
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
machine doCommands (char** a, int first, int last, machine temp)
{
    machine newTemp;
    newTemp=temp;
    int i, beginPosition = 0;
    for (i = first; i < last; i++){
        if (!strcmp(a[i], "movr"))
            newTemp=movr(newTemp);
        else if (!strcmp(a[i], "movl"))
            newTemp=movl(newTemp);
        else if (!strcmp(a[i], "inc"))
            newTemp=inc(newTemp);
        else if (!strcmp(a[i], "dec"))
            newTemp=dec(newTemp);
        else if (!strcmp(a[i], "print"))
            printf("\n%d", newTemp.tape[newTemp.loc]);
        else if (!strcmp(a[i], "get")){
                printf("\nInput symbol:");
            newTemp.tape[newTemp.loc] = getchar();
        }
        else if (!strcmp(a[i], "printc"))
            printf("\n%c", newTemp.tape[newTemp.loc]);
        else if (!strcmp(a[i], "begin"))
             beginPosition=i;
        else if (!strcmp(a[i], "end"))
            {
                while (newTemp.tape[newTemp.loc] != 0)
                    newTemp=doCommands(a, beginPosition+1, i,newTemp);
            }
        else
            printf("\nerror %s",a[i]);
    }

return newTemp;
}
int printTape(machine temp)
{
    int i;
    printf("\nTape:");
    for(i = 0; i < temp.size; i++)
        printf("  %d", temp.tape[i]);
    return 0;
}

int main(){
    machine myMachine;
    myMachine.loc=0;
    myMachine.size=1;
    int num = 0, i = 0;
    char s[255];
    char **commands;
    char *fname = NULL;

    FILE *f;
    f = fopen("test.txt", "r");
    while (f == NULL){
        printf("File test.txt not found\n Enter a new filename: ");
        scanf("%s", fname);
        f=fopen(fname, "r");
    }

    commands=(char **) malloc (sizeof(char*));
    while(fgets(s, 255, f)){
        if(s[0] != '*'){

            commands[num]=(char *) malloc (100*sizeof(char));
            commands[num]=delSpace(s);;

            commands = (char**) realloc (commands,(num+2)*sizeof(char*));
            num++;
        }
    }
    fclose(f);

    myMachine.tape = (int*) malloc (sizeof(int));
    myMachine.tape[myMachine.loc]=0;
    myMachine=doCommands(commands, 0, num,myMachine);

    for(i = 0; i < num; i++)
        free(commands[num]);
    free(commands);
    printTape(myMachine);
    return 0;
}
