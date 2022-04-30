#include <stdio.h>
#include <stdlib.h>

int main(){
	//DECLARACAO:
	char nome[100];
	FILE *arquivo;
	int fileiras;
	int matriz[20][20];
	int vetor[210]; //teorema de Gauss -> (20+1)*(20/2)
	int n, i, j;
	//ZERANDO OS VETORES:
	for(n = 0;n < 210;n++){
		vetor[n] = 0;
	}
	for(i = 0;i < 20;i++){
		for(j = 0;j < 20;j++){
			matriz[i][j] = 0;
		}
	}
	//ENTRADA:
	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s",nome);
	//LEITURA:
	arquivo = fopen(nome,"r");
	if(arquivo != NULL){
		int index, numTermos = 0, f;
		fscanf(arquivo,"%d",&fileiras); 
		for(f = fileiras;f > 0;f--){
			numTermos += f;
		}
		for(index = 0;index < numTermos;index++){
			fscanf(arquivo,"%d",&vetor[index]);
		}
	}
	fclose(arquivo);
	//TRANSFORMANDO O VETOR EM UMA MATRIZ TRIANGULAR INFERIOR
	int fila, num = 1,t,indice = 0;
	for(fila = 1;fila < fileiras+1; fila++){
		for(t = 0;t < num;t++){
			matriz[fila - 1][t] = vetor[indice];
			indice++;		
		}
		num++;
		indice = ((1+fila)*(fila))/2;
	}
	//TRANSFORMAÇAO DE MATRIZ 20X20 EM FILEIRAX4:
	int resposta[fileiras][4]; //[0] soma da fileira, [1] maior caixa da fileira
	int l,c;
	for(l = 0;l < fileiras;l++){
		resposta[l][0] = 0;
		resposta[l][1] = matriz[l][0];
		resposta[l][2] = 1;
		resposta[l][3] = l+1;
		for(c = 0;c < 20;c++){
			//CALCULO DA SOMA DE CADA FILEIRA
			resposta[l][0] += matriz[l][c];
			//CALCULO DA MAIOR CAIXA DE CADA FILEIRA
			if(resposta[l][1] < matriz[l][c]){
				resposta[l][1] = matriz[l][c];
				resposta[l][2] = c+1;
				resposta[l][3] = l+1;
			}
 		}
	}
	//CALCULO DA MELHOR CAIXA:
	int fileira = 0, caixa = 0;
	int y,k,maior = 0, tmp;
	for(y = fileiras-1;y > -1;y--){
		tmp = resposta[y][1];
		for(k = y-1;k > -1;k--){
			tmp += resposta[k][0];
		}
		if(tmp > maior){
			maior = tmp;
			fileira = resposta[y][3];
			caixa = resposta[y][2];
		}
	}
	//SAIDA:
	printf("Resposta: fileira %d, caixa %d.\n",fileira,caixa);
	return 0;
}
