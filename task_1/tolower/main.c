#include <stdio.h>
#include <stdlib.h>

//Составить программу построчной обработки текста.
//Суть обработки - приведение каждого символа в каждой строке к нижнему регистру.

//Программа считывает входные данные со стандартного ввода,
//и печатает результат в стандартный вывод.

//Процедура приведения к нижнему регистру должна быть оформлена в виде
//отдельной функции, которой на вход подается массив строк
//(который необходимо обработать), количество переданных строк,
//а также указатель на переменную, в которой необходимо разместить
//результат - массив уже обработанных строк.
//В качестве возвращаемого значения функция должна возвращать
//количество строк, содержащихся в результирующем массиве.

#define SIZE_BUFFER 80;
char lower(char c){
    if('A' <= c && c <= 'Z')
        return c - ('A' - 'a');
    return c;
}

char* toLowerString(char *line){
    if(line[0] == '\0')
        return line;

    for(int i = 0; line[i] != '\0'; i++){
        line[i] = lower(line[i]);
    }
    return line;
}

int toLower(char **text, int count, char **result){
    for(int i = 0; i < count; i++){
        result[i] = toLowerString(text[i]);
        if(!text[i]){
            printf("[error]");
            return 0;
        }
    }
    int n = count;
    return n;
}

void printText(register char** text, const int size){
    for(int i = 0; i < size; i++){
        printf("%s\n", text[i]);
    }
}

void freeText(register char** text, const int size){
    for(int i = 0; i < size; i++){
        free(text[i]);
    }
    free(text);
}

char** readText(char** text, int* countLine){
    size_t indexLine = 0;
    size_t size = SIZE_BUFFER;
    text[0] = (char*) calloc((size_t)size, sizeof(char));
    if(!text[0])
        return NULL;

    size_t i = 0;
    char c = '\0';
    while((c = getchar()) != EOF){
        text[indexLine][i++] = c;
        if(c == '\n'){
            text[indexLine][i - 1] = '\0';

            char* temp = NULL;
            temp = (char*)realloc(text[indexLine], i * sizeof(char));
            if(!temp)
                return NULL;
            text[indexLine] = temp;
            char** newText = NULL;
            newText = (char**)realloc(text,  (++indexLine + 1)* sizeof(char*));
            if(!newText)
                return NULL;
            text = newText;

            size = SIZE_BUFFER;
            text[indexLine] = (char*)calloc(size, sizeof(char));
            if(!text[indexLine])
                return NULL;
            i = 0;
        }
        if(i == size){
            size *= 2;
            char *temp = NULL;
            temp = (char*)realloc(text[indexLine], size * sizeof(char));
            if(!temp)
                return NULL;
            text[indexLine] = temp;
        }
    }
    char *temp = (char*)realloc(text[indexLine], ++i * sizeof(char));
    if(!temp)
        return NULL;
    text[indexLine] = temp;
    text[indexLine][--i] = '\0';
    *countLine = ++indexLine;
    return text;
}

int main()
{
    int countLine = 1;
    char** text = NULL;
    text = (char**)calloc(countLine, sizeof(char*));
    if(!text){
        printf("[error]");
        freeText(text, countLine);
        return 0;
    }

    text = readText(text, &countLine);
    if(!text){
        printf("[error]");
        freeText(text, countLine);
        return 0;
    }

    toLower(text, countLine, text);

    printText(text, countLine);
    freeText(text, countLine);
    return 0;
}
