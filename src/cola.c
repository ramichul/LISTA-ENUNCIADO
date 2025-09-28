#include "lista.h"
#include "cola.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct cola {
	lista_t *lista;
};

bool cola_esta_vacia(cola_t *cola)
{
	if (cola == NULL) {
		return true;
	}

	return cola_cantidad(cola) == 0;
}

cola_t *cola_crear()
{
	cola_t *nueva_cola = malloc(sizeof(cola_t));
	if (nueva_cola == NULL) {
		return NULL;
	}

	nueva_cola->lista = lista_crear();
	if (nueva_cola->lista == NULL) {
		free(nueva_cola);
		return NULL;
	}

	return nueva_cola;
}

bool cola_encolar(cola_t *cola, void *elemento)
{
	if (cola == NULL) {
		return false;
	}

	return lista_agregar(cola->lista, elemento);
}

void *cola_desencolar(cola_t *cola)
{
	if (cola == NULL) {
		return NULL;
	}

	return lista_eliminar_elemento(cola->lista, 0);
}

void *cola_ver_primero(cola_t *cola)
{
	if (cola == NULL) {
		return NULL;
	}
	if (cola_cantidad(cola) == 0) {
		return NULL;
	}

	return lista_buscar_elemento(cola->lista, 0);
}

size_t cola_cantidad(cola_t *cola)
{
	if (cola == NULL) {
		return 0;
	}

	return lista_cantidad(cola->lista);
}

void cola_destruir(cola_t *cola)
{
	if (cola == NULL) {
		return;
	}

	while (!cola_esta_vacia(cola)) {
		cola_desencolar(cola);
	}
	free(cola->lista);
	free(cola);
}