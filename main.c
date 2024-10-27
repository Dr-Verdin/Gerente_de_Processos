/*
Nomes:  Bruna Izabel da Silva Pereira - 15635441
        Camila Piscioneri Magalhães - 15697249
        Matheus Guilherme Ferreira Mendonça Learte - 15522362
*/

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
void particiona(celula **lista, int inicio, int fim, int *i, int *j, const char* tipo_chamada);
void quick_sort_prior(celula **prioridade, int inicio, int fim);
void quick_sort_tempo(celula **tempo, int inicio, int fim);
int busca_prioridade(celula **prioridade, int tamanho, int chave);
int busca_tempo(celula **t, celula *chave);
void add(celula **prioridade, celula **tempo, int tamanho);
void exec(celula ***prioridade, celula ***tempo, int *tamanho, bool *ordenada);
void next(celula **prioridade, celula **tempo, int tamanho, bool *ordenada); 
void change(celula **prioridade, celula **tempo, int tamanho, bool *ordenada); 
void print(celula **prioridade, celula **tempo, int tamanho, bool *ordenada);
void apagar(celula ***lista, int tamanho);

void particiona(celula **lista, int inicio, int fim, int *i, int *j, const char* tipo_chamada){
    if(strcmp(tipo_chamada, "prioridade") == 0){
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
    } else if (strcmp(tipo_chamada, "tempo") == 0){
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
}

void quick_sort_prior(celula **prioridade, int inicio, int fim){
    int i, j;
    
    particiona(prioridade, inicio, fim, &i, &j, "prioridade");

    if(inicio<j-1){
        quick_sort_prior(prioridade, inicio, j-1);
    }
    if(i+1<fim){
        quick_sort_prior(prioridade, i+1, fim);
    }
}

void quick_sort_tempo(celula **tempo, int inicio, int fim){
    int i, j;

    particiona(tempo, inicio, fim, &i, &j, "tempo");

    if(inicio<j-1){
        quick_sort_tempo(tempo, inicio, j-1);
    }
    if(i+1<fim){
        quick_sort_tempo(tempo, i+1, fim);
    }
}

void exec(celula ***prioridade, celula ***tempo, int *tamanho, bool *ordenada){ 
    if(!*ordenada){
        quick_sort_prior(*prioridade, 0, *tamanho-1);// Função que ordena a lista "prioridade".
        quick_sort_tempo(*tempo, 0, *tamanho-1);// Função que ordena a lista "tempo".
        *ordenada=true;// Atribui o valor "true" a variável ordenada que está na função main para indicar que os vetores estão ordenados.
    } // Testa se as listas estão ordenadas e caso não estejam ordenadas chama as funções para ordenar e indica qu estão ordenadas atribuindo o valor 1 para a variável "ordenada".

    char flag[3];
    scanf("%s", flag); 

    if(strcmp(flag, "-p")==0){ // Executa o processo com maior prior.
        // Ajusta o indice do array tempo.
        for(int i = 0; i < (*tamanho); i++){
            if((*tempo)[i] == (*prioridade)[(*tamanho) - 1]){
                for(int j = i; j < (*tamanho); j++){
                    (*tempo)[j] = (*tempo)[j + 1];
                }
            }
        }

        free((*prioridade)[(*tamanho) - 1]);// Apaga a celula de maior prioridade alocada.

        // Atualiza o tamanho.
        (*tamanho)--;
    }else if (strcmp(flag, "-t")==0){ // Executa o processo com menor tempo.
        celula *aux=(celula*)malloc(sizeof(celula));

        // Ajusta o indice do array prioridade.
        for(int i = 0; i < (*tamanho); i++){
            if((*prioridade)[i] == (*tempo)[0]){
                aux = (*prioridade)[i];
                for(int j = i; j < (*tamanho); j++){
                    (*prioridade)[j] = (*prioridade)[j + 1];
                }
            }
        }

        // Ajusta o indice do array tempo.
        for(int i = 0; i < (*tamanho); i++){
            (*tempo)[i] = (*tempo)[i + 1];
        }

        free(aux);

        // Atualiza o tamanho.
        (*tamanho)--;
    } else {
        printf("Flag invalida.\n");
        return;
    }
}

void next(celula **prioridade, celula **tempo, int tamanho, bool *ordenada){
    if(!*ordenada){
        quick_sort_prior(prioridade, 0, tamanho-1);// Função que ordena a lista "prioridade".
        quick_sort_tempo(tempo, 0, tamanho-1);// Função que ordena a lista "tempo".
        *ordenada=true;// Atribui o valor "true" a variável ordenada que está na função main para indicar que os vetores estão ordenados.
    } // Testa se as listas estão ordenadas e caso não estejam ordenadas chama as funções para ordenar e indica qu estão ordenadas atribuindo o valor 1 para a variável "ordenada".

    char flag[3];
    scanf("%s", flag); 

    if(strcmp(flag, "-p")==0){ // Celula com maior prioridade.
        printf("\n");

        celula *aux = prioridade[tamanho-1];
        printf("%02d %02d:%02d:%02d ", aux->prior, aux->chegada.hh, aux->chegada.mm, aux->chegada.ss);// Printa a prioridade e a data da celula que "aux" aponta.
        printf("%s\n", aux->descricao); // Printa a descrição da celula atual

        printf("\n");
    }else if (strcmp(flag, "-t")==0){ // Celula com menor tempo.
        printf("\n");

        celula *aux = tempo[0];
        printf("%02d %02d:%02d:%02d ", aux->prior, aux->chegada.hh, aux->chegada.mm, aux->chegada.ss);// Printa a prioridade e a data da celula que "aux" aponta.
        printf("%s\n", aux->descricao); // Printa a descrição da celula atual

        printf("\n");
    } else {
        printf("Flag invalida.\n");
        return;
    }
}

int busca_prioridade(celula **prioridade, int tamanho, int chave){ //A busca da posição para alterar a prioridade é feita por meio da busca binária
    int inf = 0, sup = tamanho - 1, meio; //variável inf que inicialmente começa em 0 que é a primeira posição do vetor prioridade
    //variável sup que inicialmente é a última posição do vetor prioridade
    //variável meio que é a posição meio do vetor prioridade

    if(*prioridade != NULL){ //se verifica se a lista de prioridade não é nula
        while(inf<=sup){ //enquanto as posições inferior e superior não forem iguais
            meio = (inf + sup)/2; //meio = (inicio + fim)/2
            if(chave == prioridade[meio]->prior){ //se a chave que estamos buscando, que é a prioridade procurada, for igual a prioridade na posição meio da lista, se retorna a posição meio
                return meio;
            } else if(chave< prioridade[meio]->prior){ //senão, se a chave for menor, então ela estã localizadana lista prioridade antes da posição meio
                sup = meio - 1; //assim, precisa-se analisar somente o que está antes dessa posição, ou seja, final = meio - 1
            } else { //senão, se a chave for maior, então ela está localizada na lista prioridade depois da posição meio 
                inf = meio + 1; //assim, precisa-se analisar somente o que está depois dessa posição, ou seja, inicio = meio + 1
            }
        }
    }
    return -1; // se não for encontrada a posição se retorna -1
}

int busca_tempo(celula **t, celula *chave) { //para achar a posição para alterar o tempo se fez uma busca sequencial ordenada
    int i=0; //se começa com o indíce i = 0, que é a posição inicial da lista tempo

    if (*t != NULL){ //se verifiica se a lista de tempo não é nula
       while(t[i]->chegada.hh<chave->chegada.hh || (t[i]->chegada.hh==chave->chegada.hh && t[i]->chegada.mm<chave->chegada.mm ) || 
            (t[i]->chegada.hh==chave->chegada.hh && t[i]->chegada.mm==chave->chegada.mm && t[i]->chegada.ss<chave->chegada.ss)){
                i++;
        } //enquanto o tempo da lista for menor que o da chave, que é o tempo que se está procurando, o indice i é adicionado
        if(t[i]->chegada.hh==chave->chegada.hh && t[i]->chegada.mm==chave->chegada.mm && t[i]->chegada.ss==chave->chegada.ss){
            return i; //se posição no tempo que i parou de ser adicionado for igual a chave, então se retorna i
        } else {
            return -1; //se não for, se retorna -1
        }
    } else {
        return -1; //se a lista tempo for igual a nulo se retorna -1
    }
}

void change(celula **prioridade, celula **tempo, int tamanho, bool *ordenada) {
    char flag[3];
    scanf(" %s", flag);

    if (strcmp("-p", flag) == 0) {
        int antes, depois;
        scanf("%d|%d", &antes, &depois); //se recebe o tempo que vai ser mudado e o novo tempo
        if (!*ordenada) {
            quick_sort_prior(prioridade, 0, tamanho - 1); //função que ordena lista de prioridade
            *ordenada = true; // Atribui o valor "true" a variável ordenada que está na função main para indicar que os vetores estão ordenados.
        }
        int pos_prior = busca_prioridade(prioridade, tamanho, antes); //variável irá receber a posição da lista do que irá ser alterado
        if (pos_prior != -1) { //se a posição for válida, então a mudança acontece
            prioridade[pos_prior]->prior = depois;
            *ordenada = false; //variável "ordenada" retorna a seu estado original, pois agora não se sabe se a lista de prioridade continua ordenada
        } else {
            printf("prioridade %d não encontrada.\n", antes);
        }
    } else if(strcmp("-t", flag) == 0){
        if(!*ordenada){
            quick_sort_tempo(tempo, 0, tamanho-1); //função que ordena lista de tempo
            *ordenada = true; // Atribui o valor "true" a variável ordenada que está na função main para indicar que os vetores estão ordenados.
        }
            celula *tempo_antigo = (celula*)malloc(sizeof(celula));
            celula *novo_tempo = (celula*)malloc(sizeof(celula));
            scanf("%d:%d:%d|%d:%d:%d", &tempo_antigo->chegada.hh,&tempo_antigo->chegada.mm,&tempo_antigo->chegada.ss,
            &novo_tempo->chegada.hh,&novo_tempo->chegada.mm,&novo_tempo->chegada.ss); // se recebe o tempo que se quer mudar e o novo tempo
            int pos_tempo = busca_tempo(tempo, tempo_antigo); //variável irá receber a posição da lista do que irá ser alterado

            if(pos_tempo != -1){ //se a posição for válida, então a mudança acontece
                tempo[pos_tempo]->chegada = novo_tempo->chegada;
                *ordenada = false; //variável "ordenada" retorna a seu estado original, pois agora não se sabe se a lista de prioridade continua ordenada
                free(tempo_antigo); //libera memória alocada o ponteiro que recebe o tempo que se queria mudar
                free(novo_tempo);  //libera memória alocada o ponteiro que recebe o novo tempo
            } else {
                printf("tempo %d:%d:%d não encontrado", tempo_antigo->chegada.hh, tempo_antigo->chegada.mm, tempo_antigo->chegada.ss);
            }
        }
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
        printf("\n");

        for(int i = tamanho-1; i >= 0; i--){
            celula *aux= prioridade[i];
            printf("%02d %02d:%02d:%02d ", aux->prior, aux->chegada.hh, aux->chegada.mm, aux->chegada.ss);// Printa a prioridade e a data da celula que "aux" aponta.
            printf("%s\n", aux->descricao);// Printa a descrição da celula atual
        }// Printa todas as celulas que estão guardadas na lista "prioridade" em ordem decrescente.

        printf("\n");
    } else if (strcmp(flag, "-t") == 0) {
        printf("\n");

        for(int i=0; i < tamanho; i++){
            celula *aux = tempo[i];
            printf("%02d %02d:%02d:%02d ", aux->prior, aux->chegada.hh, aux->chegada.mm, aux->chegada.ss);// Printa a prioridade e a data da celula que "aux" aponta.
            printf("%s\n", aux->descricao); // Printa a descrição da celula atual

        }// Printa todas as celulas que estão guardadas na lista "tempo" crescente.

        printf("\n");
    } else {
        printf("Flag invalida.\n");
        return;
    }
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
        for(int i = 0; i < tamanho; i++){
            free((*lista)[i]);// Apaga cada uma das celulas alocadas.
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

        if(strcmp(comando, "quit") == 0){
            apagar(&prioridade, tamanho); // Apaga todos os processos, apaga o vetor de ponteiros que a variável "prioridade" aponta e atribui o valor NULL para ela.
            free(tempo); // Libera o vetor de ponteiros que a variável "tempo" aponta.
            tempo=NULL; // Atribui o valor NULL para a variável "tempo".
            break;
        } else if(strcmp(comando, "add") == 0){
            add(prioridade, tempo, tamanho);
            tamanho++; // incrementa o tamanho.
            ordenada=false; // inicializa como "false" para dizer que as listas ainda não estão ordenadas.
        } else if(strcmp(comando, "exec") == 0){
            exec(&prioridade, &tempo, &tamanho, &ordenada);
        } else if(strcmp(comando, "next") == 0){
            next(prioridade, tempo, tamanho, &ordenada);
        } else if(strcmp(comando, "change") == 0){
            change(prioridade, tempo, tamanho, &ordenada);
        } else if(strcmp(comando, "print") == 0){
            print(prioridade, tempo, tamanho, &ordenada);
        }
    }

    return(0);
}
