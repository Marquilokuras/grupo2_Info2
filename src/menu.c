#include "menu.h"
#include "consumo.h"
#include "fuentes.h"
#include <stdio.h>

void mostrarMenu(struct node** head) {
    int opcMenu = 0;
    char archivoDatosConsumo[100] = "data/demandaEnergia.txt";
    char archivoDatosGeneracion[100] = "data/generacionFuente.txt";
    
    do {
        printf("\n*** MENU ACTIVIDAD ENERGETICA ***\n");
        printf("\n---------------------------------\n");
        printf("\n*** CONSUMO ENERGETICO ***\n");
        printf("1. Mostrar Consumo Energetico\n");
        printf("2. Calcular consumo energetico por sector\n");
        printf("\n*** FUENTES DE ENERGIA ***\n");
        printf("3. Mostrar Fuentes de Energia\n");
        printf("4. Calcular participacion de fuentes de energia\n");
        printf("5. Salir\n");
        printf("\n---------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcMenu);
        printf("\n");
        switch(opcMenu) {
        case 1:
            mostrarConsumoEnergetico(archivoDatosConsumo);
            break;
        case 2:
            calcularConsumoPorSector(archivoDatosConsumo, head);
            break;
        case 3:
            mostrarFuentesEnergia(archivoDatosGeneracion);
            break;
        case 4:
            calcularParticipacionFuente(archivoDatosGeneracion);
            break;
        case 5:
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpción inválida\n");
            break;
        }
    } while (opcMenu != 5);
}