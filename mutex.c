#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_OF_THREADS 100
 
static int counter = 0;
pthread_mutex_t mutex;
 
void* minus(void *args) {
    int local;
    pthread_mutex_lock(&mutex);
        local = counter;
        printf("minus %d\n", counter);
        local = local - 1;
        counter = local;
	printf("result %d \n\n", counter);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
 
void* plus(void *args) {
    int local;
    pthread_mutex_lock(&mutex);
        local = counter;
        printf("plus %d\n", counter);
        local = local + 1;
        counter = local;
	printf("plus result %d\n\n", counter);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
 
int main() {
    pthread_t threads[NUM_OF_THREADS];
    size_t i;
 
    printf("counter = %d\n", counter);
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NUM_OF_THREADS/2; i++) {
        pthread_create(&threads[i], NULL, minus, NULL);
    }
    for (; i < NUM_OF_THREADS; i++) {
        pthread_create(&threads[i], NULL, plus, NULL);
    }
    for (i = 0; i < NUM_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("\n\nRESULT = %d \n\n", counter);
    return 0;
}
