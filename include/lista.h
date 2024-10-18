#ifndef LISTA_H
#define LISTA_H

#define MAX_SECTOR 50

struct consumoSector {
    char sector[MAX_SECTOR];
    int anio;
    int residencial;
    int comercial;
    int industrial;
    char unidadMedida[5];
};

struct node {
    struct consumoSector dato;
    struct node *next;
    struct node *prev;
};

void insertar(struct node **head, char *sector, float consumo);

#endif