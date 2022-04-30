#include <stdlib.h>
#include <stdio.h>

void dec2bin(int dec){
	if((dec / 2) >= 1){
		dec2bin(dec/2);
		printf("%d",dec % 2);
	}else{
		printf("%d", dec % 2);
	}
}

int main(){
	int num;
	printf("Digite um numero inteiro: ");
	scanf("%d",&num);
	printf("Resultado: ");
	dec2bin(num);
	printf("\n");
	return 0;
}
