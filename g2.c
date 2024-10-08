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
	
	/*char line[MAX_LINE_LENGTH];
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
	}*/
	
	fclose(fp);
}

// Funci�n para calcular la participaci�n de las fuentes de energ�a
void calcularParticipacionFuente(char *archivo) {
	FILE *fp = fopen(archivo, "r");
	if (!fp) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	/*char line[MAX_LINE_LENGTH];
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
	*/
	
	fclose(fp);
}

// Men� principal
int main() {
	int opcMenu = 0;
	char archivoDatosConsumo[100] = "data/demandaEnergia.txt";  
	char archivoDatosGeneracion[100] = "data/generacionFuente.txt"; 
	//struct node* head = NULL;
	//
	do {
		printf("\n*** MENU ACTIVIDAD ENERG�TICA ***\n");
		printf("\n---------------------------------\n");
		printf("\n*** CONSUMO ENERG�TICO ***\n");
		printf("1. Mostrar Consumo Energ�tico\n");
		printf("2. Calcular consumo energ�tico por sector\n");
		printf("\n*** FUENTES DE ENERGIA ***\n");
		printf("3. Mostrar Fuentes de Energ�a\n");
		printf("4. Calcular participaci�n de fuentes de energ�a\n");
		printf("5. Salir\n");
		printf("\n---------------------------------\n");
		printf("Seleccione una opci�n: ");
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
				printf("\nOpci�n inv�lida\n");
				break;
		}
		
		sleep(1000);
		system("cls");
		
	} while (opcMenu != 5);
	
	return 0;
}
