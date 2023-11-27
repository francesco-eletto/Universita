#include <stdio.h>
#include <malloc.h>

typedef struct grafo {
    int N, E;
    int **archi;
}*sp_grafo;

void graphRead(struct grafo *sp_grafo, char *fileName);
struct grafo *graphInit();

int main(int argc, char **argv) {

    struct grafo *p_grafo;

    p_grafo = graphInit();
    graphRead(p_grafo, argv[1]);

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
