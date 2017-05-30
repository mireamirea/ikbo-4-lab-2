//
//  main.c
//  1.lab
//
//  Created by Георгий Фалилеев on 14.05.17.
//  Copyright © 2017 Георгий Фалилеев. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int movl();
int movr();
int inc();
int dec();
int command(char** com, int first, int last);
char* delprobel (char* st);

int *lenta;
int size = 1;
int local = 0;

int main(int argc, char *argv[]){
    char **com;
    char st[255];
    int num = 0, i = 0;;
    FILE *f1;
    char *fname=(char *)malloc(20);
    if (argc>=2) {
        
        f1=fopen(argv[1],"rb");
        printf("Файл успешно открыт!\n");
    }
    
    while (f1 == NULL) {
        printf("Ошибка!\nВведите имя файла: ");
        scanf("%s",fname);
        f1=fopen(fname,"rb");
    }
    
    printf("Файл успешно открыт!\n");
    com = (char **)malloc((num+1)*sizeof(char *));
    while(fgets(st, 255, f1)) {
        
        if(st[0] != '*'){
            com[num] = delprobel(st);
            num++;
            com = (char**)realloc(com,(num+1)*sizeof(char*));
        }
    }
    
    lenta = (int*) malloc (sizeof(int));
    lenta[local]=0;
    command(com, 0, num);
    
    fclose(f1);
    free(com);
    
    printf("\nЛента : ");
    
    for(i = 0; i < size; i++)
        printf(" %d", lenta[i]);
    printf("\n");
    return 0;
}

int movl(){
    if (local == 0){
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
    else local--;
    return 0;
}

int movr(){
    if (local == (size - 1)){
        int* tmp;
        size++;
        local++;
        tmp = (int*) realloc (lenta, sizeof(int) * size);
        if(tmp != NULL){
            tmp[size-1] = 0;
            lenta = tmp;
        }
        else
            return 1;
    }
    else local++;
    return 0;
}

int inc () {
    if(lenta[local] < 255)
        lenta[local]++;
    else
        lenta[local] = 0;
    return 0;
}

int dec () {
    if(lenta[local] > 0)
        lenta[local]--;
    else
        lenta[local] = 255;
    return 0;
}

int command (char** com, int first, int last){
    int i, tmp = 0;
    for (i = first; i < last; i++){
        if (strcmp(com[i], "movl") == 0)
            movl();
        else if (strcmp(com[i], "movr") == 0)
            movr();
        else if (strcmp(com[i], "inc") == 0)
            inc();
        else if (strcmp(com[i], "dec") == 0)
            dec();
        else if (strcmp(com[i], "print") == 0)
            printf("\nЗначение по текущему адресу: %d", lenta[local]);
        else if (strcmp(com[i], "get") == 0){
            printf("\nВведите символ:  ");
            lenta[local] = getchar();
        }
        else if (strcmp(com[i], "printc") == 0)
            printf("\nЗначение текущей ячейки символом: %c", lenta[local]);
        else if (strcmp(com[i], "begin") == 0)
            tmp=i+1;
        else if (strcmp(com[i], "end") == 0)
        {
            while (lenta[local] != 0)
                command(com, tmp, i);
        }
    }
    
    return 0;
}

char* delprobel (char* st){
    char* com;
    int i, j;
    com = (char*) malloc (sizeof(char)*1000);
    for(i = j = 0; st[i] != '\0'; i++)
        if(isalnum(st[i]))
            com[j++] = st[i];
    com[j] = '\0';
    return com;
}
