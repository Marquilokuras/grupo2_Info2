#ifndef FUENTES_H
#define FUENTES_H

#include "lista.h"

void cargaFuentesEnergia(char *archivo, struct Node **head);
void mostrarFuentesEnergia(struct Node *head);
void calcularParticipacionFuente(struct Node *head);
void ordenarTotal(struct Node **headFuente);

#endif