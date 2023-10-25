#include "stdio.h"
#include "malloc.h"

int main(){
    int N, *vec;

    printf("Dimensione del vettore:\n");
    scanf("%d", &N);
    vec = (int *)malloc(N*sizeof(int));
    printf("Digita i %d interi: ", N);
    for (int i = 0; i < N; ++i) {
        scanf("%d",&vec[i]);

    }

    return 0;
}