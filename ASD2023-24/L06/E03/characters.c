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

int searchByCode(sp_list list, int code){

    sp_node x;
    int TMP_code;

    for (x = list->head; x != NULL; x = x->next){
        sscanf(x->character.code, "PG%d",&TMP_code);
        if(TMP_code == code){
            printf("Personaggio trovato: %s %s %s %d %d %d %d %d %d", x->character.code, x->character.name, x->character.class, x->character.hp, x->character.mp, x->character.atk, x->character.def, x->character.mag, x->character.spr);
            return 0;
        }
    }

    return 3;

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

