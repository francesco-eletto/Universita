#include <stdio.h>
#include <malloc.h>
#define MAXLEN 50

typedef struct{
    int codice;
    char nome[MAXLEN];
    char cognome[MAXLEN];
    int giorno;
    int mese;
    int anno;
    char via[MAXLEN];
    char citta[MAXLEN];
    int cap;

}s_item;

typedef struct _s_node{
    s_item item;
    struct _s_node *next;
}s_node;

typedef struct{
    s_node *head;
    int N;
}s_list;

s_list *newList();
s_node *newNode(s_node *next, s_item);


int main() {

    s_list *p_list;

    p_list = newList();

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