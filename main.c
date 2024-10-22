#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

//Cabeçalho das funções utilizadas no código.
void particiona(celula **lista, int inicio, int fim, int *i, int *j);//x
void particao_tempo(celula **lista, int inicio, int fim, int *i, int *j);//x
void quick_sort_prior(celula **prioridade, int inicio, int fim);//x
void quick_sort_tempo(celula **tempo, int inicio, int fim);//x
void add(celula **prioridade, celula **tempo, int tamanho); //x
void exec(celula **prioridade, celula **tempo, int tamanho, bool *ordenada);
void next(celula **prioridade, celula **tempo, int tamanho, bool *ordenada);
void chance(celula **prioridade, celula **tempo, int tamanho, bool *ordenada); 
void print(celula **prioridade, celula **tempo, int tamanho, bool *ordenada);//x
void apagar(celula ***lista, int tamanho); //x

void particiona(celula **lista, int inicio, int fim, int *i, int *j){
    int pivo = lista[(inicio+fim)/2]->prior;
    *i= inicio;
    *j= fim;

    do{
        while(lista[*i]->prior<pivo){
            (*i)++;
        }

        while(lista[*j]->prior>pivo){
            (*j)--;
        }

        if(*i<*j){
            celula *temp= lista[*i];
            lista[*i]=lista[*j];
            lista[*j]=temp;
        }

    }while(*i<*j);

}

void quick_sort_prior(celula **prioridade, int inicio, int fim){
    int i, j;
    
        particiona(prioridade, inicio, fim, &i, &j);

        if(inicio<j-1){
        quick_sort_prior(prioridade, inicio, j-1);
        }
        if(i+1<fim){
        quick_sort_prior(prioridade, i+1, fim);
        }
}

void particao_tempo(celula **lista, int inicio, int fim, int *i, int *j){
    horario pivo=lista[(inicio+fim)/2]->chegada;
    *i=inicio;
    *j=fim;
    celula *temp;

    do{
        while(lista[*i]->chegada.hh<pivo.hh || (lista[*i]->chegada.hh==pivo.hh && lista[*i]->chegada.mm<pivo.mm ) || 
        (lista[*i]->chegada.hh==pivo.hh && lista[*i]->chegada.mm==pivo.mm && lista[*i]->chegada.ss<pivo.ss)){
            (*i)++;
        }

        while(lista[*j]->chegada.hh>pivo.hh || (lista[*j]->chegada.hh==pivo.hh && lista[*j]->chegada.mm>pivo.mm ) || 
        (lista[*j]->chegada.hh==pivo.hh && lista[*j]->chegada.mm==pivo.mm && lista[*j]->chegada.ss>pivo.ss)){
            (*j)--;
        }

        if(*i<*j){
            temp= lista[*i];
            lista[*i]=lista[*j];
            lista[*j]=temp;
        }

    }while(*i<*j);
}

void quick_sort_tempo(celula **tempo, int inicio, int fim){
    int i, j;

    particao_tempo(tempo, inicio, fim, &i, &j);

    if(inicio<j-1){
        quick_sort_tempo(tempo, inicio, j-1);
    }
    if(i+1<fim){
        quick_sort_tempo(tempo, i+1, fim);
    }
}

void exec(celula **prioridade, celula **tempo, int tamanho, bool *ordenada){
    if(!*ordenada){
            quick_sort_prior(prioridade, 0, tamanho-1);// Função que ordena a lista "prioridade".
            quick_sort_tempo(tempo, 0, tamanho-1);// Função que ordena a lista "tempo".
            *ordenada=true;// Atribui o valor "true" a variável ordenada que está na função main para indicar que os vetores estão ordenados.
    } // Testa se as listas estão ordenadas e caso não estejam ordenadas chama as funções para ordenar e indica qu estão ordenadas atribuindo o valor 1 para a variável "ordenada".
}

void next(celula **prioridade, celula **tempo, int tamanho, bool *ordenada){
    if(!*ordenada){
            quick_sort_prior(prioridade, 0, tamanho-1);// Função que ordena a lista "prioridade".
            quick_sort_tempo(tempo, 0, tamanho-1);// Função que ordena a lista "tempo".
            *ordenada=true;// Atribui o valor "true" a variável ordenada que está na função main para indicar que os vetores estão ordenados.
    } // Testa se as listas estão ordenadas e caso não estejam ordenadas chama as funções para ordenar e indica qu estão ordenadas atribuindo o valor 1 para a variável "ordenada".
}

void chance(celula **prioridade, celula **tempo, int tamanho, bool *ordenada){
    if(!*ordenada){
            quick_sort_prior(prioridade, 0, tamanho-1);// Função que ordena a lista "prioridade".
            quick_sort_tempo(tempo, 0, tamanho-1);// Função que ordena a lista "tempo".
            *ordenada=true;// Atribui o valor "true" a variável ordenada que está na função main para indicar que os vetores estão ordenados.
    } // Testa se as listas estão ordenadas e caso não estejam ordenadas chama as funções para ordenar e indica qu estão ordenadas atribuindo o valor 1 para a variável "ordenada".
}

