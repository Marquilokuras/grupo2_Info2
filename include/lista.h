#ifndef LISTA_H
#define LISTA_H

#define MAX_SECTOR 50

// Estructura para almacenar datos de consumo por sector
struct consumoSector
{
    char unidad[MAX_SECTOR];
    int anio;
    int residencial;
    int comercial;
    int industrial;
};

struct generacionFuente
{
    int anio;
    char unidad[MAX_SECTOR];
    int termica;
    int hidraulica;
    int nuclear;
    int renovable;
    int importacion;
    int energiaTotal;
};

// Estructura para nodo de lista doblemente enlazada de consumo
struct node
{
    struct consumoSector dato;
    struct node *next;
    struct node *prev;
};

// Estructura para nodo de lista doblemente enlazada de fuentes
struct Node
{
    struct generacionFuente fuente;
    struct Node *next;
    struct Node *prev;
};

#endif