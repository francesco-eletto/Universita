#include <stdio.h>
#include "malloc.h"
#include "string.h"
#define MAXLEN 255

typedef struct {
    char brani[5][MAXLEN];
    int num;
}s_playlistPerUser;

int fileRead(char *fileName, s_playlistPerUser **playlistPerUser);
int multiplyAlgorithm(s_playlistPerUser *playlistPerUser, int len);
int r_multiplyAlgorithm(char **sol, int pos, int n, s_playlistPerUser *playlistPerUser, int count);

int main() {
    s_playlistPerUser *playlistPerUser;
    int len;

    len = fileRead("../brani.txt", &playlistPerUser);
    multiplyAlgorithm(playlistPerUser,len);

    return 0;
}

int multiplyAlgorithm(s_playlistPerUser *playlistPerUser, int len){
    char **sol;

    sol = (char **) malloc(len*sizeof(char *));
    for (int i = 0; i < len; ++i) {
        sol[i] = (char *) malloc(MAXLEN * sizeof(char));
    }
    return r_multiplyAlgorithm(sol,0,len,playlistPerUser,0);
}

int r_multiplyAlgorithm(char **sol, int pos, int n, s_playlistPerUser *playlistPerUser, int count){
    if(pos >= n){
        for (int i = 0; i < n; ++i) {
            printf("%s ", sol[i]);
        }
        printf("\n");
        return count + 1;
    }

    for (int i = 0; i < playlistPerUser[pos].num; ++i) {
        strcpy(sol[pos], playlistPerUser[pos].brani[i]);
        r_multiplyAlgorithm(sol,pos+1,n,playlistPerUser,count);
    }
    return count;
}

int fileRead(char *fileName, s_playlistPerUser **playlistPerUser){
    FILE *fIn;
    int len, num;
    s_playlistPerUser *tmp_playlistPerUser;

    fIn =fopen(fileName, "r");
    fscanf(fIn,"%d", &len);
    tmp_playlistPerUser = (s_playlistPerUser *)malloc(len* sizeof(s_playlistPerUser));

    for (int i = 0; i < len; ++i) {
        fscanf(fIn,"%d", &num);
        tmp_playlistPerUser[i].num = num;
        for (int j = 0; j < num; ++j) {
            fscanf(fIn,"%s", tmp_playlistPerUser[i].brani[j]);
        }
    }

    *playlistPerUser = tmp_playlistPerUser;

    return len;

}