void print(celula **prioridade, celula **tempo, int tamanho, bool *ordenada){
    if(!*ordenada){
            quick_sort_prior(prioridade, 0, tamanho-1); // Função que ordena a lista "prioridade".
            quick_sort_tempo(tempo, 0, tamanho-1);// Função que ordena a lista "tempo".
            *ordenada=true;// Atribui o valor "true" a variável ordenada que está na função main para indicar que os vetores estão ordenados.
    } // Testa se as listas estão ordenadas e caso não estejam ordenadas chama as funções para ordenar e indica qu estão ordenadas atribuindo o valor 1 para a variável "ordenada".

    char flag[3];
    
    scanf(" %s", flag); // leitura da flag para saber se printa toda a lista "prioridade" ou "tempo".

    if(strcmp(flag, "-p")==0){
        for(int i=tamanho-1; i>=0; i--){
            celula *aux= prioridade[i];
            printf("%02d %02d:%02d:%02d ", aux->prior, aux->chegada.hh, aux->chegada.mm, aux->chegada.ss);// Printa a prioridade e a data da celula que "aux" aponta.
            printf("%s\n", aux->descricao);// Printa a descrição da celula atual
        }// Printa todas as celulas que estão guardadas na lista "prioridade" em ordem decrescente.

        printf("\n");
    }else
    for(int i=0; i<tamanho; i++){
        celula *aux = tempo[i];
        printf("%02d %02d:%02d:%02d ", aux->prior, aux->chegada.hh, aux->chegada.mm, aux->chegada.ss);// Printa a prioridade e a data da celula que "aux" aponta.
        printf("%s\n", aux->descricao); // Printa a descrição da celula atual

    }// Printa todas as celulas que estão guardadas na lista "tempo" crescente.

    printf("\n");
}   

void add(celula **prioridade, celula **tempo, int tamanho){
    celula *aux=(celula*)malloc(sizeof(celula)); // Aloca uma celula na heap.

    scanf("%d", &aux->prior); // Le a prioridade e guarda no conteudo da variavel "aux".
    scanf("%d:%d:%d", &aux->chegada.hh, &aux->chegada.mm, &aux->chegada.ss); // Le o horário e guarda no conteudo da variável "aux".
    scanf(" %s", aux->descricao);// Le a descrição e guarda no conteudo da variável "aux" também.

    prioridade[tamanho]=aux;// Guarda o endereço do ponteiro "aux" na lista "prioridade".
    tempo[tamanho]=aux;// Guarda o endereço do ponteiro "aux" na lista "tempo".
}

void apagar(celula ***lista, int tamanho){
    if(lista!=NULL){
        for(int i=0; i<tamanho; i++){
            free((*lista)[i]);// Apaga cada uma das celulas alocadas
            (*lista)[i]=NULL;// Atribui o valor NULL para os ponteiros que apontavam para cada uma das celulas alocadas.
        }
        free(*lista);// Libera o vetor de ponteiros que o conteudo da variável lista aponta. 
        (*lista)=NULL; // Atribui o valor NULL para o conteudo da variável lista.
    }
}



int main(void){
    char comando[7];
    celula **prioridade=(celula**)malloc(sizeof(celula*)*MAX); // Vetor que guarda os processos ordenados em relação a prioridade. 
    celula **tempo=(celula**)malloc(sizeof(celula*)*MAX); // Vetor que os processos ordenados em relação ao tempo.
    int tamanho=0; // Tamanho dos vetores.
    bool ordenada; // Variável para saber se os vetores estão ordenados.

    if(tempo==NULL|| prioridade==NULL){
        printf("Erro na alocação da memória dos vetores"); // Printa isso caso os vetores não tenham conseguido ser alocados. 
        return(1); // Esse return indica que o programa terminou por conta de uma falha que, nesse caso, é uma falha de alocação.
    }

    while(1){
        scanf(" %s", comando); // Leitura do comando.

        if(strcmp(comando, "quit")==0){
            apagar(&prioridade, tamanho); // Apaga todos os processos, apaga o vetor de ponteiros que a variável "prioridade" aponta e atribui o valor NULL para ela.
            free(tempo); // Libera o vetor de ponteiros que a variável "tempo" aponta.
            tempo=NULL; // Atribui o valor NULL para a variável "tempo".
            break;
        }else
        if(strcmp(comando, "add")==0){
            add(prioridade, tempo, tamanho);
            tamanho++; // incrementa o tamanho.
            ordenada=false; // inicializa como "false" para dizer que as listas ainda não estão ordenadas.
        }else
        if(strcmp(comando, "exec")==0){
            exec(prioridade, tempo, tamanho, &ordenada);
        }else
        if(strcmp(comando, "next")==0){
            next(prioridade, tempo, tamanho, &ordenada);
        }else
        if(strcmp(comando, "chance")==0){
            chance(prioridade, tempo, tamanho, &ordenada);
        }
        if(strcmp(comando, "print")==0){
            print(prioridade, tempo, tamanho, &ordenada);
        }// 
    }

return(0);
}