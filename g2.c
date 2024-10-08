#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para usar sleep()

#define MAX_LINE_LENGTH 1024
#define MAX_SECTOR 50

// Estructura para almacenar los datos de consumo por sector
struct consumoSector{
	char sector[MAX_SECTOR];
	float consumo;
};

//Estructura del Nodo a utilizar en la Lista Doblemente Enlazada
struct node{
	struct consumoSector dato;
	struct node *next;
	struct node *prev;
};

// Estructura para almacenar los datos de la matriz energética
typedef struct {
	char fuente[MAX_SECTOR];
	float porcentaje;
} FuenteEnergia;


// Función para calcular el consumo energético por sector
void calcularConsumoPorSector(char *archivo) {
	FILE *fp = fopen(archivo, "r");
	if (!fp) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	/*char line[MAX_LINE_LENGTH];
	ConsumoSector sectores[10]; // Aquí se puede ajustar el número de sectores según los datos
	int i = 0;
	
	while (fgets(line, sizeof(line), fp)) {
		// Procesar la línea
		// Aquí se debe extraer el sector y el consumo energético
		sscanf(line, "%[^,],%f", sectores[i].sector, &sectores[i].consumo);
		i++;
	}
	
	// Mostrar los datos de consumo por sector
	for (int j = 0; j < i; j++) {
		printf("Sector: %s, Consumo: %.2f\n", sectores[j].sector, sectores[j].consumo);
	}*/
	
	fclose(fp);
}

// Función para calcular la participación de las fuentes de energía
void calcularParticipacionFuente(char *archivo) {
	FILE *fp = fopen(archivo, "r");
	if (!fp) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	/*char line[MAX_LINE_LENGTH];
	FuenteEnergia fuentes[10]; // Aquí se puede ajustar el número de fuentes según los datos
	int i = 0;
	
	while (fgets(line, sizeof(line), fp)) {
		// Procesar la línea
		// Aquí se debe extraer la fuente de energía y su porcentaje
		sscanf(line, "%[^,],%f", fuentes[i].fuente, &fuentes[i].porcentaje);
		i++;
	}
	
	// Mostrar las fuentes y su participación
	for (int j = 0; j < i; j++) {
		printf("Fuente: %s, Participación: %.2f%%\n", fuentes[j].fuente, fuentes[j].porcentaje);
	}
	*/
	
	fclose(fp);
}

// Menú principal
int main() {
	int opcMenu = 0;
	char archivoDatosConsumo[100] = "data/demandaEnergia.txt";  
	char archivoDatosGeneracion[100] = "data/generacionFuente.txt"; 
	//struct node* head = NULL;
	
	do {
		printf("\n*** MENU ACTIVIDAD ENERGÉTICA ***\n");
		printf("\n---------------------------------\n");
		printf("\n*** CONSUMO ENERGÉTICO ***\n");
		printf("1. Mostrar Consumo Energético\n");
		printf("2. Calcular consumo energético por sector\n");
		printf("\n*** FUENTES DE ENERGIA ***\n");
		printf("3. Mostrar Fuentes de Energía\n");
		printf("4. Calcular participación de fuentes de energía\n");
		printf("5. Salir\n");
		printf("\n---------------------------------\n");
		printf("Seleccione una opción: ");
		scanf("%d", &opcMenu);
		
		switch(opcMenu) {
			case 1:
			
				break;
			case 2:
				calcularConsumoPorSector(archivoDatosConsumo);
				break;
			case 3:
			
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
		
		sleep(1000);
		system("cls");
		
	} while (opcMenu != 5);
	
	return 0;
}
