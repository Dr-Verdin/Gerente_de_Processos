#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 51

typedef struct{
    int hh;
    int mm;
    int ss;
} horario;

typedef struct{
    int prior;
    horario chegada;
    char descricao[MAX];
}celula;

int main(void){
    char *comando[7];
    celula **prioridade=(celula**)malloc(sizeof(celula*)*1);
    celula **tempo=(celula**)malloc(sizeof(celula*)*1);
    int tamanho=0;


    while(1){
        scanf("%s", comando);

        if(strcmp(comando, "quit")==0){
            break;
        }else
        if(strcmp(comando, "add")==0){
            add();
        }else
        if(strcmp(comando, "exec")==0){
            exec();
        }else
        if(strcmp(comando, "next")==0){
            next();
        }else
        if(strcmp(comando, "chance")==0){
            change();
        }
        if(strcmp(comando, "print")==0){
            print();
        }
    }
}