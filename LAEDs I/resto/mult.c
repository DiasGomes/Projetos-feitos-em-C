#include <stdio.h>
#include <stdlib.h>

int mult(int base, int exp){
	if(exp > 1){
		return base * mult(base, exp-1);
	}else{
		return base;
	}
}

int main(){
	int base, exp, resultado;
	printf("Digite a base e o expoente inteiros: ");
	scanf("%d%d", &base, &exp);
	resultado = mult(base, exp);
	printf("Resultado: %d\n", resultado);
	return 0;
}
