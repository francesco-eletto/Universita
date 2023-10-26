#include <stdio.h>
#include "malloc.h"
#define MAXLEN 255

typedef struct {
    char brani[5][255];
    int num;
}s_playlistPerUser;

int fileRead(char *fileName, s_playlistPerUser **playlistPerUser);

int main() {
    s_playlistPerUser *playlistPerUser;
    int len;

    len = fileRead("../brani.txt", &playlistPerUser);

    return 0;
}

int fileRead(char *fileName, s_playlistPerUser **playlistPerUser){
    FILE *fIn;
    int len;
    s_playlistPerUser *tmp_playlistPerUser;

    fIn =fopen(fileName, "r");
    fscanf(fIn,"%d", &len);
    tmp_playlistPerUser = (s_playlistPerUser *)malloc(len* sizeof(s_playlistPerUser));
    *playlistPerUser = tmp_playlistPerUser;

    return len;

}