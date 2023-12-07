#ifndef E03_CHARACTERS_H
#define E03_CHARACTERS_H
#include "inventory.h"
#define LENCODE 7
#define MAXEQUIP 8
#define LENSTRING 50

typedef struct S_character {
    char code[LENCODE], name[LENSTRING], class[LENSTRING];
    int hp, mp, atk, def, mag, spr, equipLen;
    sp_inventory equip[MAXEQUIP];
}s_character, *sp_character;

typedef struct S_list *sp_list;

sp_list listInitialize();
int addHeadNode(sp_list list, s_character character);
int fileRead(char *fileName, sp_list list);
sp_character searchByCode(sp_list list, int code);
int deleteByCode(sp_list list, int code);
int addItem(sp_inventorySetW inventorySetW, sp_list list, int pgCode, char *itemName);
int removeItem(sp_list list, int pgCode, char *itemName);

#endif //E03_CHARACTERS_H
