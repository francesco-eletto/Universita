#include <stdio.h>
#include "malloc.h"
#include "string.h"
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