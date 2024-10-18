#include "consumo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void mostrarConsumoEnergetico(char *archivoConsumo) {
    FILE *archivo = fopen(archivoConsumo, "r");
    
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    
    char titulo_anio[20], titulo_residencial[20], titulo_comercial[20], titulo_industrial[30], titulo_unidad[15];
    char anio[10], residencial[10], comercial[10], industrial_comercial_grande[10], unidad_medida[10];
    
    fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n", 
           titulo_anio, titulo_residencial, titulo_comercial, titulo_industrial, titulo_unidad);
    
    printf("%-6s | %-12s | %-10s | %-25s | %-12s\n", 
           titulo_anio, titulo_residencial, titulo_comercial, titulo_industrial, titulo_unidad);
    printf("--------------------------------------------------------------------------\n");
    
    while (fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n", 
                  anio, residencial, comercial, industrial_comercial_grande, unidad_medida) != EOF) {
        printf("%-6s | %-12s | %-10s | %-25s | %-12s\n", 
               anio, residencial, comercial, industrial_comercial_grande, unidad_medida);
    }
    
    fclose(archivo);
}

void calcularConsumoPorSector(char *archivo, struct node **head) {
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        printf("Error al abrir el archivo\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int isFirstLine = 1;
    double consumoComercial = 0.0, consumoIndustrial = 0.0, consumoResidencial = 0.0;

    while (fgets(line, sizeof(line), fp)) {
        if (isFirstLine) {
            isFirstLine = 0;
            continue;
        }

        char residencial[10], comercial[10], industrialComercialGrande[10];

        if (sscanf(line, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n", residencial, comercial, industrialComercialGrande) == 3) {
            consumoResidencial += atof(residencial);
            consumoComercial += atof(comercial);
            consumoIndustrial += atof(industrialComercialGrande);
        } else {
            printf("Error al leer la línea: %s\n", line);
        }
    }

    insertar(head, "Residencial", consumoResidencial);
    insertar(head, "Comercial", consumoComercial);
    insertar(head, "Industrial/Comercial Grande", consumoIndustrial);

    fclose(fp);
    printf("Lectura de archivo completada\n");
}