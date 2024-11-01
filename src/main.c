#include "../include/menu.h"
#include "../include/lista.h"
#include <stdlib.h>

int main()
{
    struct node *headConsumo = NULL;
    struct Node *headFuente = NULL;

    mostrarMenu(&headConsumo, &headFuente);

    // Liberar memoria
    struct node *temp = NULL;
    while (headConsumo != NULL)
    {
        temp = headConsumo;
        headConsumo = headConsumo->next;
        free(temp);
    }

    struct Node *tempFuente = NULL;
    while (headFuente != NULL)
    {
        tempFuente = headFuente;
        headFuente = headFuente->next;
        free(tempFuente);
    }

    return 0;
}