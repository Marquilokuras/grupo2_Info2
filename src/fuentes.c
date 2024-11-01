#include "../include/fuentes.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

void cargaFuentesEnergia(char *archivo, struct Node **head)
{
    struct Node *tail = NULL;
    char linea[MAX_LINE_LENGTH];

    FILE *fp = fopen(archivo, "r");

    if (!fp)
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    while (fgets(linea, MAX_LINE_LENGTH, fp))
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

        if (fscanf(fp, "%d,%[^,],%d,%d,%d,%d,%d,%d", &newNode->fuente.anio, newNode->fuente.unidad, &newNode->fuente.termica, &newNode->fuente.hidraulica, &newNode->fuente.nuclear, &newNode->fuente.renovable, &newNode->fuente.importacion, &newNode->fuente.energiaTotal) == 8)
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

void mostrarFuentesEnergia(struct Node *head)
{
    struct Node *newNode = head;

    printf("\nGeneración de energía por fuente:\n");
    printf("--------------------------------------------------------------------------------------------------------------\n");
    printf("%-6s | %-8s | %-10s | %-10s | %-10s | %-10s | %-12s | %-10s\n",
           "Año", "Unidad", "Térmica", "Hidráulica", "Nuclear", "Renovable", "Importación", "Total");
    printf("--------------------------------------------------------------------------------------------------------------\n");

    while (newNode != NULL)
    {
        printf("%-6d | %-8s | %-10d | %-10d | %-10d | %-10d | %-12d | %-10d\n", newNode->fuente.anio, newNode->fuente.unidad, newNode->fuente.termica, newNode->fuente.hidraulica, newNode->fuente.nuclear, newNode->fuente.renovable, newNode->fuente.importacion, newNode->fuente.energiaTotal);
        newNode = newNode->next;
    }
}

void calcularParticipacionFuente(struct Node *head)
{
    struct Node *temp = head;

    if (temp == NULL)
    {
        printf("No hay datos cargados. Primero cargue los datos con la opción 3.\n");
        return;
    }

    printf("\nParticipación de fuentes de energía por año:\n");
    printf("-------------------------------------------------------------------------\n");
    printf("%-6s | %-10s | %-10s | %-10s | %-10s | %-10s\n",
           "Año", "Térmica", "Hidráulica", "Nuclear", "Renovable", "Import.");
    printf("-------------------------------------------------------------------------\n");

    while (temp != NULL)
    {
        int total = temp->fuente.energiaTotal;
        if (total > 0)
        {
            float termica = (temp->fuente.termica / (float)total) * 100;
            float hidraulica = (temp->fuente.hidraulica / (float)total) * 100;
            float nuclear = (temp->fuente.nuclear / (float)total) * 100;
            float renovable = (temp->fuente.renovable / (float)total) * 100;
            float importacion = (temp->fuente.importacion / (float)total) * 100;
            int anio = temp->fuente.anio;
            printf("%-6d | %9.1f%% | %9.1f%% | %9.1f%% | %9.1f%% | %9.1f%%\n",
                   anio, termica, hidraulica, nuclear, renovable, importacion);
        }
        else
        {
            printf("%-6d |   N/A     |   N/A     |   N/A     |   N/A     |   N/A\n", temp->fuente.anio);
        }

        temp = temp->next;
    }

    printf("-------------------------------------------------------------------------\n");
}

void ordenarTotal(struct Node **headFuente)
{
    if (*headFuente == NULL)
        return;

    int swapped;
    struct Node *current;
    struct Node *last = NULL;

    do
    {
        swapped = 0;
        current = *headFuente;

        while (current->next != last)
        {
            if (current->fuente.energiaTotal < current->next->fuente.energiaTotal)
            {
                struct generacionFuente temp = current->fuente;
                current->fuente = current->next->fuente;
                current->next->fuente = temp;

                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}