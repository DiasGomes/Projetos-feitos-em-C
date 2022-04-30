#include <stdio.h>
#include <stdlib.h>

int Digitos(int n){
	if(n > 9){
		n = n / 10;
		return Digitos(n) + 1;	
	}else{
		return 1;	
	}
}

int main(){
	int num;
	printf("Digite um numero inteiro: ");
	scanf("%d",&num);
	num = Digitos(num);
	printf("Resultado: %d\n",num);
	return 0;	
}


