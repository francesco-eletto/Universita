#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t semA, semBCD, semEF, semG, semH, semI;

void *thA(void *arg);
void *thB(void *arg);
void *thC(void *arg);
void *thD(void *arg);
void *thE(void *arg);
void *thF(void *arg);
void *thG(void *arg);
void *thH(void *arg);
void *thI(void *arg);


int main(){
    pthread_t A,B,C,D,E,F,G,H,I;
    int i=0;

    sem_init(&semA,0,1);
    sem_init(&semBCD,0,0);
    sem_init(&semEF,0,0);
    sem_init(&semG,0,0);
    sem_init(&semH,0,0);
    sem_init(&semI,0,0);

    while(i<2){
        
        pthread_create(&A,NULL,thA,NULL);
        pthread_create(&B,NULL,thB,NULL);
        pthread_create(&C,NULL,thC,NULL);
        pthread_create(&D,NULL,thD,NULL);
        pthread_create(&E,NULL,thE,NULL);
        pthread_create(&F,NULL,thF,NULL);
        pthread_create(&G,NULL,thG,NULL);
        pthread_create(&H,NULL,thH,NULL);
        pthread_create(&I,NULL,thI,NULL);
        
        
        pthread_join(A,NULL);
        pthread_join(B,NULL);
        pthread_join(C,NULL);
        pthread_join(D,NULL);
        pthread_join(E,NULL);
        pthread_join(F,NULL);
        pthread_join(G,NULL);
        pthread_join(H,NULL);
        pthread_join(I,NULL);
        
        i++;

    }
    
    sem_destroy(&semA);
    sem_destroy(&semBCD);
    sem_destroy(&semEF);
    sem_destroy(&semG);
    sem_destroy(&semH);
    sem_destroy(&semI);



    return(0);
}


void *thA(void *arg){
sem_wait(&semA);
printf("A\n");
sleep(1);
sem_post(&semBCD);
sem_post(&semBCD);
sem_post(&semBCD);
pthread_exit(NULL);
}
void *thB(void *arg){
sem_wait(&semBCD);
printf("B\n");
sleep(1);
sem_post(&semI);
pthread_exit(NULL);
}
void *thC(void *arg){
sem_wait(&semBCD);
printf("C\n");
sleep(1);
sem_post(&semEF);
sem_post(&semEF);
pthread_exit(NULL);
}
void *thD(void *arg){
sem_wait(&semBCD);
printf("D\n");
sleep(1);
sem_post(&semH);
pthread_exit(NULL);
}
void *thE(void *arg){
sem_wait(&semEF);
printf("E\n");
sleep(1);
sem_post(&semG);
pthread_exit(NULL);
}
void *thF(void *arg){
sem_wait(&semEF);
printf("F\n");
sleep(1);
sem_post(&semG);
pthread_exit(NULL);
}
void *thG(void *arg){
sem_wait(&semG);
sem_wait(&semG);
printf("G\n");
sleep(1);
sem_post(&semI);
pthread_exit(NULL);
}
void *thH(void *arg){
sem_wait(&semH);
printf("H\n");
sleep(1);
sem_post(&semI);
pthread_exit(NULL);
}
void *thI(void *arg){
sem_wait(&semI);
sem_wait(&semI);
sem_wait(&semI);
printf("I\n");
sleep(1);
sem_post(&semA);
pthread_exit(NULL);
}


