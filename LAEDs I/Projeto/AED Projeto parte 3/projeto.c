#include <stdio.h>
#include <stdlib.h>

/****

LAED1 - Projeto (Parte III) - Estimativa do formato da pista

Alunos(as): Joao Victor Dias Gomes;

Data: 22/01/2022

****/

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

int margemAceitacao(int num){
    //ARRENDODAMENTO DE PORCETAGEM PARA INTEIRO
    num = num * 3;
    if(num % 10 == 0){
        return num;
    }else{
        return num + 1;
    }
}

int formatoPista(int *pm, int tam){
    int margemErro = 15;
    int *tmp = malloc(tam * sizeof(int));
    //VERIFICANDO E DESCARTANDO IMPERFEICOES NA IMAGEM
    int i, erro = 0, valido = 0;
    for(i = 0; i < tam; i++){
        if(pm[i] == -1){
            erro++;
        }else{
            tmp[i-erro] = pm[i];
            valido++;
        }
    }
    tmp = (int *) realloc(tmp, valido * sizeof(int));

    //CASO 70% DAS LINHAS SEJAM VÁLIDAS CALCULA DIFERENÇA ENTRE OS PONTOS MEDIOS
    
    int dif;
    int movimento, pista = 0;

    if(erro <= margemAceitacao(tam)){
        for(i = valido - 1; i > 0; i--){
            //DETECTANDO O MOVIMENTO EM DOIS PONTOS MEDIOS  
            dif = tmp[i] - tmp[i-1];  
            if( (dif > ((-1)*margemErro)) && (dif < margemErro)){
                //RETA
                movimento = 2;
            }else if(dif > margemErro){
                //ESQUERDA
                movimento = 1;
            }else{
                //DIREITA
                movimento = 3;
            }
            //VERIFICANDO UM COMPORTAMENTO
            if(i == valido -1){
                pista = movimento;
            }else{
                switch (pista)
                {
                case 1: //COMPORTAMENTO INESPERADO
                    if((movimento != 1)){pista = 0;}
                    break;
                case 2:
                    pista = movimento;
                    break;
                case 3: //COMPORTAMENTO INESPERADO
                    if(movimento != 3){pista = 0;}
                    break;
                
                default:    pista = 0;
                    break;
                }
            }
        }
    }
    return pista;               
}

int pontoMedio(TipoLista lista){
    TipoApontador tmp;
    tmp = lista.Primeiro -> Prox;
    //PERCORRE A LINHA ARMAZENADA NA LISTA PARA ACHAR O PONTO MEDIO DO ELEMENTO TIPO 2
    while(tmp != NULL){
        if(tmp->Item.tipo == 2){
            return tmp->Item.pontoMedio;
        }
        tmp = tmp -> Prox;
    }
    return -1;
}

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
                 return pontoMedio(Lista);
            }
        }
        aux = aux -> Prox;
    }
    return -1;
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

/*========================================================================================================*/

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
    int pontoInicial, pontoFinal;
    int k, index = 0;
    int *resultado = (int *) malloc(linhas * sizeof(int));
    for(k = 0; k < linhas; k++){ 
        int j;
        //O VALOR DO INDEX DE VETOR TEM DE SER INCREMENTADO A CADA CICLO
        for(j = k*size; j < (k+1)*size; j++){
            if(j == k*size){
                        pontoInicial = 0;
                        index = 0;
                        item.chave = index;
                        item.tipo = retornaTipo(vetor[j]);
                        item.numElementos = 1;
            }else{
                if(vetor[j-1] == vetor[j]){
                        //VERIFICA SE O NUMERO REPETIU PARA INCREMENTAR A QUANTIDADE
                        item.numElementos = item.numElementos + 1;
                        pontoFinal = j - (k*size);
                }else{
                        //CASO SEJA DIFERENTE EH UM NOVO VALOR ENTÃO INSERE O ITEM
                        item.pontoMedio = (pontoInicial+pontoFinal)/2;
                        Insere(item, &lista);
                        //RECEBE VALOR DO NOVO ITEM
                        pontoInicial = j - (k*size);
                        index++;
                        item.chave = index;
                        item.tipo = retornaTipo(vetor[j]);
                        item.numElementos = 1;
                    }
                }

        }
        //INSERE O ULTIMO ITEM 
        pontoFinal = size;
        item.pontoMedio = (pontoInicial+pontoFinal)/2;
        Insere(item, &lista);
        //RECEBE O PONTO MEDIO OU UM VALOR QUE INDICA IMPERFEICAO NA IMAGEM
        resultado[k] = analiseSegmento(lista);
        //ESVAZIA A LISTA PARA ANALISAR A PROXIMA LINHA L
        FLVazia(&lista);
    }

    //SAIDA
    switch (formatoPista(resultado, linhas))
    {
    case 1: printf("Resultado: Curva a esquerda.");
        break;
    case 2: printf("Resultado: Pista em linha reta.");
        break;
    case 3: printf("Resultado: Curva a direita.");
        break;
    default:    printf("Resultado: Formato da pista nao estimado.");
        break;
    }

    //LIBERA MEMORIA E ENCERRA
    free(vetor);
    free(resultado);
    return 0;
}
