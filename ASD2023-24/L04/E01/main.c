#include <stdio.h>
#include <malloc.h>

typedef struct grafo {
    int N, E;
    int **archi;
}*sp_grafo;

void graphRead(struct grafo *sp_grafo, char *fileName);
struct grafo *graphInit();
void partsAlgorithm();
void partsAlgorithmR();

int main(int argc, char **argv) {

    struct grafo *p_grafo;

    p_grafo = graphInit();
    graphRead(p_grafo, argv[1]);
    partsAlgorithm(p_grafo->N, p_grafo);

    return 0;
}

struct grafo *graphInit(){
    struct grafo *p_grafoTmp;

    p_grafoTmp = malloc(sizeof(*p_grafoTmp));

    return p_grafoTmp;
}

void graphRead(struct grafo *sp_grafo, char *fileName){

    FILE *fIn;

    fIn = fopen(fileName, "r");
    fscanf(fIn,"%d", &(sp_grafo->N));
    fscanf(fIn,"%d", &(sp_grafo->E));

    sp_grafo->archi = (int **)malloc(sp_grafo->E * sizeof(int *));
    for (int i = 0; i < sp_grafo->E; ++i) {
        sp_grafo->archi[i] = (int *) malloc(2*sizeof(int));
    }

    for (int i = 0; i < sp_grafo->E; ++i) {
        for (int j = 0; j < 2; ++j) {
            fscanf(fIn, "%d", &(sp_grafo->archi[i][j]));
        }
    }
}

void partsAlgorithm(int n, struct grafo *p_grafo){

    int *val, *sol;

    val = (int *) malloc(n*sizeof(int));
    sol = (int *) malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
        val[i] = i;
    }
    partsAlgorithmR(0,val,sol,n,p_grafo);

}

void partsAlgorithmR(int pos, int *val, int *sol, int n, struct grafo *p_grafo){
    if(pos >= n){
        if(1){
            for (int i = 0; i < n; ++i) {
                if(sol[i]!=0) {
                    printf("%d ", val[i]);
                }
            }
            printf("\n");
            return;
        }
    }

    sol[pos] = 0;
    partsAlgorithmR(pos+1,val,sol,n,p_grafo);
    sol[pos] = 1;
    partsAlgorithmR(pos+1,val,sol,n,p_grafo);
    return;

}