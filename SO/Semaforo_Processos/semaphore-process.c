#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESS  100
#define NUM_STEPS 100000

// funcao soma 
void somaValor(long* sum, sem_t *s)
{
   int i ;

   for (i=0; i< NUM_STEPS; i++)
   {
      sem_wait (s) ;
      *sum += 1 ;   // critical section
      sem_post (s) ;
   }

}

int main (int argc, char *argv[])
{
    
    const int SIZE = 4096;
	const char *name = "shared_memory1";
    const char *name2 = "shared_memory2";
	int shm_fd, shm_fd2;
	long *soma;
    sem_t *s ;

    // cria area de memoria para a variavel soma
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SIZE);
	soma = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (soma == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

    // cria area de memoria para o semaforo
    shm_fd2 = shm_open(name2, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd2,SIZE);
	s = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd2, 0);
	if (s == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

    // inicializa semaforo e memoria compartilhada
    sem_init (s, 1, 1) ;
    *soma = 0;
    printf("mem adress %p, mem content %ld\n", soma, *soma);
    
   // cria os processos
   int filhos, retorno ;
   for(filhos=0; filhos<NUM_PROCESS; filhos++)
   {
      retorno = fork();
      // somente o pai cria os filhos
      if(retorno == 0){
        break;
      }
   }
   
   // espera todos os processos filhos terminarem   
   if(retorno > 0){
        printf("Numero de filhos: %d\n", filhos);
        for (filhos=0; filhos<NUM_PROCESS; filhos++)
        {
            wait(0);
        }
        printf ("A soma deveria ser: %d e foi de: %ld\n", NUM_PROCESS*NUM_STEPS, *soma);
   }else{
        // processos filhos fazem a soma
        somaValor(soma, s);
   }

   exit(0);
}
