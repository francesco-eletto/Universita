#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAXLEN 50

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
void fileRead(char *fileName, s_list *p_list);
s_item searchByCode(int code, s_list *p_list);
s_item itemVoid();
void itemPrint(s_item item);


int main() {

    s_list *p_list;
    p_list = newList();

    fileRead("../anag1.txt",p_list);
    itemPrint(searchByCode(2,p_list));

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
    if (TMPp_node == NULL) return NULL;
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

    s_node *x, *p, *tmp;

    if(p_list->head == NULL || dataGrater(item.dataNascita, p_list->head->item.dataNascita)){
        if((tmp = newNode(p_list->head,item)) == NULL) return NULL;
        (p_list->N)++;
        return tmp;
    }

    p = NULL;
    for (x = p_list->head; x != NULL && dataGrater(x->item.dataNascita, item.dataNascita); p = x, x = x->next);
    if ((p->next = newNode(x, item)) == NULL) return NULL;
    (p_list->N)++;
    return p_list->head;

}

void fileRead(char *fileName, s_list *p_list){

    FILE *fIn;
    s_item TMP_item;
    s_node *TMPp_head;

    fIn = fopen(fileName,"r");
    while ((fscanf(fIn, "A%d %s %s %d/%d/%d %s %s %d ",&TMP_item.codice,TMP_item.nome,TMP_item.cognome,&TMP_item.dataNascita.giorno,&TMP_item.dataNascita.mese,&TMP_item.dataNascita.anno,TMP_item.via,TMP_item.citta,&TMP_item.cap)) != EOF){
        TMPp_head = listSortInsert(p_list, TMP_item);
        if(TMPp_head == NULL){
            printf("Impossibile allocare memoria!");
            return;
        }
        p_list->head = TMPp_head;
    }

}

s_item itemVoid(){
    s_item TMP_item;

    TMP_item.dataNascita.anno = -1;
    TMP_item.dataNascita.giorno = -1;
    TMP_item.dataNascita.mese = -1;
    TMP_item.codice = -1;
    TMP_item.cap = -1;
    strcpy(TMP_item.citta,"NULL");
    strcpy(TMP_item.nome,"NULL");
    strcpy(TMP_item.cognome,"NULL");

    return TMP_item;

}

s_item searchByCode(int code, s_list *p_list){

    s_node *x;

    for (x = p_list->head; x != NULL && x->item.codice != code; x = x->next) {
    }
    if(x == NULL) return itemVoid();
    return x->item;
}

void itemPrint(s_item item){

    printf("A%.4d %s %s %.2d/%.2d/%.4d %s %s %.5d", item.codice, item.nome, item.cognome, item.dataNascita.giorno, item.dataNascita.mese, item.dataNascita.anno, item.via, item.citta, item.cap);

}