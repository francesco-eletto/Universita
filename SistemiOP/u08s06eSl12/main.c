#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

#define MAXLEN 50

typedef struct {
    FILE *fIn;
    int sum, cnt, index;
}s_args;

sem_t s;

void *th_readFunction(void *args);

int main(int argc, char **argv){
    
    int k,totSum = 0, totCtr = 0;
    s_args *args;
    FILE *fIn;
    char fileName[MAXLEN];
    pthread_t *vec_tid;

    sem_init(&s,0,1);
    k = atoi(argv[1]);
    vec_tid = (pthread_t *)malloc(k*sizeof(pthread_t));
    args = (s_args *)malloc(k*sizeof(s_args));
    strcpy(fileName,argv[2]);
    fIn = fopen(fileName,"r");

    for(int i = 0; i<k; i++){
        args[i].fIn = fIn;
        args[i].index=i;
        args[i].sum=0;
        args[i].cnt=0;
        pthread_create(&(vec_tid[i]),NULL,th_readFunction,(void *) &(args[i]));
    }

    for(int i = 0; i<k; i++){
        pthread_join(vec_tid[i],NULL);
        totSum += args[i].sum;
        totCtr += args[i].cnt;
    }

    printf("somma totale: %d, valori letti: %d\n", totSum, totCtr);

    return(0);
}

void *th_readFunction(void *args){
    
    int val, retVal;
    s_args *tmp_args;
    tmp_args = args;

    while(1) {
        sem_wait(&s);
        (retVal = fscanf(tmp_args->fIn, "%d", &val));
        sem_post(&s);
        if (retVal == EOF) break;
        tmp_args->sum += val;
        tmp_args->cnt++;
    }
    printf("Thread %d - somma: %d, valori letti: %d\n", tmp_args->index, tmp_args->sum,tmp_args->cnt);
    pthread_exit(0);
}
