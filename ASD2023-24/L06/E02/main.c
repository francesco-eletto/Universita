#include <stdio.h>
#include <malloc.h>

typedef struct {

    int nz,nr,nt,ns;
}s_collana;

int main(int argc, char **argv) {

    FILE *fIn;
    s_collana collana;
    int len;

    fIn = fopen(argv[1], "r"); //TODO chiudere
    fscanf(fIn,"%d",&len);

    for (int i = 0; i < len; ++i) {
        fscanf(fIn, " %d %d %d %d", &collana.nz, &collana.nr, &collana.nt, &collana.ns);
    }

    return 0;
}
