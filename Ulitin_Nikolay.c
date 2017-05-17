#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct List1{ //Структура для двусвязанного списка
struct List1 *Left;
int Count;
struct List1 *Right;
} List;

#define NumOfCommands 100 //Объявляем размер блока, на который в случае заполнения будем увеличивать массив
long int AddCommand(char *rout,char *Commands);

int main(int argc,char *argv[]){
    FILE *readFile;
    char rout[255],*Commands,ByteCh;
    int i=0,flag=0,j;
    long int NumCom=0;
    List Word,*Pointer,*PointerBack;
    List Stack,*PointerStack,*PointerStackBack;
    if (argc>1){ //Блок открытия файла с помощью батник
        readFile = fopen(argv[1],"r");
        if (readFile==NULL){
        while(1){ //Считываем до тех пор, пока не будет введен верный путь к файлу
            printf("Unknown file\nEnter a new file name: ");
            scanf("%s",rout);
            readFile = fopen(rout,"r");
            if (readFile!=NULL)
                break;
                }
            }
        }
    else while(1){ //Блок для считывания файла по введенному пути
            printf("Enter a new file name: ");
            scanf("%s",rout);
            readFile = fopen(rout,"r");
            if (readFile!=NULL)
                break;
            printf("Unknown file\n");
        }
        Word.Left=NULL;Word.Right=NULL;Word.Count=0; //Заводим начальные элементы структур
        Stack.Left=NULL;Stack.Right=NULL;Stack.Count=-1;
        Pointer=&Word;PointerStack=&Stack;

        Commands=(char*)malloc(NumOfCommands*sizeof(char));
        j=NumOfCommands;
        while(fscanf(readFile,"%s",rout)!=EOF){ //Считываем команды в массив/увеличиваем размер дин. массива, если переполнение
                if (NumCom==j){
                    j+=NumOfCommands;
                    Commands=(char*)realloc(Commands,j);
                }
                NumCom=AddCommand(rout,Commands);
        }
        fclose(readFile);
        while(i<=NumCom){ //Обрабатываем каждую комманду
        if (flag==0){
            if (Commands[i]=='l'){ //Делаем сдвиг влево по списку
                if (Pointer->Left==NULL){
                    Pointer->Left=(List*)malloc(sizeof(List));
                    PointerBack=Pointer;
                    Pointer=Pointer->Left;
                    Pointer->Right=PointerBack;
                    Pointer->Left=NULL;
                    Pointer->Count=0;
                }
                else
                    Pointer=Pointer->Left;
            }
            if (Commands[i]=='r'){ //Делаем сдвиг вправо по списку
                if (Pointer->Right==NULL){
                    Pointer->Right=(List*)malloc(sizeof(List));
                    PointerBack=Pointer;
                    Pointer=Pointer->Right;
                    Pointer->Left=PointerBack;
                    Pointer->Right=NULL;
                    Pointer->Count=0;
                }
                else
                    Pointer=Pointer->Right;
            }
        if (Commands[i]=='i'){ //Увеличиваем значение в текущей ячейке
            Pointer->Count++;
        if (Pointer->Count==256){ //Проверяем переполнение
            printf("Index out of range\n");
            Pointer->Count=0;
            }
        }
        if (Commands[i]=='d'){ //Уменьшаем значение в текущей ячейке
            Pointer->Count--;
            if (Pointer->Count==-1){
                printf("Index out of range\n"); //Проверяем выход за диапозон значений
                Pointer->Count=0;
            }
        }
        if (Commands[i]=='t') //Выводим численное значение ячейки
            printf("%d\n",Pointer->Count);
        if (Commands[i]=='c') //Выводим символьное значение ячейки
            printf("%c\n",Pointer->Count);
        if (Commands[i]=='g'){ //Считываем символ с консоли
            fflush(stdin);
            scanf("%c",&ByteCh);
            fflush(stdin);
            Pointer->Count=ByteCh;
        }
        }
        if (Commands[i]=='b'){ //Обработчик начала цикла
            if (Pointer->Count==0){
                flag=1;
            }
            PointerStack->Right=(List*)malloc(sizeof(List)); //Добавляем позицию бегина в стек
            PointerStackBack=PointerStack;
            PointerStack=PointerStack->Right;
            PointerStack->Left=PointerStackBack;
            PointerStack->Count=i;
        }
        if (Commands[i]=='e'){ //Обработчик конца списка
            if (Pointer->Count==0){ //Вытаскиваем позицию бегина из стека
                PointerStack=PointerStack->Left;
                free(PointerStack->Right);
                flag=0;
            } else
                i=PointerStack->Count;
        }
        i++; //Рассматриваем следующий элемент
    }
}

long int AddCommand(char *rout,char *Commands){ //Блок обработки введенных комманд
    static long int i=0;
    int j=0;
    while((rout[j]=='/t') || (rout[j]==' '))
        j++;
    if (rout[j]=='m' && rout[j+3]=='l')
        Commands[i]='l';
    if (rout[j]=='m' && rout[j+3]=='r')
        Commands[i]='r';
    if (rout[j]=='i')
        Commands[i]='i';
    if (rout[j]=='d')
        Commands[i]='d';
    if (rout[j]=='g')
        Commands[i]='g';
    if (rout[j]=='p' && rout[j+5]!='c')
        Commands[i]='t';
    if (rout[j]=='p' && rout[j+5]=='c')
        Commands[i]='c';
    if (rout[j]=='b')
        Commands[i]='b';
    if (rout[j]=='*')
        return i;
    if (rout[j]=='e')
        Commands[i]='e';
    i++;
    return i;
}
