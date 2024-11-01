#include "../include/menu.h"
#include "../include/consumo.h"
#include "../include/fuentes.h"
#include <stdio.h>

void mostrarMenu(struct node **headConsumo, struct Node **headFuente)
{
    int opcMenu = 0;
    char archivoDatosConsumo[100] = "data/demandaEnergia.txt";
    char archivoDatosGeneracion[100] = "data/generacionFuente.txt";

    cargaConsumoEnergetico(archivoDatosConsumo, headConsumo);
    cargaFuentesEnergia(archivoDatosGeneracion, headFuente);

    do
    {
        printf("\n** MENU ACTIVIDAD ENERGETICA **\n");
        printf("\n---------------------------------\n");
        printf("\n** CONSUMO ENERGETICO **\n");
        printf("1. Mostrar Consumo Energetico\n");
        printf("2. Calculo del Consumo Energético por Sector\n");
        printf("3. Busqueda por Año\n");
        printf("\n** FUENTES DE ENERGIA **\n");
        printf("4. Mostrar Fuentes de Energia\n");
        printf("5. Calcular de Participación de Fuentes de Energia\n");
        printf("6. Ordenar por Total de Fuente de Energia\n");
        printf("7. Salir\n");
        printf("\n---------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcMenu);

        switch (opcMenu)
        {
        case 1:
            mostrarConsumoEnergetico(*headConsumo);
            break;
        case 2:
            calcularConsumoPorSector(headConsumo);
            break;
        case 3:
            busquedaAnio(*headConsumo);
            break;
        case 4:
            cargaFuentesEnergia(archivoDatosGeneracion, headFuente);
            mostrarFuentesEnergia(*headFuente);
            break;
        case 5:
            calcularParticipacionFuente(*headFuente);
            break;
        case 6:
            ordenarTotal(headFuente);
            mostrarFuentesEnergia(*headFuente);
            break;
        case 7:
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpción inválida\n");
            break;
        }
    } while (opcMenu != 7);
}