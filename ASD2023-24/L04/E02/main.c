#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAXLEN 50
#define OUTFILENAME "../output.txt"

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

int found = 1;



s_list *newList();
s_node *newNode(s_node *next, s_item);
int dataGrater(s_data data1, s_data data2);
s_node *listSortInsert(s_list *p_list, s_item item);
int fileRead(char *fileName, s_list *p_list);
s_item searchByCode(int code, s_list *p_list);
s_item itemVoid();
void itemPrint(s_item item);
s_item deleteByCode(int code, s_list *p_list);
s_item deleteByDataRange(s_data data1, s_data data2, s_list *p_list);
void printOnFile(char *file, s_list *p_list);


int main() {

    s_list *p_list;
    p_list = newList();
    s_item TMP_item;
    s_data data1, data2;
    int cmdIndex, TMP_code, readReturn;
    char infileName[MAXLEN];

    //CLIENT MENU'

    printf("Scegli un opzione: \n[1]Acquisizione da tastiera\n[2]Acquisizione da file\n[3]Ricerca per codice\n[4]Cancellazione per codice\n[5]Cancellazione in range di date\n[6]Stampa su file\n[0]Esci\n\n");
    scanf("%d",&cmdIndex);

    while(cmdIndex != 0){

        switch (cmdIndex) {
            case 1: //Acquisizione da tastiera
                printf("Inserisci i valori:\ncodice nome cognome giorno mese anno via citta' cap\n\n");
                scanf("%d %s %s %d %d %d %s %s %d",&TMP_item.codice,TMP_item.nome,TMP_item.cognome,&TMP_item.dataNascita.giorno,&TMP_item.dataNascita.mese,&TMP_item.dataNascita.anno,TMP_item.via,TMP_item.citta,&TMP_item.cap);
                if ((p_list->head = listSortInsert(p_list,TMP_item)) == NULL) {
                    printf("Impossibile allocare altro elemento in lista!\n\n");
                }else{
                    printf("Elemento inserito correttamente\n\n");
                }
                break;
            case 2: //Acquisizione da file
                printf("Inserisci nome del file:\n");
                scanf("%s",infileName);
                readReturn = fileRead(infileName,p_list);
                if( readReturn == -1){
                    printf("Impossibile allocare altro elemento in lista!\n\n");
                } else if( readReturn == -2){
                    printf("Impossibile aprire il file!\n\n");
                }
                else{
                    printf("Elementi acquisiti da file correttamente!\n\n");
                }

                break;
            case 3: //Ricerca per codice
                printf("Inserisci codice da ricercare:\n");
                scanf("%d",&TMP_code);
                TMP_item = searchByCode(TMP_code,p_list);
                if(strcmp(TMP_item.nome, "NULL")){
                    itemPrint(TMP_item);
                    printf("\n");
                }else{
                    printf("Nessun elemento trovato con questo codice!\n\n");
                }
                break;
            case 4: //Cancellazione per codice
                printf("Inserisci codice da eliminare:\n");
                scanf("%d",&TMP_code);
                TMP_item = deleteByCode(TMP_code,p_list);
                if(strcmp(TMP_item.nome, "NULL")){
                    itemPrint(TMP_item);
                    printf("Elemento eliminato correttamente\n\n");
                }else{
                    printf("Nessun elemento trovato con questo codice!\n\n");
                }
                break;
            case 5: //Cancellazione in range di date
                printf("Inserisci data1 data2 (gg/mm/aaaa):\n");
                scanf("%d/%d/%d %d/%d/%d", &data1.giorno,&data1.mese,&data1.anno,&data2.giorno,&data2.mese,&data2.anno);
                for (int i = 0; found == 1; ++i) {
                    TMP_item = deleteByDataRange(data1,data2, p_list);
                    if(strcmp(TMP_item.nome, "NULL") == 0){

                    } else{
                        itemPrint(TMP_item);
                    }
                    printf("\n");
                }
                break;
            case 6: //Stampa su file
                printOnFile(OUTFILENAME, p_list);
                break;
            default:
                printf("Digita un'opzione valida!\n\n");
                break;


        }

        printf("Scegli un opzione: \n[1]Acquisizione da tastiera\n[2]Acquisizione da file\n[3]Ricerca per codice\n[4]Cancellazione per codice\n[5]Cancellazione in range di date\n[6]Stampa su file\n[0]Esci\n\n");
        scanf("%d",&cmdIndex);
    }

    //-----------

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
    if(data1.anno == data2.anno && data1.mese == data2.mese && data1.giorno >= data2.giorno) return 1;

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

int fileRead(char *fileName, s_list *p_list){

    FILE *fIn;
    s_item TMP_item;
    s_node *TMPp_head;

    if((fIn = fopen(fileName,"r")) == NULL) return -2;
    while ((fscanf(fIn, "A%d %s %s %d/%d/%d %s %s %d ",&TMP_item.codice,TMP_item.nome,TMP_item.cognome,&TMP_item.dataNascita.giorno,&TMP_item.dataNascita.mese,&TMP_item.dataNascita.anno,TMP_item.via,TMP_item.citta,&TMP_item.cap)) != EOF){
        TMPp_head = listSortInsert(p_list, TMP_item);
        if(TMPp_head == NULL){
            return -1;
        }
        p_list->head = TMPp_head;
    }
    fclose(fIn);
    return 0;

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

    printf("A%.4d %s %s %.2d/%.2d/%.4d %s %s %.5d\n", item.codice, item.nome, item.cognome, item.dataNascita.giorno, item.dataNascita.mese, item.dataNascita.anno, item.via, item.citta, item.cap);

}

s_item deleteByCode(int code, s_list *p_list){

    s_node *x, *p, *tmp;
    s_item TMP_item;
    if(p_list->head == NULL) return itemVoid();
    if(p_list->head->item.codice == code){
        TMP_item = p_list->head->item;
        tmp = p_list->head->next;
        free(p_list->head);
        (p_list->N)--;
        p_list->head = tmp;
        return TMP_item;
    }

    p = NULL;
    for (x = p_list->head; x != NULL && x->item.codice != code; p = x, x = x->next){
    }
    if(x == NULL) return itemVoid();
    TMP_item = x->item;
    tmp = x;
    p->next = x->next;
    (p_list->N)--;
    free(tmp);
    return TMP_item;

}

s_item deleteByDataRange(s_data data1, s_data data2, s_list *p_list){

    s_node *x, *p, *tmp;
    s_item TMP_item;

    found = 0;
    if(p_list->head == NULL) return itemVoid();
    if(dataGrater(p_list->head->item.dataNascita, data1) && dataGrater(data2, p_list->head->item.dataNascita)){
        found = 1;
        TMP_item = p_list->head->item;
        tmp = p_list->head->next;
        free(p_list->head);
        (p_list->N)--;
        p_list->head = tmp;
        return TMP_item;
    }

    for(p = NULL, x = p_list->head; x != NULL && (dataGrater(data1, x->item.dataNascita) || dataGrater(x->item.dataNascita, data2)); p = x, x = x->next){
    }
    if(x == NULL) return itemVoid();
    found = 1;
    TMP_item = x->item;
    tmp = x;
    p->next = x->next;
    (p_list->N)--;
    free(tmp);
    return TMP_item;

}

void printOnFile(char *file, s_list *p_list){

    FILE *fOut;
    s_node *x;

    fOut = fopen(file,"w");
    for (x = p_list->head; x != NULL; x = x->next) {
        fprintf(fOut, "A%.4d %s %s %.2d/%.2d/%.4d %s %s %.5d\n", x->item.codice, x->item.nome, x->item.cognome, x->item.dataNascita.giorno, x->item.dataNascita.mese, x->item.dataNascita.anno, x->item.via, x->item.citta, x->item.cap);

    }
    fclose(fOut);
}