#include <stdio.h>
#include <stdlib.h>

//FUNCAO IMPRIMIR
void imprimir(int *v, int size){
    int i;
    for(i = 0; i < size;i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(){
    //DECLARACAO
    char nome[100];
    FILE *arquivo;
    int n, size = 0;
    int *vetor = NULL;
    //ENTRADA
    printf("Digite o nome do arquivo: ");
    scanf("%s",nome);
    arquivo = fopen(nome, "r");
    
    //LENDO CONTEUDO DO ARQUIVO
    if(arquivo != NULL){
        while(!feof(arquivo)){
            fscanf(arquivo, "%d", &n);
            //VETOR CRESCE DINAMICAMENTE
            int *tmp = (int *) realloc(vetor, (size+1) * sizeof(* vetor));
            tmp[size] = n;
            if(tmp != NULL){
                vetor = tmp;
            }
            size++;
        }
    }
    fclose(arquivo);

    //ANALISE DE SEGMENTO
    int j, index = 0;
    int *quant, *valor;
    for(j = 0; j < size; j++){
        if(j == 0){
            valor = malloc(sizeof(int));
            valor[0] = vetor[0];
            quant = malloc(sizeof(int));
            quant[0] = 1;
        }else{
            if(vetor[j-1] == vetor[j]){
                //VERIFICA SE O NUMERO REPETIU PARA INCREMENTAR A QUANTIDADE
                quant[index] = quant[index] + 1;
            }else{
                //CASO SEJA DIFERENTE EH UM NOVO VALOR E TALVEZ UM NOVO TIPO
                index++;
                valor = (int *) realloc(valor, (index+1) * sizeof(int));
                valor[index] = vetor[j];
                quant = (int *) realloc(quant, (index+1) * sizeof(int));
                quant[index] = 1;
            }
        }
    }

    //CRIANDO UM VETOR DE VALORES PARA DEPOIS ORDENA-LO
    int x, y;
    int *ordena = (int *) malloc((index+1) * sizeof(int));
    for(x = 0; x < index+1; x++){
        ordena[x] = valor[x];
    }

    //ORDENANDO O VETOR
    for(x = 1; x < index+1; x++){
        for(y = 0; y < index; y++){
            if (ordena[y] > ordena[y + 1]) {
			    int aux = ordena[y];
                ordena[y] = ordena[y+1];
                ordena[y+1] = aux;
	        }
        }
    }

    //REMOVENDO REPETIDOS DO VETOR ORDENADO
    int tam = index+1;
    int repetidos = 0;
    for(x = 0; x < index - repetidos; x++){
        if(ordena[x] == ordena[x+1]){
            repetidos++;
            int q;
            for(q = x+1; q < index; q++){
                ordena[q] = ordena[q+1]; 
            }
        }
    }
    tam = tam - repetidos;
    ordena = (int *) realloc(ordena, tam * sizeof(int));

    //DEFININDO O TIPO DOS VALORES COM BASE NO INDEX + 1 DO VALOR ORDENADO
    int *tipo = (int *) malloc((index+1) * sizeof(int));
    int k;
    for(k = 0; k < index + 1; k++){
        int c;
        for(c = 0; c < tam; c++){
            if(valor[k] == ordena[c]){
                tipo[k] = c+1;
            }
        }
    }
    //SAIDA
    printf("Matriz:\n");
    imprimir(tipo, index+1);
    imprimir(quant, index+1);
    //LIBERA MEMORIA
    free(ordena);
    free(tipo);
    free(quant);
    free(valor);
    free(vetor);
    return 0;
}
