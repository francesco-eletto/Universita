#include <stdio.h>
#include <malloc.h>

typedef struct graph {
    int N, E;
    int **archi;
}s_graph;

void graphRead(s_graph *p_graph, char *fileName);
s_graph *graphInit();
void partsAlgorithm();
void partsAlgorithmR();
int check(int *sol, s_graph *p_graph);

int main(int argc, char **argv) {

    s_graph *p_graph;

    p_graph = graphInit();
    graphRead(p_graph, argv[1]);
    partsAlgorithm(p_graph->N, p_graph);

    return 0;
}

s_graph *graphInit(){
    s_graph *p_graphTmp;

    p_graphTmp = malloc(sizeof(*p_graphTmp));

    return p_graphTmp;
}

void graphRead(s_graph *p_graph, char *fileName){

    FILE *fIn;

    fIn = fopen(fileName, "r");
    fscanf(fIn,"%d", &(p_graph->N));
    fscanf(fIn,"%d", &(p_graph->E));

    p_graph->archi = (int **)malloc(p_graph->E * sizeof(int *));
    for (int i = 0; i < p_graph->E; ++i) {
        p_graph->archi[i] = (int *) malloc(2 * sizeof(int));
    }

    for (int i = 0; i < p_graph->E; ++i) {
        for (int j = 0; j < 2; ++j) {
            fscanf(fIn, "%d", &(p_graph->archi[i][j]));
        }
    }
}

int check(int *sol, s_graph *p_graph){

    int success = 1;

    for (int i = 0; i < p_graph->E; ++i) {
        if(!(sol[p_graph->archi[i][0]] || sol[p_graph->archi[i][1]])) success = 0;
    }
    return success;

}

void partsAlgorithm(int n, s_graph *p_graph){

    int *val, *sol;

    val = (int *) malloc(n*sizeof(int));
    sol = (int *) malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
        val[i] = i;
    }
    partsAlgorithmR(0, val, sol, n, p_graph);

}

void partsAlgorithmR(int pos, int *val, int *sol, int n, s_graph *p_graph){
    if(pos >= n){
        if(check(sol, p_graph)){
            for (int i = 0; i < n; ++i) {
                if(sol[i]!=0) {
                    printf("%d ", val[i]);
                }
            }
            printf("\n");
        }
        return;
    }

    sol[pos] = 0;
    partsAlgorithmR(pos+1, val, sol, n, p_graph);
    sol[pos] = 1;
    partsAlgorithmR(pos+1, val, sol, n, p_graph);
    return;

}