#include <stdio.h>
#include <stdlib.h>

/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos(as): Joao Victor Dias Gomes;

Data:

****************/

//ESTRUTURA DE LISTA OBTIDA PELO CODIGO DO ZIVIANE:
//http://www2.dcc.ufmg.br/livros/algoritmos/implementacoes-03.php

typedef int TipoChave;

typedef struct {
  int chave;
  int numElementos;
  int tipo;
  int pontoMedio;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista){
    Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Primeiro;
    Lista -> Primeiro -> Prox = NULL;
}

void Insere(TipoItem x, TipoLista *Lista){
    Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    Lista -> Ultimo -> Item = x;
    Lista -> Ultimo -> Prox = NULL;
}

void ImprimeLista(TipoLista Lista, int conteudo){
    TipoApontador Aux;
    Aux = Lista.Primeiro -> Prox;

    switch (conteudo){
        case 0: printf("Chave:\n");
            break;
        case 1: printf("Numero Elementos:\n");
            break;
        case 2: printf("Tipo:\n");
            break;
        case 3: printf("Ponto Medio:\n");
            break;
        default:    printf("ERRO: conteudo invalido\n");
            break;
        }

    while (Aux != NULL) {
        switch (conteudo){
        case 0: printf("%d ", Aux -> Item.chave);
            break;
        case 1: printf("%d ", Aux -> Item.numElementos);
            break;
        case 2: printf(" %d ", Aux -> Item.tipo);
            break;
        case 3: printf("%d ", Aux -> Item.pontoMedio);
            break;
        default:    printf("-");
            break;
        }
        Aux = Aux -> Prox;
    }
    printf("\n");
}

/* ========================================================================= */

int analiseSegmento(TipoLista Lista){
    int v[5];
    TipoApontador aux;
    aux = Lista.Primeiro -> Prox;
    while (aux != NULL) {
        if(aux -> Item.chave < 4){
            //NAO HA ELEMENTOS SUFICIENTES PARA A SEQUENCIA
            v[aux -> Item.chave] = aux -> Item.tipo;
        }else{
            //PARA INDEX 4 HA 5 ELEMENTOS PELA PRIMEIRA VEZ ENTAO NAO SE DEVE MOVER O VETOR
            if(aux -> Item.chave > 4){
                //MOVE OS ELEMENTOS DO VETOR ELIMINANDO O PRIMEIRO TERMO
                int i;
                for(i = 0; i < 4;i++){
                    v[i] = v[i+1];
                }
            }
            //ULTIMA POSIÇAO RECEBE NOVO ELEMENTO
            v[4] = aux -> Item.tipo;
            //VERIFICA A SEQUENCIA 1 3 2 3 1
            if((v[0] == 1) && (v[1] == 3) && (v[2] == 2) && (v[3] == 3) && (v[4] == 1)){
                 return 1;
            }
        }
        aux = aux -> Prox;
    }
    return 0;
}

//FUNCAO QUE RETORNA O TIPO
int retornaTipo(int num){
    switch (num){
        case 0: return 1;    //PRETO
            break;
        case 128: return 2;  //CINZA
            break;
        case 255: return 3;  //BRANCO
            break;
        default: return -1;  //COR NAO INDENTIFICADA
            break;
        }
}

int main(){

    //DECLARACAO
    char nome[100];
    FILE *arquivo;
    int n, size = 0;
    int *vetor;

    //ELEMENTOS DA LISTA:
    TipoLista lista;
    TipoItem item;
    FLVazia(&lista);

    //ENTRADA
    printf("Digite o nome do arquivo: ");
    scanf("%s",nome);
    arquivo = fopen(nome, "r");

    //LENDO CONTEUDO DO ARQUIVO
    if(arquivo != NULL){
        int cont = 0;
        fscanf(arquivo, "%d", &size);
        vetor = (int *) malloc(size * sizeof(int));
        while(!feof(arquivo)){
            fscanf(arquivo, "%d", &n);
            vetor[cont] = n;
            cont++;
        }
    }
    fclose(arquivo);

    //ANALISE DE SEGMENTO
    int j, index = 0;
    for(j = 0; j < size; j++){
        if(j == 0){
                    item.chave = index;
                    item.tipo = retornaTipo(vetor[0]);
                    item.numElementos = 1;
         }else{
             if(vetor[j-1] == vetor[j]){
                    //VERIFICA SE O NUMERO REPETIU PARA INCREMENTAR A QUANTIDADE
                    item.numElementos = item.numElementos + 1;
             }else{
                    //CASO SEJA DIFERENTE EH UM NOVO VALOR ENTÃO INSERE O ITEM
                    Insere(item, &lista);
                    //RECEBE VALOR DO NOVO ITEM
                    index++;
                    item.chave = index;
                    item.tipo = retornaTipo(vetor[j]);
                    item.numElementos = 1;
                }
            }

    }
    //INSERE O ULTIMO ITEM
    Insere(item, &lista);

    //SAIDA
    if(analiseSegmento(lista)){
        printf("Resultado: Padrao encontrado.\n");
    }else{
        printf("Resultado: Padrao nao encontrado.\n");
    }

    //LIBERA MEMORIA
    free(vetor);
    return 0;
}
