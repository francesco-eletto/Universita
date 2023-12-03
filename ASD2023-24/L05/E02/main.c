#include <stdio.h>
#include <malloc.h>

typedef struct {
    char color1, color2;
    int val1, val2;
    int rot, fixed;

} s_tile;

s_tile *readTilesFile(char *fileName, int *len);
s_tile **readBoardFile(char *fileName, int *r, int *c, s_tile *p_tiles, int *boardFreeSlots);
s_tile tileSetVoid();
void sequenceMaker(s_tile *p_tiles, s_tile **m_board, int len, int r, int c, int tilesLen);
void sequenceMakerR(int pos, int *sol, int n, int r, int c, int tilesLen, int *mark, s_tile *p_tiles, s_tile **m_board, int *maxResult, s_tile ***max_board);
int calculate(s_tile **m_board, int r, int c);
void fillMatrix(s_tile ***m_board, s_tile *p_tiles, int r, int c, int *sol);
void swap(s_tile ***m_board, int r, int c);
s_tile **copyMatrix(s_tile **max_board, int r, int c);
void printSequence(s_tile **m_board, int r, int c, int maxResult);


int main(int argc, char **argv) {

    int tilesLen, boardFreeSlots, r, c;
    s_tile *p_tiles, **m_board;

    p_tiles = readTilesFile(argv[1], &tilesLen);
    m_board = readBoardFile(argv[2], &r, &c, p_tiles, &boardFreeSlots);
    sequenceMaker(p_tiles,m_board,boardFreeSlots, r, c, tilesLen);

    return 0;
}


s_tile *readTilesFile(char *fileName, int *len){

    FILE *fIn;
    s_tile *TMPp_tiles;

    fIn = fopen(fileName,"r");
    fscanf(fIn, "%d", len);
    TMPp_tiles = (s_tile *)malloc(*len * sizeof(s_tile));

    for (int i = 0; i < *len; ++i) {
        fscanf(fIn," %c %d %c %d", &TMPp_tiles[i].color1, &TMPp_tiles[i].val1, &TMPp_tiles[i].color2, &TMPp_tiles[i].val2);
        TMPp_tiles[i].rot = 0;
        TMPp_tiles[i].fixed = 0;
    }
    fclose(fIn);
    return TMPp_tiles;
}

s_tile **readBoardFile(char *fileName, int *r, int *c, s_tile *p_tiles, int *boardFreeSlots){

    FILE *fIn;
    s_tile **TMPm_board;
    int tileIndex, tileRot;


    fIn = fopen(fileName, "r");
    fscanf(fIn,"%d %d", r,c);
    *boardFreeSlots = (*r)*(*c);
    TMPm_board = (s_tile **) malloc(*r*sizeof(s_tile *));

    for (int i = 0; i < *r; ++i) {
        TMPm_board[i] = (s_tile *) malloc(*c * sizeof(s_tile));
        for (int j = 0; j < *c; ++j) {
            fscanf(fIn," %d/%d",&tileIndex,&tileRot);
            if(tileIndex == -1) {
                TMPm_board[i][j] = tileSetVoid();
            } else {
                (*boardFreeSlots)--;
                p_tiles[tileIndex].fixed = 1;
                TMPm_board[i][j] = p_tiles[tileIndex];
                if(tileRot) swap(&TMPm_board,i,j);

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
    TMP_tile.fixed = 0;

    return TMP_tile;

}

void sequenceMaker(s_tile *p_tiles, s_tile **m_board, int len, int r, int c, int tilesLen){

    int *sol, *mark, maxResult = 0;
    s_tile **max_board;

    sol = (int *) malloc(tilesLen *sizeof(int));
    mark = (int *) calloc(tilesLen,sizeof(int));
    sequenceMakerR(0, sol, len, r, c, tilesLen, mark, p_tiles, m_board, &maxResult, &max_board);

    printSequence(max_board, r, c, maxResult);
}

s_tile **copyMatrix(s_tile **max_board, int r, int c){

    s_tile **TMPmax_matrix;

    TMPmax_matrix = (s_tile **) malloc(r * sizeof(s_tile *));
    for (int i = 0; i < r; ++i) {
        TMPmax_matrix[i] = (s_tile *) malloc(c*sizeof(s_tile));
        for (int j = 0; j < c; ++j) {
            TMPmax_matrix[i][j] = max_board[i][j];
        }
    }

    return TMPmax_matrix;
}

void sequenceMakerR(int pos, int *sol, int n, int r, int c, int tilesLen, int *mark, s_tile *p_tiles, s_tile **m_board, int *maxResult, s_tile ***max_board){
    int TMP_result;

    if (pos >= n){
        fillMatrix(&m_board,p_tiles,r,c,sol);
        TMP_result = calculate(m_board,r,c);
        if(TMP_result > *maxResult){
            *maxResult = TMP_result;
            *max_board = copyMatrix(m_board, r, n);
        }
        return;
    }

    for (int i = 0; i < tilesLen; ++i) {
        if (mark[i] == 0 && p_tiles[i].fixed == 0){
            mark[i] = 1;
            sol[pos] = i;
            sequenceMakerR(pos+1, sol, n, r, c, tilesLen, mark, p_tiles, m_board, maxResult, max_board);
            p_tiles[i].rot = 1;
            sequenceMakerR(pos+1, sol, n, r, c, tilesLen, mark, p_tiles, m_board, maxResult, max_board);
            p_tiles[i].rot = 0;
            mark[i] = 0;
        }
    }
}

int calculate(s_tile **m_board, int r, int c){

    int *resultX, *resultY,*flagY, *flagX, result = 0;

    flagX = (int *)calloc(c, sizeof(int));
    flagY = (int *)calloc(r, sizeof(int));



    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if((j != 0) && m_board[i][j].color1 != m_board[i][j-1].color1) flagY[i] = 1;
            if((i != 0) && m_board[i][j].color2 != m_board[i-1][j].color2) flagX[j] = 1;
        }
    }

    for (int i = 0; i < c; ++i) {
        if(!flagX[i]){
            for (int j = 0; j < r; ++j) {
                result += m_board[i][j].val2;
            }
        }
    }
    for (int i = 0; i < r; ++i) {
        if(!flagY[i]){
            for (int j = 0; j < c; ++j) {
                result += m_board[i][j].val1;
            }
        }
    }

    return result;

}

void fillMatrix(s_tile ***m_board, s_tile *p_tiles, int r, int c, int *sol){

    int index = 0;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if ((*m_board)[i][j].fixed == 0){
                (*m_board)[i][j] = p_tiles[sol[index]];
                index++;
            }
            if((*m_board)[i][j].rot) swap(m_board, i, j);
        }
    }


}

void swap(s_tile ***m_board, int r, int c){

    int TMP_val;
    char TMP_color;

    TMP_val = (*m_board)[r][c].val1;
    (*m_board)[r][c].val1 = (*m_board)[r][c].val2;
    (*m_board)[r][c].val2 = TMP_val;
    TMP_color = (*m_board)[r][c].color1;
    (*m_board)[r][c].color1 = (*m_board)[r][c].color2;
    (*m_board)[r][c].color2 = TMP_color;

}

void printSequence(s_tile **m_board, int r, int c, int maxResult){

    printf("La miglior combinazione e' la seguente: \n", maxResult);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            printf("%c %d %c %d\t\t", m_board[i][j].color1,m_board[i][j].val1,m_board[i][j].color2,m_board[i][j].val2);
        }
        printf("\n\n");
    }
    printf("somma massima: %d", maxResult);

}