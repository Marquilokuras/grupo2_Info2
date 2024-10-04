#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_SECTOR 50

// Estructura para almacenar los datos de consumo por sector
typedef struct {
	char sector[MAX_SECTOR];
	float consumo;
} ConsumoSector;

// Estructura para almacenar los datos de la matriz energ�tica
typedef struct {
	char fuente[MAX_SECTOR];
	float porcentaje;
} FuenteEnergia;

// Funci�n para calcular el consumo energ�tico por sector
void calcularConsumoPorSector(char *archivo) {
	FILE *fp = fopen(archivo, "r");
	if (!fp) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	char line[MAX_LINE_LENGTH];
	ConsumoSector sectores[10]; // Aqu� se puede ajustar el n�mero de sectores seg�n los datos
	int i = 0;
	
	while (fgets(line, sizeof(line), fp)) {
		// Procesar la l�nea
		// Aqu� se debe extraer el sector y el consumo energ�tico
		sscanf(line, "%[^,],%f", sectores[i].sector, &sectores[i].consumo);
		i++;
	}
	
	// Mostrar los datos de consumo por sector
	for (int j = 0; j < i; j++) {
		printf("Sector: %s, Consumo: %.2f\n", sectores[j].sector, sectores[j].consumo);
	}
	
	fclose(fp);
}

// Funci�n para calcular la participaci�n de las fuentes de energ�a
void calcularParticipacionFuente(char *archivo) {
	FILE *fp = fopen(archivo, "r");
	if (!fp) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	char line[MAX_LINE_LENGTH];
	FuenteEnergia fuentes[10]; // Aqu� se puede ajustar el n�mero de fuentes seg�n los datos
	int i = 0;
	
	while (fgets(line, sizeof(line), fp)) {
		// Procesar la l�nea
		// Aqu� se debe extraer la fuente de energ�a y su porcentaje
		sscanf(line, "%[^,],%f", fuentes[i].fuente, &fuentes[i].porcentaje);
		i++;
	}
	
	// Mostrar las fuentes y su participaci�n
	for (int j = 0; j < i; j++) {
		printf("Fuente: %s, Participaci�n: %.2f%%\n", fuentes[j].fuente, fuentes[j].porcentaje);
	}
	
	fclose(fp);
}

// Men� principal
int main() {
	int opcMenu = 0;
	char archivoDatosConsumo[100] = "data/demandaEnergia.txt"; 
	char archivoDatosGeneracion[100] = "data/generacionFuente.txt"; 
	
	do {
		printf("Seleccione una opci�n:\n");
		printf("1. Calcular consumo energ�tico por sector\n");
		printf("2. Calcular participaci�n de fuentes de energ�a\n");
		printf("3. Salir\n");
		scanf("%d", &opcMenu);
		
		switch(opcMenu) {
		case 1:
			calcularConsumoPorSector(archivoDatosConsumo);
			break;
		case 2:
			calcularParticipacionFuente(archivoDatosGeneracion);
			break;
		case 3:
			printf("\nSaliendo del programa...\n");
			break;
		default:
			printf("\nOpci�n no v�lida\n");
			break;
		}
	} while (opcMenu != 3);
	
	return 0;
}
