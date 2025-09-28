#include "lista.h"
#include "pila.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct pila {
	lista_t *lista;
};

bool pila_esta_vacia(pila_t *pila)
{
	if (pila == NULL) {
		return true;
	}

	return pila_cantidad(pila) == 0;
}

pila_t *pila_crear()
{
	pila_t *nueva_pila = malloc(sizeof(pila_t));
	if (nueva_pila == NULL) {
		return NULL;
	}

	nueva_pila->lista = lista_crear();
	if (nueva_pila->lista == NULL) {
		free(nueva_pila);
		return NULL;
	}

	return nueva_pila;
}

bool pila_apilar(pila_t *pila, void *elemento)
{
	if (pila == NULL) {
		return false;
	}
	if (pila_cantidad(pila) == 0) {
		return lista_agregar(pila->lista, elemento);
	}
	return lista_insertar(pila->lista, elemento, 0);
}

void *pila_desapilar(pila_t *pila)
{
	if (pila == NULL) {
		return NULL;
	}

	return lista_eliminar_elemento(pila->lista, 0);
}

void *pila_ver_primero(pila_t *pila)
{
	if (pila == NULL) {
		return NULL;
	}
	if (pila_cantidad(pila) == 0) {
		return NULL;
	}

	return lista_buscar_elemento(pila->lista, 0);
}

size_t pila_cantidad(pila_t *pila)
{
	if (pila == NULL) {
		return 0;
	}

	return lista_cantidad(pila->lista);
}

void pila_destruir(pila_t *pila)
{
	if (pila == NULL) {
		return;
	}

	while (!pila_esta_vacia(pila)) {
		pila_desapilar(pila);
	}
	free(pila->lista);
	free(pila);
}