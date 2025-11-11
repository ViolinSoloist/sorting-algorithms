#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

#define MENOR_INT -2147483648

typedef struct no_ NO;

struct no_ {
	int item;
	NO* next;
};

struct queue_ {
	NO* inicio;
	NO* fim;
	int tamanho;
};

QUEUE* q_new(void) {
	QUEUE* fila = (QUEUE*)malloc(sizeof(QUEUE));

	if (fila != NULL) {
		fila->inicio = NULL;
		fila->fim = NULL;
		fila->tamanho = 0;
	} else{
		fprintf(stderr, "ERRO: alocação para fila falhou.\n");
	}

	return fila;
}

bool q_isfull(QUEUE* fila) {
	if (fila == NULL) return false;

	NO* noaux = (NO*)malloc(sizeof(NO));
	if (noaux == NULL) {
		return true;
	}

	free(noaux);
	return false;
}

bool q_isempty(QUEUE* fila) {
	if (fila == NULL) return true;
	if (fila->tamanho == 0) return true;
	return false;
}

bool q_insert(QUEUE* fila, int item) {

	// verificação das condições para poder inserir.
	if (fila == NULL) {
		fprintf(stderr, "ERRO: Fila inválida.\n");
		return false;
	}

	if (q_isfull(fila)) {
		fprintf(stderr, "ERRO: Fila cheia.\n");
		return false;
	}

	// alocação do NÓ
	NO* no = (NO*)malloc(sizeof(NO));

	if (no != NULL) {
		no->item = item;
		no->next = NULL;
	} else{
		fprintf(stderr, "ERRO: alocação para no_ falhou.\n");
		return false;
	}

	// redirecionamento dos ponteiros
	if (fila->tamanho == 0) {
		fila->inicio = no;
	} else{
		fila->fim->next = no;
	}

	fila->fim = no;
	fila->tamanho++;

	return true;
}

int q_rm(QUEUE* fila) {
	if (fila == NULL || q_isempty(fila)) return MENOR_INT;

	int it = fila->inicio->item;
	// Remove o nó do início da fila e atualiza os ponteiros
	NO* old_ini = fila->inicio;
	fila->inicio = old_ini->next;
	old_ini->next = NULL;
	free(old_ini);

	if (fila->inicio == NULL) {
		fila->fim = NULL;
	}

	fila->tamanho--;

	return it;
}

bool q_del(QUEUE** fila) {
	if (fila == NULL) return false;

	while(!q_isempty(*fila)) {
		NO* noaux = (*fila)->inicio->next;
		(*fila)->inicio->next = NULL;
		free((*fila)->inicio);
		(*fila)->inicio = noaux;
		(*fila)->tamanho--;
	}
	(*fila)->fim = NULL;

	return true;
}

int q_size(QUEUE* fila)
{
    if (fila == NULL || q_isempty(fila)) return MENOR_INT;

    return (fila->tamanho);
}

int q_front(QUEUE* fila)
{
	if (fila == NULL || q_isempty(fila)) return MENOR_INT;

    return (fila->inicio->item);
}




