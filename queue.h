#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#define TAM 10000

typedef struct queue_ QUEUE;

// se tiver um erro, a maioria das funções retorna INT_MIN

QUEUE* q_new();
bool q_isfull(QUEUE* fila);
bool q_isempty(QUEUE* fila);
bool q_insert(QUEUE* fila, int item);
int q_rm(QUEUE* fila);
int q_size(QUEUE* fila);

// retorna o próximo item a sair (frente da fila, primeiro que chegou)
int q_front(QUEUE* fila);

bool q_del(QUEUE** fila);

#endif // QUEUE_H_INCLUDED
