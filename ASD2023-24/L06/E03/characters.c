#include "characters.h"
#include <malloc.h>
#include <stdio.h>

typedef struct S_node{
    struct S_character character;
    struct S_node *next;
} *sp_node;

struct S_list {
    sp_node head;
    int len;
};

sp_list listInitialize(){

    sp_list TMP_list;

    TMP_list = (sp_list) malloc(sizeof(struct S_list));
    TMP_list->head = NULL;
    TMP_list->len = 0;

    return TMP_list;
}

sp_node newNode(sp_node next, s_character character){

    sp_node TMPp_node;

    if((TMPp_node = (sp_node) malloc(sizeof(struct S_node))) == NULL) return TMPp_node;
    TMPp_node->next = next;
    TMPp_node->character = character;
    TMPp_node->character.equipLen = 0;

    return TMPp_node;

}

int addHeadNode(sp_list list, s_character character){
    sp_node TMPp_node;
    TMPp_node = newNode(list->head,character);
    if(TMPp_node == NULL) return 1;
    list->head = TMPp_node;
    list->len++;
    return 0;
}

int fileRead(char *fileName, sp_list list){

    FILE *fIn = fopen(fileName, "r");
    s_character TMP_character;

    if(fIn == NULL){
        return 2;
    }
    while (fscanf(fIn," %s %s %s %d %d %d %d %d %d", TMP_character.code, TMP_character.name, TMP_character.class, &TMP_character.hp, &TMP_character.mp, &TMP_character.atk, &TMP_character.def, &TMP_character.mag, &TMP_character.spr) != EOF){
        if(addHeadNode(list,TMP_character)) return 5;
    }
    fclose(fIn);
    return 0;
}

sp_character searchByCode(sp_list list, int code){

    sp_node x;
    int TMP_code;
    sp_character TMP_character = NULL;

    for (x = list->head; x != NULL; x = x->next){
        sscanf(x->character.code, "PG%d",&TMP_code);
        if(TMP_code == code){
            printf("Personaggio trovato: %s %s %s %d %d %d %d %d %d\n", x->character.code, x->character.name, x->character.class, x->character.hp, x->character.mp, x->character.atk, x->character.def, x->character.mag, x->character.spr);
            TMP_character = &x->character;
            if(x->character.equipLen){
                printf("Ogetti posseduti:\n");
                for (int i = 0; i < x->character.equipLen; ++i) {
                    printf("%s %s %d %d %d %d %d %d\n", x->character.equip[i]->name, x->character.equip[i]->type, x->character.equip[i]->hpMod, x->character.equip[i]->mpMod, x->character.equip[i]->atkMod, x->character.equip[i]->defMod, x->character.equip[i]->magMod, x->character.equip[i]->sprMod);
                }
            }
            return TMP_character;
        }

    }
    return NULL;

}

int deleteByCode(sp_list list, int code){

    sp_node x, p;
    int TMP_code;

    for (p = NULL, x = list->head; x != NULL; p = x, x = x->next){
        sscanf(x->character.code, "PG%d",&TMP_code);
        if(TMP_code == code){
            printf("Personaggio eliminato: %s %s %s %d %d %d %d %d %d", x->character.code, x->character.name, x->character.class, x->character.hp, x->character.mp, x->character.atk, x->character.def, x->character.mag, x->character.spr);
            p->next = x->next;
            if(x->next == list->head){
                list->head = x->next;
            }
            list->len--;
            free(x);
            return 0;
        }
    }

    return 4;

}

int addItem(sp_inventorySetW inventorySetW, sp_list list, int pgCode, char *itemName){

    sp_inventory TMP_inventory;
    sp_character TMP_character;

    if((TMP_inventory = searchByName(itemName,inventorySetW)) != NULL && (TMP_character = searchByCode(list,pgCode)) != NULL){
        TMP_character->equip[TMP_character->equipLen] = TMP_inventory;
        TMP_character->equipLen++;
        return 0;
    }
    return 8;
}

int removeItem(sp_list list, int pgCode, char *itemName){

    sp_character TMP_character;

    if((TMP_character = searchByCode(list,pgCode)) != NULL){
        for (int i = 0; i < TMP_character->equipLen; ++i) {
            if(TMP_character->equip[i]->name == itemName){
                TMP_character->equip[i] = NULL;
                TMP_character->equipLen--;
                return 0;
            }
        }

        return 9;
    }
    return 8;
}