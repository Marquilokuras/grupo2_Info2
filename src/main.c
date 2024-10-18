#include "menu.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct node* head = NULL;
    
    mostrarMenu(&head);
    
    // Liberar la memoria de la lista
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}