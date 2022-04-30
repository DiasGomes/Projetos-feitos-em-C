#include <stdio.h>
#include <stdlib.h>

/****************

LAED1 - Projeto (Parte II) - Detecção de impedimentos na pista

Alunos(as): Joao Victor Dias Gomes;

Data: 14/01/2022

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
 /*
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
*/
/* ========================================================================= */

int sequenciaCompleta(int v[], int num){
    int aux[5];
    if(num > 4){    //PARA QUE HAJA UMA SEQUENCIA COMPLETA
        int i;
        for(i = 0; i < num; i++){
            if(i < 4){
                aux[i] = v[i];
            }else{
                if(i > 4){
                    //MOVE OS ELEMENTOS DO VETOR ELIMINANDO O PRIMEIRO TERMO
                    int j;
                    for(j = 0; j < 4;j++){
                        aux[j] = aux[j+1];
                    }
                }
                //ULTIMA POSIÇAO RECEBE NOVO ELEMENTO
                aux[4] = v[i];
                //VERIFICA A SEQUENCIA 1 3 2 3 1
                if((aux[0] == 1) && (aux[1] == 3) && (aux[2] == 2) && (aux[3] == 3) && (aux[4] == 1)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int analiseSegmento(TipoLista Lista){

/****************

AVALIA SE HÁ O PADRAO NA LINHA
PADROES VALIDOS:
    2 3 1 X             curva para a esquerda
    X 1 2 3             curva para a direita
    3 2 3 1 X           curva para a esquerda     
    X 1 3 2 3           curva para a direita
    x 1 3 2 3 1 X       reta

****************/
    
    TipoApontador aux;
    aux = Lista.Primeiro -> Prox;
    int size = Lista.Ultimo->Item.chave + 1; //numero de elementos da lista
    int *v = (int *) malloc( size * sizeof(int) ); 
    // TODOS OS TIPOS SAO ARMAZENADOS NO VETOR
    while (aux != NULL) {
        v[aux -> Item.chave] = aux -> Item.tipo;
        aux = aux -> Prox;
        
    }
    if(size > 2){  //MINIMO PARA UMA SEQUENCIA
        if(
            ((v[0] == 2) && (v[1] == 3) && (v[2] == 1)) ||
            ((v[size-3] == 1) && (v[size-2] == 3) && (v[size-1] == 2)) ||
            ((v[0] == 3) && (v[1] == 2) && (v[2] == 3) && (v[3] == 1)) ||
            ((v[size-4] == 1) && (v[size-3] == 3) && (v[size-2] == 2) && (v[size-1] == 3)) ||
            sequenciaCompleta(v, size)
        ){
            return 1;
        }
    }
    free(v);
    return 0;
}



int analiseObstaculo(int v[], int num){
    //SE TODOS OS VALORES FOREM 1s ENTAO TODAS AS LINHAS POSSUEM O SEGMENTO SEM OBSTACULOS
    int i;
    for(i = 0; i < num; i++){
        if(v[i] == 0){
            //ALGUMA LINHA NAO APRESENTOU UMA SEQUENCIA VALIDA
            return 0;
        }
    }
    return 1;
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
    int n, size = 0, linhas = 0;
    int *vetor;

    //CRIANDO UMA LISTA:
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
        fscanf(arquivo, "%d", &linhas);
        fscanf(arquivo, "%d", &size); 
        fscanf(arquivo, "%d", &n);
        vetor = (int *) malloc(size * linhas * sizeof(int));   
        while(!feof(arquivo)){
            fscanf(arquivo, "%d", &n);
            if(cont < (linhas * size)){
                vetor[cont] = n;
            }
            cont++;
        }
    }
    fclose(arquivo);

    //PREENCHENDO A LISTA
    int k, index = 0;
    int *resultado = (int *) malloc(linhas * sizeof(int));
    for(k = 0; k < linhas; k++){ 
        int j;
        //O VALOR DO INDEX DE VETOR TEM DE SER INCREMENTADO A CADA CICLO
        for(j = k*size; j < (k+1)*size; j++){
            if(j == k*size){
                        index = 0;
                        item.chave = index;
                        item.tipo = retornaTipo(vetor[j]);
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
        //ANALISE DO SEGMENTO DA RESPECTIVA LINHA
        if(analiseSegmento(lista)){
            resultado[k] = 1;       //APRESENTA O SEGMENTO
        }else{
            resultado[k] = 0;       //NAO APRESENTA O SEGMENTO
        }
        //ESVAZIA A LISTA PARA ANALISAR A PROXIMA LINHA L
        FLVazia(&lista);
    }

    //SAIDA
    if(analiseObstaculo(resultado, linhas)){
        printf("Resultado: Pista sem impedimento.\n");
    }else{
        printf("Resultado: Pista com impedimento.\n");
    }

    //LIBERA MEMORIA E ENCERRA
    free(vetor);
    free(resultado);
    return 0;
}
