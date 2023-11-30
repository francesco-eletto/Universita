#include <stdio.h>
#include <malloc.h>

typedef struct{
    int sTime, fTime, timeLen;
}s_att;

s_att *fileRead(char *fileName, int *p_len);

int main(int argc, char **argv) {

    s_att *p_att;
    int len;

    p_att = fileRead(argv[1], &len);

    return 0;
}

s_att *fileRead(char *fileName, int *p_len){

    FILE *fIn;
    s_att *TMPp_att;

    fIn = fopen(fileName,"r");
    fscanf(fIn,"%d",p_len);
    TMPp_att = (s_att *)malloc(*p_len * sizeof(s_att));

    for (int i = 0; i < *p_len; ++i) {
        fscanf(fIn, "%d %d",&TMPp_att[i].sTime, &TMPp_att[i].fTime);
        TMPp_att[i].timeLen = TMPp_att[i].fTime - TMPp_att[i].sTime;
    }

    return TMPp_att;
}