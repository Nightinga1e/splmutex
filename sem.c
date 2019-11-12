#define _CRT_SECURE_NO_WARNINGS
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
 
sem_t semaphore;
 
static int counter = 0;
 
void* worker1(void* args) {
    int i;
    int local;
    for (i = 0; i < 100; i++) {
        sem_wait(&semaphore);
        local = counter;
        printf("plus - %d\n", local);
        local++;
        counter = local;
	printf("plus result - %d\n\n", local);
       // sleep(1);
        sem_post(&semaphore);
    }
}
 
void* worker2(void* args) {
    int i;
    int local;
    for (i = 0; i < 100; i++) {
        sem_wait(&semaphore);
        local = counter;
        printf("minus - %d\n", local);
        local--;
        counter = local;
        printf("minus result - %d\n\n", local);
      //  sleep(1);
        sem_post(&semaphore);
    }
}
 
void main() {
    pthread_t thread1;
    pthread_t thread2;
     
    sem_init(&semaphore, 0, 1);
 
    pthread_create(&thread1, NULL, worker1, NULL);
    pthread_create(&thread2, NULL, worker2, NULL);
 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
 
    sem_destroy(&semaphore);
    printf("\n\nRESULT = %d\n", counter);
}
