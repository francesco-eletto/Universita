#include <stdio.h>
#include "characters.h"
#include "inventory.h"

int main() {

    sp_list list;

    list = listInitialize();
    fileRead("../pg.txt", list);
    deleteByCode(list,9);

    return 0;
}
