#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 4 // número de threads
#define QUANTUM 2 // quantum de tempo (em segundos)

pthread_mutex_t lock; // mutex para garantir exclusão mútua
sem_t semaforo; // semáforo para sincronização das threads
int i, processo_atual = 0, tempo_restante = QUANTUM;

typedef struct processo {
    int id;
    int tempo_execucao;
} processo;

processo processos[NTHREADS] = {{0, 5}, {1, 3}, {2, 1}, {3, 4}}; // define os processos com seus tempos de execução

void *func_thread(void *arg) {
    int id = *((int *) arg);
    
    while(1) {
        sem_wait(&semaforo); // espera o semáforo
        pthread_mutex_lock(&lock); // trava o mutex
        
        // Encontra o processo com menor tempo de execução restante
        int menor_tempo = QUANTUM + 1;
        int menor_tempo_id = -1;
        for (int j = 0; j < NTHREADS; j++) {
            if (processos[j].tempo_execucao < menor_tempo && processos[j].tempo_execucao > 0) {
                menor_tempo = processos[j].tempo_execucao;
                menor_tempo_id = j;
            }
        }
        
        // Executa o processo com menor tempo de execução restante
        if (menor_tempo_id >= 0) {
            printf("Thread %d executando processo %d (tempo restante: %d)\n", id, menor_tempo_id, processos[menor_tempo_id].tempo_execucao);
            processos[menor_tempo_id].tempo_execucao--;
        }
        
        pthread_mutex_unlock(&lock); // destrava o mutex
    }
}

int main() {
    pthread_t threads[NTHREADS];
    int ids[NTHREADS];
    
    sem_init(&semaforo, 0, 0);
    pthread_mutex_init(&lock, NULL);
    
    for(i = 0; i < NTHREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, func_thread, &ids[i]);
    }
    
    int c = 0;
    while(c < NTHREADS) {
        sleep(1); // espera 1 segundo
        sem_post(&semaforo); // libera o semáforo
        c++;
    }
    
    for(i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL); // espera todas as threads terminarem
    }
    
    return 0;
}