#include <stdio.h>
#include <malloc.h>

typedef struct {
    char color1, color2;
    int val1, val2;
    int rot;

} s_tile;

s_tile *readTilesFile(char *fileName, int *len);
s_tile **readBoardFile(char *fileName, int *r, int *c, s_tile *p_tiles);
s_tile tileSetVoid();


int main(int argc, char **argv) {

    int len, r, c;
    s_tile *p_tiles, **m_board;

    p_tiles = readTilesFile(argv[1], &len);
    m_board = readBoardFile(argv[2], &r, &c, p_tiles);


    return 0;
}


s_tile *readTilesFile(char *fileName, int *len){

    FILE *fIn;
    s_tile *TMPp_tiles;

    fIn = fopen(fileName,"r");
    fscanf(fIn, "%d", len);
    TMPp_tiles = (s_tile *)malloc(*len * sizeof(s_tile)); //TODO deallocare

    for (int i = 0; i < *len; ++i) {
        fscanf(fIn," %c %d %c %d", &TMPp_tiles[i].color1, &TMPp_tiles[i].val1, &TMPp_tiles[i].color2, &TMPp_tiles[i].val2);
        TMPp_tiles[i].rot = 0;
    }
    fclose(fIn);
    return TMPp_tiles;
}

s_tile **readBoardFile(char *fileName, int *r, int *c, s_tile *p_tiles){

    FILE *fIn;
    s_tile **TMPm_board;
    int tileIndex, tileRot;

    fIn = fopen(fileName, "r");
    fscanf(fIn,"%d %d", r,c);
    TMPm_board = (s_tile **) malloc(*r*sizeof(s_tile *)); //TODO deallocare

    for (int i = 0; i < *r; ++i) {
        TMPm_board[i] = (s_tile *) malloc(*c * sizeof(s_tile)); //TODO deallocare
        for (int j = 0; j < *c; ++j) {
            fscanf(fIn," %d/%d",&tileIndex,&tileRot);
            if(tileIndex == -1) {
                TMPm_board[i][j] = tileSetVoid();
            } else {
                TMPm_board[i][j] = p_tiles[tileIndex];
            }

        }
    }
    fclose(fIn);
    return  TMPm_board;

}

s_tile tileSetVoid(){

    s_tile TMP_tile;

    TMP_tile.rot = -1;
    TMP_tile.val1 = -1;
    TMP_tile.val2 = -1;
    TMP_tile.color1 = 'X';
    TMP_tile.color2 = 'X';

    return TMP_tile;

}