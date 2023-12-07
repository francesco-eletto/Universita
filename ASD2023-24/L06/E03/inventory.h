#ifndef E03_INVENTORY_H
#define E03_INVENTORY_H
#define LENSTRING 50

typedef struct {
    char name[LENSTRING], type[LENSTRING];
    int hpMod, mpMod, atkMod, defMod, magMod, sprMod;
} *sp_inventory;

typedef struct {
    sp_inventory inventorySet;
    int len, MaxLen;
} *sp_inventorySetW;

int inventorySetRead(char* fileName, sp_inventorySetW inventorySetW);
sp_inventory searchByName(char *name, sp_inventorySetW inventorySetW);


#endif //E03_INVENTORY_H
