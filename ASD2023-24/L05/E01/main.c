#include <stdio.h>
#include <malloc.h>

typedef struct{
    int sTime, fTime, timeLen;
}s_att;

s_att *fileRead(char *fileName, int *p_len);
void sequenceMaker(int len, s_att *att);
void powerset_disp_rip_ricors(int pos, int *sol, int *val, int n, s_att *att);


int main(int argc, char **argv) {

    s_att *p_att;
    int len;

    p_att = fileRead(argv[1], &len);
    sequenceMaker(len,p_att);
    return 0;
}

s_att *fileRead(char *fileName, int *p_len){

    FILE *fIn;
    s_att *TMPp_att;

    fIn = fopen(fileName,"r");
    fscanf(fIn,"%d",p_len);
    TMPp_att = (s_att *)malloc(*p_len * sizeof(s_att)); //TODO deallocare

    for (int i = 0; i < *p_len; ++i) {
        fscanf(fIn, "%d %d",&TMPp_att[i].sTime, &TMPp_att[i].fTime);
        TMPp_att[i].timeLen = TMPp_att[i].fTime - TMPp_att[i].sTime;
    }

    return TMPp_att;
}

void sequenceMaker(int len, s_att *p_att){

    int *sol, *val; //TODO deallocare

    sol = (int *)malloc(len * sizeof(int));
    val = (int *)malloc(len * sizeof(int));
    powerset_disp_rip_ricors(0,sol,val,len,p_att);

}

void powerset_disp_rip_ricors(int pos, int *sol, int *val, int n, s_att *p_att){

    if(pos >= n){
        for (int i = 0; i < n; ++i) {
            if(sol[i] == 1) printf("%d %d, ", p_att[i].sTime, p_att[i].fTime);
        }
        printf("\n");
        return;
    }


    sol[pos] = 1;
    powerset_disp_rip_ricors(pos+1,sol,val,n,p_att);
    sol[pos] = 0;
    powerset_disp_rip_ricors(pos+1,sol,val,n,p_att);
}