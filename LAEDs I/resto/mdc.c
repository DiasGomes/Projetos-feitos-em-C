#include <stdio.h>
#include <stdlib.h>

int mdc(int a, int b){
	//algoritmo de euclides
	if ((a % b) != 0){
		return  mdc(b, a%b);	
	}else{
		return b;
	}
}

int main(){
	int num1, num2, resultado = 0;
	printf("Digite dois numeros inteiros: ");
	scanf("%d%d",&num1,&num2);
	//Para o algoritmo funcionar o primeiro parametro tem que ser o maior numero
	//Desta forma garante que funcionara independente da ordem de entrada do usuario  
	if((num1 != 0) && (num2 != 0)){	
		if(num1 >= num2){
			resultado = mdc(num1, num2);
		}else{
			resultado = mdc(num2, num1);
		}
	}
	printf("Resultado %d\n", resultado);
	return 0;
}
