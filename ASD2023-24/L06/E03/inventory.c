#include "inventory.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

sp_inventorySetW inventorySetInitialize(){
    sp_inventorySetW TMP_inventorySet;

    TMP_inventorySet = (sp_inventorySetW) malloc(sizeof(*TMP_inventorySet));
    TMP_inventorySet->inventorySet = NULL;
    TMP_inventorySet->len = 0;
    TMP_inventorySet->MaxLen = 0;

    return TMP_inventorySet;
}

int inventorySetRead(char* fileName, sp_inventorySetW inventorySetW){

    FILE *fIn;

    fIn = fopen(fileName, "r");
    if(fIn == NULL) return 6;
    fscanf(fIn, "%d", &inventorySetW->MaxLen);
    inventorySetW->len = 0;
    inventorySetW->inventorySet = (sp_inventory) malloc(inventorySetW->MaxLen * sizeof(*(inventorySetW->inventorySet)));

    for (int i = 0; i < inventorySetW->MaxLen; ++i) {
        fscanf(fIn," %s %s %d %d %d %d %d %d", inventorySetW->inventorySet[i].name, inventorySetW->inventorySet[i].type, &(inventorySetW->inventorySet[i].hpMod), &(inventorySetW->inventorySet[i].mpMod), &(inventorySetW->inventorySet[i].atkMod), &(inventorySetW->inventorySet[i].defMod), &(inventorySetW->inventorySet[i].magMod), &(inventorySetW->inventorySet[i].sprMod));
        inventorySetW->len++;
    }

    return 0;
}

sp_inventory searchByName(char *name, sp_inventorySetW inventorySetW){

    for (int i = 0; i < inventorySetW->len; ++i) {
        if(!strcmp(inventorySetW->inventorySet[i].name, name)){
            printf("%s %s %d %d %d %d %d %d\n", inventorySetW->inventorySet[i].name, inventorySetW->inventorySet[i].type, (inventorySetW->inventorySet[i].hpMod), (inventorySetW->inventorySet[i].mpMod), (inventorySetW->inventorySet[i].atkMod), (inventorySetW->inventorySet[i].defMod), (inventorySetW->inventorySet[i].magMod), (inventorySetW->inventorySet[i].sprMod));
            return &inventorySetW->inventorySet[i];
        }
    }
    return NULL;
}

