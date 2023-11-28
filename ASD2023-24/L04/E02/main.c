#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAXLEN 50
#define MAXDATASTRINGLEN 8

typedef struct{
    int giorno, mese, anno;
}s_data;

typedef struct{
    int codice;
    char nome[MAXLEN];
    char cognome[MAXLEN];
    s_data dataNascita;
    char via[MAXLEN];
    char citta[MAXLEN];
    int cap;

}s_item;

typedef struct ds_node{
    s_item item;
    struct ds_node *next;
}s_node;

typedef struct{
    s_node *head;
    int N;
}s_list;

s_list *newList();
s_node *newNode(s_node *next, s_item);
int dataGrater(s_data data1, s_data data2);
s_node *listSortInsert(s_list *p_list, s_item item);


int main() {

    s_list *p_list;
    p_list = newList();

    s_item item1, item2, item3;

    /*item1.dataNascita.anno = 2023;
    item2.dataNascita.anno = 2021;
    item3.dataNascita.anno = 2009;
    item1.dataNascita.mese = 12;
    item2.dataNascita.mese = 8;
    item3.dataNascita.mese = 2;
    item1.dataNascita.giorno = 7;
    item2.dataNascita.giorno = 31;
    item3.dataNascita.giorno = 25;

    p_list->head = listSortInsert(p_list, item1);
    p_list->head = listSortInsert(p_list, item2);
    p_list->head = listSortInsert(p_list, item3);*/

    return 0;
}

s_list *newList(){

    s_list *TMPp_list;

    TMPp_list = (s_list *) malloc(sizeof(s_list));
    TMPp_list->N = 0;
    TMPp_list->head = NULL;

    return TMPp_list;
}

s_node *newNode(s_node *next, s_item item){

    s_node *TMPp_node;

    TMPp_node = (s_node *) malloc(sizeof(s_node));
    TMPp_node->next = next;
    TMPp_node->item = item;

    return TMPp_node;
}

int dataGrater(s_data data1, s_data data2){

    if(data1.anno > data2.anno) return 1;
    if(data1.anno == data2.anno && data1.mese > data2.mese) return 1;
    if(data1.anno == data2.anno && data1.mese == data2.mese && data1.giorno > data2.giorno) return 1;

    return 0;
}

s_node *listSortInsert(s_list *p_list, s_item item){

    s_node *x, *p;

    if(p_list->head == NULL || dataGrater(item.dataNascita, p_list->head->item.dataNascita)){
        return newNode(p_list->head,item);
    }

    p = NULL;
    for (x = p_list->head; x != NULL && dataGrater(x->item.dataNascita, item.dataNascita); p = x, x = x->next);
    p->next = newNode(x, item);
    return p_list->head;

}