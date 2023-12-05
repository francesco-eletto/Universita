#include <stdio.h>
#include <malloc.h>

typedef struct {

    int nz,nr,nt,ns;
}s_collana;

void sequenceMaker(s_collana collana);
int fz(s_collana *collana, char **knownSeqZ, char **knownSeqR, char **knownSeqT, char **knownSeqS, int len, int pos, char *sol);
int fr(s_collana *collana, char **knownSeqZ, char **knownSeqR, char **knownSeqT, char **knownSeqS, int len, int pos, char *sol);
int ft(s_collana *collana, char **knownSeqZ, char **knownSeqR, char **knownSeqT, char **knownSeqS, int len, int pos, char *sol);
int fs(s_collana *collana, char **knownSeqZ, char **knownSeqR, char **knownSeqT, char **knownSeqS, int len, int pos, char *sol);
void solLinker(char **sol, int len, int pos, char **knownSeq);

int main(int argc, char **argv) {

    FILE *fIn;
    s_collana collana;
    int len;

    fIn = fopen(argv[1], "r"); //TODO chiudere
    fscanf(fIn,"%d",&len);

    for (int i = 0; i < len; ++i) {
        fscanf(fIn, " %d %d %d %d", &collana.nz, &collana.nr, &collana.nt, &collana.ns);
        sequenceMaker(collana);
    }

    return 0;
}
void sequenceMaker(s_collana collana){

    int len, maxZ, maxR, maxT, maxS;
    char **knownSeqZ, **knownSeqR, **knownSeqT,**knownSeqS, *sol;

    len = collana.nz + collana.nr + collana.nt + collana.ns;
    knownSeqZ = (char **)malloc(len*sizeof(char *)); //TODO deallocare
    knownSeqR = (char **)malloc(len*sizeof(char *));
    knownSeqT = (char **)malloc(len*sizeof(char *));
    knownSeqS = (char **)malloc(len*sizeof(char *));
    sol = (char *)malloc(len * sizeof(char));
    for (int i = 0; i < len; ++i) {
        knownSeqZ[i] = (char *)malloc(len *sizeof(char));
        knownSeqZ[i][0] = 'X';
        knownSeqR[i] = (char *)malloc(len *sizeof(char));
        knownSeqR[i][0] = 'X';
        knownSeqT[i] = (char *)malloc(len *sizeof(char));
        knownSeqT[i][0] = 'X';
        knownSeqS[i] = (char *)malloc(len *sizeof(char));
        knownSeqS[i][0] = 'X';
    }

    maxZ = fz(&collana, knownSeqZ, knownSeqR, knownSeqT, knownSeqS, len, 0, sol);
}

void solLinker(char **sol, int len, int pos, char **knownSeq){

    for (int i = pos; i < len; ++i) {
        (*sol)[i] = knownSeq[len-pos][i-pos];
    }
}

int fz(s_collana *collana, char **knownSeqZ, char **knownSeqR, char **knownSeqT, char **knownSeqS, int len, int pos, char *sol){

    if(knownSeqZ[len - pos][0] != 'X'){
        solLinker(&sol, len, pos, knownSeqZ);
        return len;
    }
    if(pos >= len){
        return len;
    }

    sol[pos] = 'z';
    collana->nz--;
    if(collana->nz){
        fz(collana, knownSeqZ, knownSeqR, knownSeqT, knownSeqS, len, pos+1, sol); //tmp soluzione per salvare la sottosoluzione con un zaffiro dopo
    }
    collana->nz++;
    if(collana->nr){
        fr(collana, knownSeqZ, knownSeqR, knownSeqT, knownSeqS, len, pos+1, sol); //tmp soluzione per salvare la sottosoluzione con un rubino dopo
    }
    collana->nr++;
    return len;

    //controllare per vedere quale delle due collane e migliore e salvare su know

}
