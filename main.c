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

void add(celula **prioridade, celula **tempo, int tamanho);
void exec(celula **prioridade, celula **tempo, int tamanho);
void next(celula **prioridade, celula **tempo, int tamanho);
void next(celula **prioridade, celula **tempo, int tamanho);
void print(celula **prioridade, celula **tempo, int tamanho);

void print(celula **prioridade, celula **tempo, int tamanho){
    char flag[3];
    
    scanf("%s", flag);

    if(strcmp(flag, "-p")){
        
    }
}




int main(void){
    char comando[7];
    celula **prioridade=(celula**)malloc(sizeof(celula*)*1);
    celula **tempo=(celula**)malloc(sizeof(celula*)*1);
    int tamanho=0;


    while(1){
        scanf("%s", comando);

        if(strcmp(comando, "quit")==0){
            break;
        }else
        if(strcmp(comando, "add")==0){
            add(prioridade, tempo, tamanho);
            tamanho++;
        }else
        if(strcmp(comando, "exec")==0){
            exec(prioridade, tempo, tamanho);
        }else
        if(strcmp(comando, "next")==0){
            next(prioridade, tempo, tamanho);
        }else
        if(strcmp(comando, "chance")==0){
            next(prioridade, tempo, tamanho);
        }
        if(strcmp(comando, "print")==0){
            print(prioridade, tempo, tamanho);
        }
    }
}