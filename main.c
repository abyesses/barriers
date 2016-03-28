//
//  main.c
//  ejemplo_barrera
//
//  Created by Abraham Esses on 3/28/16.
//  Copyright © 2016 Abraham Esses. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
void * func (void *);
static pthread_barrier_t barrier;
void * func (void * a){
    int * id = (int *)a;
    for (int i=0; i<10; i++) {
        
        printf("Soy el hilo %d ejecutando acción\n",*id);
        sleep(rand()%5);
    }
    printf("hilo %d termino\n",*id);
    pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
}
int main(int argc, const char * argv[]) {
    srand(time(NULL));
    int *id;
    pthread_t * threads = (pthread_t * )malloc(sizeof(pthread_t)*5);
    pthread_barrier_init(&barrier,NULL,5);
    for (int i = 0; i< 5; i++) {
        id = (malloc(sizeof(int)));
        id = &i;
        pthread_create(&threads[i], NULL, func, (void*)i);
    }
    for (int i = 0; i< 5; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Todos han terminado\n");
    return 0;
}
