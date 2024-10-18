#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertar(struct node **head, char *sector, float consumo) {
    struct node *nuevo_nodo = (struct node*)malloc(sizeof(struct node));
    
    if (!nuevo_nodo) {
        printf("Error al asignar memoria\n");
        return;
    }

    strcpy(nuevo_nodo->dato.sector, sector);
    nuevo_nodo->dato.residencial = (strcmp(sector, "Residencial") == 0) ? consumo : 0.0;
    nuevo_nodo->dato.comercial = (strcmp(sector, "Comercial") == 0) ? consumo : 0.0;
    nuevo_nodo->dato.industrial = (strcmp(sector, "Industrial/Comercial Grande") == 0) ? consumo : 0.0;

    nuevo_nodo->next = NULL;
    nuevo_nodo->prev = NULL;

    if (*head == NULL) {
        *head = nuevo_nodo;
    } else {
        struct node *temp = *head;
        struct node *prev = NULL;

        while (temp != NULL) {
            if (strcmp(temp->dato.sector, sector) == 0) {
                if (strcmp(sector, "Residencial") == 0) {
                    temp->dato.residencial += consumo;
                } else if (strcmp(sector, "Comercial") == 0) {
                    temp->dato.comercial += consumo;
                } else if (strcmp(sector, "Industrial/Comercial Grande") == 0) {
                    temp->dato.industrial += consumo;
                }
                free(nuevo_nodo);
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        prev->next = nuevo_nodo;
        nuevo_nodo->prev = prev;
    }

    printf("Nodo insertado: %s - Consumo: %.2f\n", sector, consumo);
}