#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binDec(char v[]){
	//convertendo binario para decimal
	int i, dec = 0;
	for(i = 0;i < 5;i++){
		//[48 a 57] == [0,9] tabela Ascii
		//4-i -> lendo da esquerda para a direita
		dec += ((int) (v[i]-48)) * pow(2,4-i);
	}
	return dec;
}

void deletar(char vetor[], int index, int quantidade){
	//remove n elementos apartir do index do vetor
	int i;
	for(i = index;i < 10000;i++){
		vetor[i] = vetor[i+quantidade];
	}
}

void reflete(char v[]){
	int i;
	char tmp;
	//troca a posicao das duplas
	for(i = 0;i < 10000; i+=2){
		tmp = v[i];
		v[i] = v[i+1];
		v[i+1] = tmp;
	}
}

void space(char v[], int s){
	int i;
	for(i = 0; i < s; i++){
		if(v[i] == '#'){
			v[i] = ' ';
		}
	}
}

void permuta(char v[], int s){
	int i;
	char c1, c2;
	//permuta as duplas
	for(i = 0;i < s/2; i+=4){
		c1 = v[s-i-1];
		c2 = v[s-i-2];
		v[s-i-2] = v[i];
		v[s-i-1] = v[i+1];
		v[i] = c2;
		v[i+1] = c1;
	}
}

void decifra(char v[], int s){
	//cifra de Cezar com uma rotacao de 5 posiçoes a direita
	//tabela ascii [A .. Z] == [65 .. 90] && [a .. z] == [97 .. 122]
	int i;
	for(i = 0;i < s;i++){
		if(v[i] != ' '){
			if(v[i]-5 < 65){
				v[i] = 90 - (64-(v[i]-5));
			}else if((v[i]-5 < 97) && (v[i] - 5) > 90){
				v[i] = 122 - (96-(v[i]-5));
			}else{
				v[i] -= 5;
			}

		}
	}
}

void linha1(){
    printf("--------------------\n");
}

void linha2(){
	printf("----------------------\n");
}

int main(){
	//declaracao:
	char menssagem[10000], nome[100];
	FILE *arquivo;
	int position, size = 0;
	//lendo arquivo:
	printf("Digite o nome do arquivo: ");
	scanf("%s",nome);
	arquivo = fopen(nome, "r");
	if(arquivo != NULL){
		fscanf(arquivo,"%s",menssagem);
	}
	fclose(arquivo);
	//saida 1:
	printf("\n");
	linha1();
	printf("Mensagem codificada:\n");
	linha1();
	printf("%s\n",menssagem);
	//decodificando:
		//posicao caractere extra
		position = binDec(menssagem);
		//removendo caractere extra e binario
		deletar(menssagem,0,5);
		deletar(menssagem, position-1,1);
		//tamanho da menssagem
		while(menssagem[size] != '\0'){
			size++;
		}
		//permutando duplas
		permuta(menssagem, size);
		//refletindo duplas de caracteres
		reflete(menssagem);
		//decifrando
		space(menssagem, size);
		decifra(menssagem, size);
	//saida 2:
	printf("\n");
	linha2();
	printf("Mensagem decodificada:\n");
	linha2();
	printf("%s\n",menssagem);
	return 0;
}


