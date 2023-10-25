#include "stdio.h"
#include "malloc.h"

int majority(int *vec, int N);
int r_majority(int l, int r, int *vec);
int val_count(int l, int r, int val, int *vec);

int main(){
    int N, *vec, result;

    printf("Dimensione del vettore:\n");
    scanf("%d", &N);
    vec = (int *)malloc(N*sizeof(int));
    printf("Digita i %d interi: ", N);
    for (int i = 0; i < N; ++i) {
        scanf("%d",&vec[i]);

    }

    result = majority(vec, N);
    printf("%d", result);


    return 0;
}

int majority(int *vec, int N){
    int l = 0, r = N-1;

    return r_majority(l,r,vec);
}

int r_majority(int l, int r, int *vec){
    int q, magl, magr, countl = 0, countr = 0;

    if(l >= r) return vec[r];
    q = (l+r)/2;

    magl = r_majority(l, q, vec);
    countl = val_count(l, r, magl, vec);
    magr = r_majority(q+1,r, vec);
    countr = val_count(l, r, magr, vec);

    if(magr == magl) return magr;
    if(countr >= countl) return magr;
    return magl;

}

int val_count(int l, int r, int val, int *vec){
    int count = 0;

    for (int i = l; i <= r; ++i) {
        if(vec[i] == val) count++;
    }
    if (count <= (r-l)/2 + 1) return -1;
    return count;
}