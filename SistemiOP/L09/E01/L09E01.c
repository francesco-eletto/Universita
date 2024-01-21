#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#define MAXLEN 100
#define MAXFNAMELEN 20

typedef struct {
    int *end;
    char fName[MAXFNAMELEN];
    char *row;
}s_arg;

sem_t semA, semB, semC;

void *readF(void *arg);
void *swapF(void *arg);
void *writeF(void *arg);

int main(int argc, char **argv){

    int end = 0;
    char row[MAXLEN];
    pthread_t readingTh, swappingTh, writingTh;
    s_arg args[3];
    
    sem_init(&semA,0,1);
    sem_init(&semB,0,0);
    sem_init(&semC,0,0);
    strcpy(args[0].fName, argv[1]);
    args[0].end = &end;
    args[0].row = row;
    args[1].end = &end;
    args[1].row = row;
    strcpy(args[2].fName, argv[2]);
    args[2].row = row;
    args[2].end = &end;
    pthread_create(&readingTh,NULL,readF,(void *)&(args[0]));
    pthread_create(&swappingTh,NULL,swapF,(void *)&(args[1]));
    pthread_create(&writingTh,NULL,writeF,(void *)&(args[2]));
    
    pthread_join(readingTh,NULL);
    return 0;
}

void *readF(void *arg){
    FILE *fIn;
    s_arg *tmps_arg;

    tmps_arg = arg;
    fIn = fopen(tmps_arg->fName,"r");
    while(1){
    sem_wait(&semA);
    if((fgets(tmps_arg->row, MAXLEN, fIn)) == NULL ){
        *(tmps_arg->end) = 1;
        pthread_exit(NULL);
    }
    sem_post(&semB);
    }
}

void *swapF(void *arg){
    int len;
    char tmp;
    s_arg *tmps_arg;
    
    tmps_arg = arg;
    while(1){
    sem_wait(&semB);
    len = strlen(tmps_arg->row);
    for (int i = 0; i < (len/2); i++){
        tmp = tmps_arg->row[len-2-i];
        tmps_arg->row[len-2-i] = tmps_arg->row[i];
        tmps_arg->row[i] = tmp;
    }
    sem_post(&semC);
    }
    pthread_exit(NULL);
}

void *writeF(void *arg){
    s_arg *tmps_arg;
    
    tmps_arg = arg;
    while(1){
    sem_wait(&semC);
    printf("%s",tmps_arg->row);
    sem_post(&semA);
    }
    pthread_exit(NULL);
}
