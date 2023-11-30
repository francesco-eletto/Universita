#include <stdio.h>
#include "string.h"
#include "malloc.h"
#define LEN 4
#define MAXLEN 100

typedef struct {
    int nz, nr, nt, ns;
}s_collana;

int found, pruning;

void sequenceMaker(s_collana collana);
void r_disp_ripet(int pos, char *val, char *sol, int n, int k, s_collana *collana);
int collanaCheckNum(s_collana collana, int index);
void collanaUpdateNum(s_collana *collana, int index, int value);
int check(char followingC, char c);


int main(int argc, char **argv) {

    s_collana collana;
    FILE *fIn;
    int len;

    fIn = fopen(argv[1], "r");
    fscanf(fIn,"%d",&len);

    for (int i = 0; i < len; ++i) {
        fscanf(fIn,"%d %d %d %d", &collana.nz, &collana.nr, &collana.nt, &collana.ns);
        sequenceMaker(collana);
    }

    return 0;
}

void sequenceMaker(s_collana collana){

    int len;
    char sol[MAXLEN], val[LEN];

    found = 0;
    len = collana.ns + collana.nt + collana.nz + collana.nr;
    strcpy(val,"zrts");

    for (int i = len; i > 0 && found == 0; --i) {
        pruning = 1;
        r_disp_ripet(0,val,sol,LEN,i, &collana);
    }


}

void r_disp_ripet(int pos, char *val, char *sol, int n, int k, s_collana *collana){
    if(found || !pruning) return;
    if(pos >= k){
        found = 1;
        for (int i = 0; i < k; ++i) {
            printf("%c",sol[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < n; ++i) {
        if(collanaCheckNum(*collana,i)){
            collanaUpdateNum(collana,i,-1);
            sol[pos] = val[i];
            if(pos != 0){
                pruning = check(sol[pos], sol[pos-1]);
            }
            r_disp_ripet(pos+1,val,sol,n,k,collana);
            pruning = 1;
            collanaUpdateNum(collana,i,1);
        }
    }
    return;
}

int collanaCheckNum(s_collana collana, int index){

    switch (index) {
        case 0:
            if(collana.nz > 0) return 1;
            break;
        case 1:
            if(collana.nr > 0) return 1;
            break;
        case 2:
            if(collana.nt > 0) return 1;
            break;
        case 3:
            if(collana.ns > 0) return 1;
            break;
    }
    return 0;
}

void collanaUpdateNum(s_collana *collana, int index, int value){
    switch (index) {
        case 0:
            collana->nz = collana->nz + value;
            break;
        case 1:
            collana->nr = collana->nr + value;
            break;
        case 2:
            collana->nt = collana->nt + value;
            break;
        case 3:
            collana->ns = collana->ns + value;
            break;
    }
}

int check(char followingC, char c){
    switch (c) {
        case 'z':
            if(followingC == 'z' || followingC == 'r') return 1;
            break;
        case 'r':
            if(followingC == 's' || followingC == 't') return 1;
            break;
        case 't':
            if(followingC == 'z' || followingC == 'r') return 1;
            break;
        case 's':
            if(followingC == 's' || followingC == 't') return 1;
            break;
    }
    return 0;
}