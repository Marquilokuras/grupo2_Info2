#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para usar sleep()

#define MAX_LINE_LENGTH 1024
#define MAX_SECTOR 50

// Estructura para almacenar los datos de consumo por sector
struct consumoSector{
	char sector[MAX_SECTOR];
	int anio;
	int residencial;
	int comercial;
	int industrial;
	char unidadMedida[5];
};

// Estructura para almacenar los datos de participacion de fuentes de energia
struct fuentesEnergia{
	char sector[MAX_SECTOR];
	int anio;
	char unidadMedida[5];
	int energiaTermica;
	int energiaHidraulica;
	int energiaNuclear;
	int energiaRenovable;
	int importacion;
	int energiaTotal;
};

// Estructura del Nodo a utilizar en la Lista Doblemente Enlazada
struct node{
	struct consumoSector dato;
	struct node *next;
	struct node *prev;
};

// Declaración de funciones
void insertar(struct node **head, char *sector, float consumo);
void mostrarConsumoEnergetico(struct node *head);
void calcularConsumoPorSector(char *archivo, struct node **head);
void calcularParticipacionFuente(char *archivo);
void mostrarMenu();

// Función para insertar en la lista doblemente enlazada
void insertar(struct node **head, char *sector, float consumo) {
	struct node *nuevo_nodo = (struct node*) malloc(sizeof(struct node));
	strcpy(nuevo_nodo->dato.sector, sector);
	nuevo_nodo->dato.consumo = consumo;
	nuevo_nodo->next = NULL;
	nuevo_nodo->prev = NULL;
	
	if (*head == NULL) {
		*head = nuevo_nodo;
	} else {
		struct node *temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nuevo_nodo;
		nuevo_nodo->prev = temp;
	}
}

// Función para mostrar la lista doblemente enlazada
void mostrarConsumoEnergetico(struct node *head) {
	
	FILE *archivo = fopen("data/demandaEnergia.txt", "r");
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	// Variables para almacenar cada valor
	
	char titulo_anio[20], titulo_residencial[20], titulo_comercial[20], titulo_industrial[30], titulo_unidad[15];
	char anio[10], residencial[10], comercial[10], industrial_comercial_grande[10], unidad_medida[10];
	
	// Leer la primera línea (títulos)
	fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n", 
		   titulo_anio, titulo_residencial, titulo_comercial, titulo_industrial, titulo_unidad);
	
	// Imprimir los títulos formateados
	printf("%-6s | %-12s | %-10s | %-25s | %-12s\n", 
		   titulo_anio, titulo_residencial, titulo_comercial, titulo_industrial, titulo_unidad);
	printf("--------------------------------------------------------------------------\n");
	
	// Leer y mostrar los valores (segunda línea y siguientes)
	while (fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n", 
				  anio, residencial, comercial, industrial_comercial_grande, unidad_medida) != EOF) {
		// Imprimir los valores leídos
		printf("%-6s | %-12s | %-10s | %-25s | %-12s\n", 
			   anio, residencial, comercial, industrial_comercial_grande, unidad_medida);
	}
	
	// Cerrar el archivo
	fclose(archivo);
	
	/*if (head == NULL) {
		printf("No hay datos de consumo disponibles.\n");
		return;
	}
	
	
	printf("\nConsumo Energético por Sector:\n");
	printf("%-20s %-10s\n", "Sector", "Consumo");
	printf("----------------------------\n");
	while (head != NULL) {
		printf("%-20s %-10.2f GWh\n", head->dato.sector, head->dato.consumo);
		head = head->next;
	}*/
	
}

// Función para calcular el consumo energético por sector (lectura desde archivo)
void calcularConsumoPorSector(char *archivo, struct node **head) {
	FILE *fp = fopen(archivo, "r");
	if (!fp) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	char line[MAX_LINE_LENGTH];
	int isFirstLine = 1;
	
	while (fgets(line, sizeof(line), fp)) {
		// Ignorar la primera línea (encabezado)
		if (isFirstLine) {
			isFirstLine = 0;
			continue;
		}
		
		// Extraer los datos de cada línea
		float consumo_residencial, consumo_comercial, consumo_industrial;
		sscanf(line, "%*[^;];%f;%f;%f;%*s", &consumo_residencial, &consumo_comercial, &consumo_industrial);
		
		// Insertar en la lista por sector
		insertar(head, "Residencial", consumo_residencial);
		insertar(head, "Comercial", consumo_comercial);
		insertar(head, "Industrial/Comercial Grande", consumo_industrial);
	}
	
	fclose(fp);
}

// Función para calcular la participación de las fuentes de energía
void calcularParticipacionFuente(char *archivo) {
	FILE *fp = fopen(archivo, "r");
	if (!fp) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	// Ejemplo: Procesar el archivo de fuentes energéticas
	// Aquí deberías adaptar el procesamiento según la estructura de tu archivo
	char line[MAX_LINE_LENGTH];
	int isFirstLine = 1;
	
	while (fgets(line, sizeof(line), fp)) {
		// Ignorar la primera línea (encabezado)
		if (isFirstLine) {
			isFirstLine = 0;
			continue;
		}
		
		// Extraer los datos de cada línea
		char fuente[MAX_SECTOR];
		float porcentaje;
		sscanf(line, "%[^;];%f", fuente, &porcentaje);
		
		// Mostrar los datos de la fuente de energía
		printf("Fuente: %-20s Participación: %.2f%%\n", fuente, porcentaje);
	}
	
	fclose(fp);
}

// Menú principal
void mostrarMenu(struct node** head) {
	int opcMenu = 0;
	char archivoDatosConsumo[100] = "data/demandaEnergia.txt";  // Archivo de datos de consumo energético
	char archivoDatosGeneracion[100] = "data/generacionFuente.txt";  // Archivo de fuentes de energía
	
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
		
		switch(opcMenu) {
		case 1:
			mostrarConsumoEnergetico(*head);
			break;
		case 2:
			calcularConsumoPorSector(archivoDatosConsumo, head);
			break;
		case 3:
			// Mostrar fuentes de energía
			calcularParticipacionFuente(archivoDatosGeneracion);
			break;
		case 4:
			// Calcular participación de fuentes de energía
			calcularParticipacionFuente(archivoDatosGeneracion);
			break;
		case 5:
			printf("\nSaliendo del programa...\n");
			break;
		default:
			printf("\nOpción inválida\n");
			break;
		}
		
		//sleep(1); // Esperar 1 segundo antes de limpiar la pantalla
		//system("clear"); // Limpiar la pantalla (usar "cls" en Windows)
		
	} while (opcMenu != 5);
}


int main() {
	struct node* head = NULL;
	// Cargar el consumo desde el archivo al inicio
	calcularConsumoPorSector("data/demandaEnergia.txt", &head);
	mostrarMenu(&head);
	
	// Liberar la memoria de la lista
	struct node *temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
	
	return 0;
}
