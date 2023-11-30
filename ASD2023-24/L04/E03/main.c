#include <stdio.h>
#include "string.h"
#include "malloc.h"
#define LEN 4

typedef struct {
    int nz, nr, nt, ns;
}s_collana;

int found;

void sequenceMaker(s_collana collana);
void r_disp_ripet(int pos, char *val, char *sol, int n, int k);


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
    char *sol, val[LEN];

    found = 0;
    len = collana.ns + collana.nt + collana.nz + collana.nr;
    sol = (char *)malloc(len*sizeof(char));
    strcpy(val,"zrts");

    for (int i = len; i > 0 && found == 0; --i) {
        r_disp_ripet(0,val,sol,LEN,i);
    }

    free(sol);

}

void r_disp_ripet(int pos, char *val, char *sol, int n, int k){
    if(found) return;
    if(pos >= k){
        found = 1;
        for (int i = 0; i < k; ++i) {
            printf("%c",sol[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < n; ++i) {
        sol[pos] = val[i];
        r_disp_ripet(pos+1,val,sol,n,k);
    }
    return;
}
