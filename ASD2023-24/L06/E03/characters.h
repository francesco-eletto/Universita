#ifndef E03_CHARACTERS_H
#define E03_CHARACTERS_H
#define LENCODE 7
#define LENSTRING 50

typedef struct S_character {
    char code[LENCODE], name[LENSTRING], class[LENSTRING];
    int hp, mp, atk, def, mag, spr;
}s_character;

typedef struct S_list *sp_list;

sp_list listInitialize();
int addHeadNode(sp_list list, s_character character);
int fileRead(char *fileName, sp_list list);
int searchByCode(sp_list list, int code);
int deleteByCode(sp_list list, int code);

#endif //E03_CHARACTERS_H
