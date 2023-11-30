#include <stdio.h>
#include <malloc.h>

typedef struct{
    int sTime, fTime, timeLen;
}s_att;

s_att *fileRead(char *fileName, int *p_len);
void sequenceMaker(int len, s_att *p_att);
void powerset_disp_rip_ricors(int pos, int *sol, int *result, int n, s_att *p_att, int *maxSol, int *maxTime, int *maxLen);
int resultVectorMaker(int *result, int len, int *sol);
int check(s_att *p_att, int *result, int len);
int getResultTime(s_att *p_att, int len, int *result);
void sequencePrint(s_att *p_att, int len, int *maxSol);

int main(int argc, char **argv) {

    s_att *p_att;
    int len;

    p_att = fileRead(argv[1], &len);
    sequenceMaker(len,p_att);
    free(p_att);
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

    fclose(fIn);
    return TMPp_att;
}

void sequenceMaker(int len, s_att *p_att){

    int *sol, *maxSol, *result, maxTime = 0, maxLen = 0, resultLen;

    maxSol = (int *)malloc(len * sizeof(int));
    sol = (int *)malloc(len * sizeof(int));
    result = (int *)malloc(len * sizeof(int));
    powerset_disp_rip_ricors(0, sol, result, len, p_att, maxSol, &maxTime, &maxLen);
    sequencePrint(p_att,maxLen, maxSol);
    free(sol);
    free(maxSol);
    free(result);
}

void powerset_disp_rip_ricors(int pos, int *sol, int *result, int n, s_att *p_att, int *maxSol, int *maxTime, int *maxLen){
    int resultTime, resultLen;

    if(pos >= n){
        resultLen = resultVectorMaker(result,n,sol);
        if((!check(p_att,result,resultLen)) && *maxTime < (resultTime = getResultTime(p_att,resultLen, result))){
            *maxTime = resultTime;
            for (int i = 0; i < resultLen; ++i) {
                maxSol[i] = result[i];
                *maxLen = resultLen;
            }
        }

        return;
    }


    sol[pos] = 0;
    powerset_disp_rip_ricors(pos+1, sol, result, n, p_att, maxSol, maxTime, maxLen);
    sol[pos] = 1;
    powerset_disp_rip_ricors(pos+1, sol, result, n, p_att, maxSol, maxTime, maxLen);
}

int resultVectorMaker(int *result, int len, int *sol){
    int j = 0;

    for (int i = 0; i < len; ++i) {
        if(sol[i]){
            result[j] = i;
            j++;
        }

    }
    return j;
}

int check(s_att *p_att, int *result, int len){

    for (int i = 0; i < len-1; ++i) {
        if(p_att[result[i]].fTime > p_att[result[i+1]].sTime) return -1;
    }

    return 0;

}

int getResultTime(s_att *p_att, int len, int *result){

    int time = 0;

    for (int i = 0; i < len; ++i) {
        time = time + p_att[result[i]].timeLen;
    }

    return time;
}

void sequencePrint(s_att *p_att, int len, int *maxSol){

    for (int i = 0; i < len; ++i) {
        printf("(%d %d) ", p_att[maxSol[i]].sTime, p_att[maxSol[i]].fTime);

    }
    printf("\n");
}