#include <stdio.h>
#include "characters.h"
#include "inventory.h"
#include "string.h"
#include "stdlib.h"


int main() {

    sp_list list;
    list = listInitialize();
    sp_inventorySetW inventorySetW;
    inventorySetW = inventorySetInitialize();
    s_character TMP_character;
    int option, code;
    char prompt[LENSTRING];


    do {
        printf("\n------RPG Manager------\nScegli un opzione:\n[1] Lettura file personaggi\n[2] Lettura file ogetti\n[3] Aggiunta nuovo personaggio\n[4] Eliminazione di un personaggio\n[5] Aggiunta di ogetto ad un personaggio\n[6] Rimozione ogetto da un personaggio\n[7] Cerca personaggio con codice \n[0] Uscita\n\n");
        scanf(" %s",prompt);
        if((option = atoi(prompt)) == 0){
            option = 99;
        }
        switch (option) {
            case 0:
                printf("------Uscita------");
                return 0;
            case 1:
                printf("Digita il nome del file:\n");
                scanf("%s",prompt);
                if (fileRead(prompt, list)){
                    printf("Errore - File non trovato!\n");
                }else{
                    printf("Personaggi aggiunti!\n");
                }
                break;
            case 2:
                printf("Digita il nome del file:\n");
                scanf("%s",prompt);
                if (inventorySetRead(prompt, inventorySetW)){
                    printf("Errore - File non trovato!\n");
                }else{
                    printf("Ogetti aggiunti!\n");
                }
                break;
            case 3:

                printf("Inserisci il personaggio[codice nome classe vita mana attacco difesa magia sprint]:\n");
                scanf(" %s %s %s %d %d %d %d %d %d", prompt, TMP_character.name, TMP_character.class, &TMP_character.hp, &TMP_character.mp, &TMP_character.atk, &TMP_character.def, &TMP_character.mag, &TMP_character.spr);
                code = atoi(prompt);
                if(searchByCode(list, code) == NULL){
                    addHeadNode(list, TMP_character);
                    printf("Personaggio aggiunto correttamente\n");
                } else{
                    printf("Errore - Codice già in lista!\n");
                }
                break;
            case 4:
                printf("Digita il codice da eliminare:\n");
                scanf(" %d",prompt);
                code = atoi(prompt);
                if(deleteByCode(list,code)){
                    printf("Errore - Codice non trovato!\n");
                } else{
                    printf("Personaggio rimosso correttamente\n");
                }
                break;
            case 5:
                printf("Digita il nome dell'ogetto e il codice del personaggio[nome ogetto codice]:\n");
                scanf("%s %d", prompt, &code);
                addItem(inventorySetW,list,code, prompt);
                break;
            case 6:
                printf("Digita il nome dell'ogetto e il codice del personaggio[nome ogetto codice]:\n");
                scanf("%s %d", prompt, &code);
                removeItem(list,code,prompt);
                break;
            case 7:
                printf("Digita il codice del personaggio:\n");
                scanf("%s", prompt);
                if((code = atoi(prompt)) == 0){
                    printf("Errore - Codice non trovato!\n");
                } else{
                    searchByCode(list,code);
                }
                break;
            default:
                printf("Errore - Opzione non valida!\n");
                option = 99;
        }


    }while (1);
}
