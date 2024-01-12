#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#define MAXLEN 50

typedef struct {
    char strA[MAXLEN], strB[MAXLEN];
    int i;
} s_attributes;

void *sort(void *arg);
void sortAlgorithm(int *vec, int n);

int main(int argc, char **argv){

    s_attributes *attributes;
    pthread_t *p_tid;
    void *exitstatus;
    int n = atoi(argv[1]);


    attributes = (s_attributes *)malloc(n*sizeof(s_attributes));
    p_tid = (pthread_t *)malloc(n*sizeof(pthread_t));
    for (int i = 0; i<n; i++){
        
        strcpy((attributes[i]).strA, argv[2]);
        strcpy((attributes[i]).strB, argv[3]);
        (attributes[i]).i = i+1;
        pthread_create(&(p_tid[i]),NULL,sort,(void *) &(attributes[i]));
    }

    for(int i=0;i<n;i++) {
    pthread_join(p_tid[i] , &exitstatus );
  }
}

void *sort(void *arg){
    
    s_attributes *attributes = (s_attributes *)arg;
    int *vec, n;
    char inFileName[MAXLEN], outFileName[MAXLEN];
    FILE *fIn, *fOut;
    
    sprintf(inFileName,"./%s%d.txt",attributes->strA,attributes->i);
    sprintf(outFileName,"./%s%d.txt",attributes->strB,attributes->i);
    fIn = fopen(inFileName, "r");
    fOut = fopen(outFileName, "w");
    
    fscanf(fIn,"%d",&n);
    vec = (int *) malloc(n*sizeof(int));
    for(int i = 0; i<n; i++){
        fscanf(fIn,"%d",&vec[i]);
    }
    sortAlgorithm(vec, n);

    for (int i = 0; i < n; ++i) {
        fprintf(fOut, "%d\n", vec[i]);
    }

    fclose(fIn);
    fclose(fOut);

    return NULL;
}

void sortAlgorithm(int *vec, int n){

    for(int i=0;i<n;i++) {
        for(int j=0;j<i;j++) {
            if(vec[i]<vec[j]) {
                int temp=vec[i];
                vec[i]=vec[j];
                vec[j]=temp;
            }
        }
    }

}