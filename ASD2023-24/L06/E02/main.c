#include <stdio.h>
#include <stdlib.h>

typedef enum {
    zaffiro,rubino,topazio,smeraldo
} Item;

int SolveM(int *val);
int ****malloc4d(int MAXZ,int MAXR,int MAXT,int MAXS);
int max(int a,int b);
int fz(int ****mz,int ****mr,int ****mt,int ****ms,int *val);
int fr(int ****mz,int ****mr,int ****mt,int ****ms,int *val);
int ft(int ****mz,int ****mr,int ****mt,int ****ms,int *val);
int fs(int ****mz,int ****mr,int ****mt,int ****ms,int *val);
void dealloca(int ****memoizationZ,int ****memoizationR,int ****memoizationT,int ****memoizationS,int maxZ,int maxR,int maxT);

int main(){
    FILE *fp;
    int lunghezza;
    int testcase;
    int i;
    int val[4];
    fp=fopen("../easy_test_set.txt","r");
    if(fp!=NULL){
        fscanf(fp,"%d\n",&testcase);
        for(i=1;i<=testcase;i++){
            fscanf(fp,"%d %d %d %d",&val[zaffiro],&val[rubino],&val[topazio],&val[smeraldo]);
            lunghezza=SolveM(val);
            printf("Lunghezza test %d e' di : %d \n",i,lunghezza);
        }
    }else{
        printf("Errore file");
    }
    return 0;
}

int SolveM(int *val){
    int ****MemorizationZ;
    int ****MemorizationR;
    int ****MemorizationT;
    int ****MemorizationS;
    int lenmax,tmp;
    int MAXZ=val[zaffiro],MAXR=val[rubino],MAXT=val[topazio],MAXS=val[smeraldo];

    MemorizationZ=malloc4d(MAXZ,MAXR,MAXT,MAXS);
    MemorizationR=malloc4d(MAXZ,MAXR,MAXT,MAXS);
    MemorizationT=malloc4d(MAXZ,MAXR,MAXT,MAXS);
    MemorizationS=malloc4d(MAXZ,MAXR,MAXT,MAXS);
    lenmax=fz(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,val);
    tmp=fr(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,val);
    lenmax=max(lenmax,tmp);
    tmp=ft(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,val);
    lenmax=max(lenmax,tmp);
    tmp=fs(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,val);
    lenmax=max(lenmax,tmp);
    dealloca(MemorizationZ,MemorizationR,MemorizationT,MemorizationS,MAXZ,MAXR,MAXT);
    return lenmax;
}

int ****malloc4d(int MAXZ,int MAXR,int MAXT,int MAXS){
    int ****m;
    int z,r,t,s;
    m=(int ****) malloc((MAXZ+1)*sizeof(int ***));
    for(z=0;z<=MAXZ;z++){
        m[z]=(int ***) malloc((MAXR+1)*sizeof(int **));
        for(r=0;r<=MAXR;r++){
            m[z][r]=(int **) malloc((MAXT+1)*sizeof(int *));
            for(t=0;t<=MAXT;t++){
                m[z][r][t]=(int *) malloc((MAXS+1)*sizeof(int));
            }
        }
    }
    for(z=0;z<=MAXZ;z++) for(r=0;r<=MAXR;r++) for(t=0;t<=MAXT;t++) for(s=0;s<=MAXS;s++) m[z][r][t][s]=-1;
    return m;
}

int fz(int ****mz,int ****mr,int ****mt,int ****ms, int *val){
    int maxz,maxr;
    int resz;
    if(val[zaffiro]==0) return 0;
    if(mz[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]!=-1) return mz[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];
    val[zaffiro]--;
    maxz=fz(mz,mr,mt,ms,val);
    maxr=fr(mz,mr,mt,ms,val);
    val[zaffiro]++;
    resz=max(maxz,maxr)+1;
    mz[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]=resz;
    return resz;
}

int ft(int ****mz,int ****mr,int ****mt,int ****ms, int *val){
    int maxz,maxr;
    int rest;
    if(val[topazio]==0) return 0;
    if(mt[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]!=-1) return mt[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];
    val[topazio]--;
    maxz=fz(mz,mr,mt,ms,val);
    maxr=fr(mz,mr,mt,ms,val);
    val[topazio]++;
    rest=max(maxz,maxr)+1;
    mt[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]=rest;
    return rest;
}

int fr(int ****mz,int ****mr,int ****mt,int ****ms, int *val){
    int maxs,maxt;
    int resr;
    if(val[rubino]==0) return 0;
    if(mr[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]!=-1) return mr[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];
    val[rubino]--;
    maxs=fs(mz,mr,mt,ms,val);
    maxt=ft(mz,mr,mt,ms,val);
    val[rubino]++;
    resr=max(maxs,maxt)+1;
    mr[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]=resr;
    return resr;
}

int fs(int ****mz,int ****mr,int ****mt,int ****ms, int *val){
    int maxs,maxt;
    int ress;
    if(val[smeraldo]==0) return 0;
    if(ms[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]!=-1) return ms[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]];
    val[smeraldo]--;
    maxs=fs(mz,mr,mt,ms,val);
    maxt=ft(mz,mr,mt,ms,val);
    val[smeraldo]++;
    ress=max(maxs,maxt)+1;
    ms[val[zaffiro]][val[rubino]][val[topazio]][val[smeraldo]]=ress;
    return ress;
}

int max(int a,int b){
    return a>b ? a:b;
}

void dealloca(int ****memoizationZ,int ****memoizationR,int ****memoizationT,int ****memoizationS,int maxZ,int maxR,int maxT){
    int i,j,k;
    for(i = 0; i <= maxZ; i++) {
        for(j = 0; j <= maxR; j++) {
            for(k = 0; k <= maxT; k++) {
                free(memoizationZ[i][j][k]);
                free(memoizationR[i][j][k]);
                free(memoizationT[i][j][k]);
                free(memoizationS[i][j][k]);
            }
            free(memoizationZ[i][j]);
            free(memoizationR[i][j]);
            free(memoizationT[i][j]);
            free(memoizationS[i][j]);
        }
        free(memoizationZ[i]);
        free(memoizationR[i]);
        free(memoizationT[i]);
        free(memoizationS[i]);
    }
    free(memoizationZ);
    free(memoizationR);
    free(memoizationT);
    free(memoizationS);
}