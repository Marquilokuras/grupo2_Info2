#include "fuentes.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SECTOR 50

void mostrarFuentesEnergia(char *archivoFuente) {
    FILE *archivo = fopen(archivoFuente, "r");
    
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    
    char titulo_anio[20], titulo_unidad[20], titulo_energia_termica[20], titulo_energia_hidraulica[30], titulo_energia_nuclear[15],titulo_energia_renovable[15],titulo_importacion[15],titulo_energia_total[20];
    char anio[10], unidad[10], energiaTermica[10], energiaHidraulica[10], energiaNuclear[10],energiaRenovable[10],importacion[10],energiaTotal[10];
    
    fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n",
           titulo_anio, titulo_unidad, titulo_energia_termica, titulo_energia_hidraulica, titulo_energia_nuclear, titulo_energia_renovable, titulo_importacion, titulo_energia_total);
    
    printf("Anio  | Unidad     | Energia Termica | Energia Hidraulica  | Energia Nuclear   | Energia Renovable  | Importacion   | Energia Total\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    
    while (fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n",
                  anio, unidad, energiaTermica, energiaHidraulica, energiaNuclear, energiaRenovable, importacion, energiaTotal) != EOF) {
        
        printf("%-6s | %-10s | %-15s | %-18s | %-16s | %-17s | %-13s | %-12s\n",
               anio, unidad, energiaTermica, energiaHidraulica, energiaNuclear, energiaRenovable, importacion, energiaTotal);
    }
    
    fclose(archivo);
}

void calcularParticipacionFuente(char *archivo) {
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        printf("Error al abrir el archivo\n");
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    int isFirstLine = 1;
    
    while (fgets(line, sizeof(line), fp)) {
        if (isFirstLine) {
            isFirstLine = 0;
            continue;
        }
        
        char fuente[MAX_SECTOR];
        float porcentaje;
        sscanf(line, "%[^;];%f", fuente, &porcentaje);
        
        printf("Fuente: %-20s Participación: %.2f%%\n", fuente, porcentaje);
    }
    
    fclose(fp);
}