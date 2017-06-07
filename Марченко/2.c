#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int *lenta;
int size = 1;
int loc = 0;

int movl(void){
    if (loc == 0){
        int i;
        int* tmp;
        size++;
        tmp = (int*) realloc (lenta, sizeof(int) * size);
        if(tmp != NULL){
            for (i = size - 1; i != 0; i--)
                tmp[i]=tmp[i-1];
            tmp[0] = 0;
            lenta = tmp;
        }
        else
            return 1;
    }
    else loc--;
return 0;
}

int movr(void){
    if (loc == (size - 1)){
        int* tmp;
        size++;
        loc++;
        tmp = (int*) realloc (lenta, sizeof(int) * size);
        if(tmp != NULL){
            tmp[size-1] = 0;
            lenta = tmp;
        }
        else
            return 1;
    }
    else loc++;
return 0;
}

int inc (void) {
    if(lenta[loc] < 255)
        lenta[loc]++;
    else
        lenta[loc] = 0;
return 0;
}

int dec (void) {
    if(lenta[loc] > 0)
        lenta[loc]--;
    else
        lenta[loc] = 255;
return 0;
}

int commands (char** a, int first, int last){
    int i, tmp = 0;
    for (i = first; i < last; i++){
        if (strcmp(a[i], "movl") == 0)
            movl();
        else if (strcmp(a[i], "movr") == 0)
            movr();
        else if (strcmp(a[i], "inc") == 0)
            inc();
        else if (strcmp(a[i], "dec") == 0)
            dec();
        else if (strcmp(a[i], "print") == 0)
            printf("\n%d", lenta[loc]);
        else if (strcmp(a[i], "get") == 0){
                printf("\nEnter symbol:");
            lenta[loc] = getchar();
        }
        else if (strcmp(a[i], "printc") == 0)
            printf("\n%c", lenta[loc]);
        else if (strcmp(a[i], "begin") == 0)
             tmp=i+1;
        else if (strcmp(a[i], "end") == 0)
            {
                while (lenta[loc] != 0)
                    commands(a, tmp, i);
            }
        else
            printf("\nerror %s",a[i]);
    }

return 0;
}

char* delprobel (char* s){
    char* a;
    int i, j;
    a = (char*) malloc (sizeof(char)*5);
    for(i = j = 0; s[i] != '\0'; i++)
        if(isalnum(s[i]))
            a[j++] = s[i];
    a[j] = '\0';
    return a;
}

int main(){
    char s[255];
    char **a;
    int num = 0, i = 0;;
    char *fname = NULL;

    FILE * file;
    file = fopen("test.txt", "r");
    while (file == NULL){
        printf(" Error opening file\n Enter a new filename");
        scanf("%s", fname);
        file=fopen(fname, "r");
    }

    a=(char **) malloc ((num+1)*sizeof(char *));
    while(fgets(s, 255, file)){

        if(s[0] != '*'){
            a[num] = delprobel(s);
            //a[num] = s;
            num++;
            a = (char**) realloc (a,(num+1)*sizeof(char*));
        }
    }
    fclose(file);

    lenta = (int*) malloc (sizeof(int));
    lenta[loc]=0;
    commands(a, 0, num);

    for(i = 0; i < num; i++)
        free(a[num]);
    free(a);
    printf("\n Tape : ");
    for(i = 0; i < size; i++)
        printf("  %d", lenta[i]);
    return 0;
}
