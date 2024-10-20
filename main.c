#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCR 51
#define MAX 100

typedef struct{
    int hh;
    int mm;
    int ss;
} horario;

typedef struct{
    int prior;
    horario chegada;
    char descricao[MAX_DESCR];
}celula;

void leitura_horario();
void add(celula **prioridade, celula **tempo, int tamanho);
void exec(celula **prioridade, celula **tempo, int tamanho);
void next(celula **prioridade, celula **tempo, int tamanho);
void chance(celula **prioridade, celula **tempo, int tamanho);
void print(celula **prioridade, celula **tempo, int tamanho);

void print(celula **prioridade, celula **tempo, int tamanho){
    char flag[3];
    
    scanf("%s", flag);

    if(strcmp(flag, "-p")){
        for(int i=tamanho-1; i>=0; i--){
            celula *aux= prioridade[i];
            printf("%d %d:%d:%d ", aux->prior, aux->chegada.hh, aux->chegada.mm, aux->chegada.ss);
            printf("%s", aux->descricao);
        }
    }else
    for(int i=0; i<tamanho; i++){
        celula *aux = tempo[i];
        printf("%d %d:%d:%d ", aux->prior, aux->chegada.hh, aux->chegada.mm, aux->chegada.ss);
        printf("%s", aux->descricao);

    }
}

void add(celula **prioridade, celula **tempo, int tamanho){
    celula *aux=(celula*)malloc(sizeof(celula));

    scanf("%d", aux->prior);
    scanf("%d:%d:%d", aux->chegada.hh, aux->chegada.mm, aux->chegada.ss);
    scanf("%s", aux->descricao);

    

}




int main(void){
    char comando[7];
    celula **prioridade=(celula**)malloc(sizeof(celula*)*MAX);
    celula **tempo=(celula**)malloc(sizeof(celula*)*MAX);
    int tamanho=0;

    if(tempo="NULL"){
        
    }

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