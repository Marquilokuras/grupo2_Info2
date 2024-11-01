#include "../include/consumo.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

void cargaConsumoEnergetico(char *archivo, struct node **head)
{
    struct node *tail = NULL;
    char linea[MAX_LINE_LENGTH];

    FILE *fp = fopen(archivo, "r");

    if (fp == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Omitir el encabezado
    fgets(linea, MAX_LINE_LENGTH, fp);

    while (fgets(linea, MAX_LINE_LENGTH, fp))
    {
        struct node *newNode = (struct node *)malloc(sizeof(struct node));

        if (sscanf(linea, "%d,%d,%d,%d,%s", &newNode->dato.anio, &newNode->dato.residencial, &newNode->dato.comercial, &newNode->dato.industrial, newNode->dato.unidad) == 5)
        {
            newNode->next = NULL;
            newNode->prev = tail;

            if (tail)
            {
                tail->next = newNode;
            }
            else
            {
                *head = newNode;
            }
            tail = newNode;
        }
        else
        {
            free(newNode);
        }
    }

    fclose(fp);
}

void mostrarConsumoEnergetico(struct node *head)
{
    struct node *temp = head;

    printf("\n");
    printf("%-6s | %-12s | %-10s | %-12s | %-6s\n",
           "Año", "Residencial", "Comercial", "Industrial", "Unidad");
    printf("----------------------------------------------------------\n");

    while (temp != NULL)
    {
        printf("%-6d | %-12d | %-10d | %-12d | %-6s\n", temp->dato.anio, temp->dato.residencial, temp->dato.comercial, temp->dato.industrial, temp->dato.unidad);
        temp = temp->next;
    }
}

void calcularConsumoPorSector(struct node **head)
{
    struct node *current = *head;
    int totalResidencial = 0;
    int totalComercial = 0;
    int totalIndustrial = 0;

    while (current != NULL)
    {
        totalResidencial += current->dato.residencial;
        totalComercial += current->dato.comercial;
        totalIndustrial += current->dato.industrial;

        current = current->next;
    }

    printf("\n");
    printf("Consumo total por sector:\n");
    printf("Residencial: %d GWh\n", totalResidencial);
    printf("Comercial: %d GWh\n", totalComercial);
    printf("Industrial: %d GWh\n", totalIndustrial);
}

void busquedaAnio(struct node *head)
{
    struct node *temp = head;
    int anioBusqueda = 0, encontrado = 0;

    printf("\nIngrese año a buscar: ");
    scanf("%d", &anioBusqueda);

    while (temp != NULL)
    {
        if (temp->dato.anio == anioBusqueda)
        {
            printf("\n");
            printf("%-6s | %-12s | %-10s | %-12s | %-6s\n",
                   "Año", "Residencial", "Comercial", "Industrial", "Unidad");
            printf("----------------------------------------------------------\n");
            printf("%-6d | %-12d | %-10d | %-12d | %-6s\n", temp->dato.anio, temp->dato.residencial, temp->dato.comercial, temp->dato.industrial, temp->dato.unidad);
            encontrado++;
        }
        temp = temp->next;
    }
    if (encontrado == 0)
    {
        printf("\nAño Solicitado Inexistente\n");
    }
}