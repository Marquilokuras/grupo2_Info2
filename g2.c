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

// Declaraci�n de funciones
void insertar(struct node **head, char *sector, float consumo);
void mostrarConsumoEnergetico(char *archivo);
void calcularConsumoPorSector(char *archivo, struct node **head);
void mostrarFuentesEnergia(char *archivo);

void calcularParticipacionFuente(char *archivo);
void mostrarMenu();

// Funci�n para mostrar la lista doblemente enlazada
void mostrarConsumoEnergetico(char *archivoConsumo) {
	
	FILE *archivo = fopen(archivoConsumo, "r");
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	// Variables para almacenar cada valor
	
	char titulo_anio[20], titulo_residencial[20], titulo_comercial[20], titulo_industrial[30], titulo_unidad[15];
	char anio[10], residencial[10], comercial[10], industrial_comercial_grande[10], unidad_medida[10];
	
	// Leer la primera l�nea (t�tulos)
	fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n", 
		   titulo_anio, titulo_residencial, titulo_comercial, titulo_industrial, titulo_unidad);
	
	// Imprimir los t�tulos formateados
	printf("%-6s | %-12s | %-10s | %-25s | %-12s\n", 
		   titulo_anio, titulo_residencial, titulo_comercial, titulo_industrial, titulo_unidad);
	printf("--------------------------------------------------------------------------\n");
	
	// Leer y mostrar los valores (segunda l�nea y siguientes)
	while (fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n", 
				  anio, residencial, comercial, industrial_comercial_grande, unidad_medida) != EOF) {
		// Imprimir los valores le�dos
		printf("%-6s | %-12s | %-10s | %-25s | %-12s\n", 
			   anio, residencial, comercial, industrial_comercial_grande, unidad_medida);
	}
	
	// Cerrar el archivo
	fclose(archivo);
	
}

void insertar(struct node **head, char *sector, float consumo) {
    struct node *nuevo_nodo = (struct node*)malloc(sizeof(struct node));
    
    if (!nuevo_nodo) {
        printf("Error al asignar memoria\n");
        return;
    }

    // Inicializar el nuevo nodo
    strcpy(nuevo_nodo->dato.sector, sector);
    nuevo_nodo->dato.residencial = (strcmp(sector, "Residencial") == 0) ? consumo : 0.0;
    nuevo_nodo->dato.comercial = (strcmp(sector, "Comercial") == 0) ? consumo : 0.0;
    nuevo_nodo->dato.industrial = (strcmp(sector, "Industrial/Comercial Grande") == 0) ? consumo : 0.0;

    nuevo_nodo->next = NULL;
    nuevo_nodo->prev = NULL;

    // Verificar si la lista está vacía
    if (*head == NULL) {
        *head = nuevo_nodo;
    } else {
        struct node *temp = *head;
        struct node *prev = NULL;

        // Buscar si el sector ya existe
        while (temp != NULL) {
            // Si el sector ya existe, actualizar el consumo
            if (strcmp(temp->dato.sector, sector) == 0) {
                if (strcmp(sector, "Residencial") == 0) {
                    temp->dato.residencial += consumo;  // Sumar al consumo existente
                } else if (strcmp(sector, "Comercial") == 0) {
                    temp->dato.comercial += consumo;  // Sumar al consumo existente
                } else if (strcmp(sector, "Industrial/Comercial Grande") == 0) {
                    temp->dato.industrial += consumo;  // Sumar al consumo existente
                }
                free(nuevo_nodo);  // Liberar la memoria del nuevo nodo
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        // Si el sector no existe, agregar el nuevo nodo al final de la lista
        prev->next = nuevo_nodo;
        nuevo_nodo->prev = prev;
    }

    printf("Nodo insertado: %s - Consumo: %.2f\n", sector, consumo);
}

// Funci�n para calcular el consumo energ�tico por sector (lectura desde archivo)
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

void mostrarFuentesEnergia(char *archivoFuente) {
	
	FILE *archivo = fopen(archivoFuente, "r");
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	// Variables para almacenar cada valor
	char titulo_anio[20], titulo_unidad[20], titulo_energia_termica[20], titulo_energia_hidraulica[30], titulo_energia_nuclear[15],titulo_energia_renovable[15],titulo_importacion[15],titulo_energia_total[20];
	char anio[10], unidad[10], energiaTermica[10], energiaHidraulica[10], energiaNuclear[10],energiaRenovable[10],importacion[10],energiaTotal[10];
	
	// Leer la primera l�nea (t�tulos)
	fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n",
		   titulo_anio, titulo_unidad, titulo_energia_termica, titulo_energia_hidraulica, titulo_energia_nuclear, titulo_energia_renovable, titulo_importacion, titulo_energia_total);
	
	
	// Imprimir los t�tulos formateados
	printf("Anio  | Unidad     | Energia Termica | Energia Hidraulica  | Energia Nuclear   | Energia Renovable  | Importacion   | Energia Total\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------\n");
	
	// Leer y mostrar los valores (segunda l�nea y siguientes)
	while (fscanf(archivo, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";\"%[^\"]\"\n",
				  anio, unidad, energiaTermica, energiaHidraulica, energiaNuclear, energiaRenovable, importacion, energiaTotal) != EOF) {
		
		printf("%-6s | %-10s | %-15s | %-18s | %-16s | %-17s | %-13s | %-12s\n",
			   anio, unidad, energiaTermica, energiaHidraulica, energiaNuclear, energiaRenovable, importacion, energiaTotal);
	}
	
	// Cerrar el archivo
	fclose(archivo);
	
}

// Funci�n para calcular la participaci�n de las fuentes de energ�a
void calcularParticipacionFuente(char *archivo) {
	FILE *fp = fopen(archivo, "r");
	if (!fp) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	// Ejemplo: Procesar el archivo de fuentes energ�ticas
	// Aqu� deber�as adaptar el procesamiento seg�n la estructura de tu archivo
	char line[MAX_LINE_LENGTH];
	int isFirstLine = 1;
	
	while (fgets(line, sizeof(line), fp)) {
		// Ignorar la primera l�nea (encabezado)
		if (isFirstLine) {
			isFirstLine = 0;
			continue;
		}
		
		// Extraer los datos de cada l�nea
		char fuente[MAX_SECTOR];
		float porcentaje;
		sscanf(line, "%[^;];%f", fuente, &porcentaje);
		
		// Mostrar los datos de la fuente de energ�a
		printf("Fuente: %-20s Participaci�n: %.2f%%\n", fuente, porcentaje);
	}
	
	fclose(fp);
}

// Men� principal
void mostrarMenu(struct node** head) {
	int opcMenu = 0;
	char archivoDatosConsumo[100] = "data/demandaEnergia.txt";  // Archivo de datos de consumo energ�tico
	char archivoDatosGeneracion[100] = "data/generacionFuente.txt";  // Archivo de fuentes de energ�a
	
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
			// Mostrar fuentes de energ�a
			mostrarFuentesEnergia(archivoDatosGeneracion);
			break;
		case 4:
			// Calcular participaci�n de fuentes de energ�a
			calcularParticipacionFuente(archivoDatosGeneracion);
			break;
		case 5:
			printf("\nSaliendo del programa...\n");
			break;
		default:
			printf("\nOpci�n inv�lida\n");
			break;
		}
		
		//sleep(1); // Esperar 1 segundo antes de limpiar la pantalla
		//system("clear"); // Limpiar la pantalla (usar "cls" en Windows)
		
	} while (opcMenu != 5);
}


int main() {
	struct node* head = NULL;
	
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