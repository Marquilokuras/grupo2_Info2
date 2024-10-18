#ifndef CONSUMO_H
#define CONSUMO_H

#include "lista.h"

void mostrarConsumoEnergetico(char *archivo);
void calcularConsumoPorSector(char *archivo, struct node **head);

#endif