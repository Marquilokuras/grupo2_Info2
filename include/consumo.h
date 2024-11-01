#ifndef CONSUMO_H
#define CONSUMO_H

#include "lista.h"

void cargaConsumoEnergetico(char *archivo, struct node **head);
void mostrarConsumoEnergetico(struct node *head);
void calcularConsumoPorSector(struct node **head);
void busquedaAnio(struct node *head);

#endif