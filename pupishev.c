#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define K 255
#define S 100
#define F 50

int l = 0;
int s = 1;
int *tape;


int movl(){
    if (l == 0){
        int i;
        int* temp;
        s++;
        temp = (int*)realloc(tape,s * sizeof(int));
        if(temp != NULL){
            for (i = s - 1; i != 0; i--)
                temp[i]=temp[i-1];
            temp[0] = 0;
            tape = temp;
        }
        else
            return 1;
    }
    else l--;
    return 0;
}

int movr(){
    if (l == (s - 1)){
        s++;
        l++;
        int* temp;
        temp = (int*) realloc (tape, sizeof(int) * s);
        if(temp != NULL){
            temp[s-1] = 0;
            tape = temp;
        }
        else
            return 1;
    }
    else l++;
    return 0;
}

int inc () {
    if(tape[l] < K)
        tape[l]++;
    else
        tape[l] = 0;
    return 0;
}

int dec () {
    if(tape[l] > 0)
        tape[l]--;
    else
        tape[l] = K;
    return 0;
}

int commands(char **a, int left, int right) {
    int i, temp = 0;
    for (i=left; i<right; i++) {
        if (strcmp(a[i], "inc")==0) inc();
        else if (strcmp(a[i], "dec")==0) dec();
        else if (strcmp(a[i], "movr")==0) movr();
        else if (strcmp(a[i], "movl")==0) movl();
        else if (strcmp(a[i], "get")==0){
            printf("\nEnter symbol:\n");
            scanf ("%i", &tape[l]);
        }
        else if (strcmp(a[i], "print")==0) printf("\n%d", tape[l]);
        else if (strcmp(a[i], "printc")==0) printf("\n%c", tape[l]);
        else if (strcmp(a[i], "begin")==0) temp=i+1;
        else if (strcmp(a[i], "end")==0) {
            while (tape[l]!=0) commands(a, temp, i);
        }
    }
    
    return 0;
}

char* space (char* str){
    int i, j;
    char* a;
    a = (char*) malloc (S*sizeof(char));
    for(i = j = 0; str[i] != '\0'; i++)
        if(isalnum(str[i]))
            a[j++] = str[i];
    a[j] = '\0';
    return a;
}

int main(void){
    int N = 0, i = 0;
    char **a, str[K];
    FILE *file = NULL;
    char *filename=(char *)malloc(F);
    printf ("Enter file name\n");
    scanf("%s",filename);
    file=fopen(filename,"r");
    while (file == NULL) {
        printf("File not found. Try again.\n");
        scanf("%s",filename);
        file=fopen(filename,"r");
    }
    a=(char**)malloc((N+1)*sizeof(char*));
    while(fgets(str, K, file)) {
        if(str[0] != '*'){
            a[N] = space(str);
            N++;
            a = (char**)realloc(a,(N+1)*sizeof(char*));
        }
    }
    
    tape = (int*) malloc (sizeof(int));
    tape[l]=0;
    commands(a, 0, N);
    fclose(file);
    free(a);
    printf("\n Tape : ");
    for(i = 0; i < s; i++)
        printf(" %d", tape[i]);
    printf("\n");
    return 0;
}

