#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct nodo {
	void *contenido;
	struct nodo *siguiente_nodo;
} nodo_t;

struct lista {
	nodo_t *inicio;
	nodo_t *fin;
	size_t cantidad_nodos;
};

struct lista_iterador {
	nodo_t *actual;
	lista_t *lista;
};

void inicializar_nodo(nodo_t *nodo, void *contenido, nodo_t *siguiente_nodo)
{
	nodo->contenido = contenido;
	nodo->siguiente_nodo = siguiente_nodo;
}

void *lista_buscar_nodo(lista_t *lista, size_t posicion)
{
	if (lista == NULL) {
		return NULL;
	}
	if (posicion >= lista_cantidad(lista)) {
		return NULL;
	}
	if (posicion == lista_cantidad(lista) - 1) {
		return lista->fin;
	}

	nodo_t *actual = lista->inicio;
	for (size_t i = 0; i < posicion; i++) {
		actual = actual->siguiente_nodo;
	}
	return actual;
}

lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}
	lista->inicio = NULL;
	lista->fin = NULL;
	lista->cantidad_nodos = 0;

	return lista;
}

bool lista_vacia(lista_t *lista)
{
	if (lista == NULL) {
		return true;
	}
	if (lista_cantidad(lista) == 0 && lista->inicio == NULL &&
	    lista->fin == NULL) {
		return true;
	}
	return false;
}

size_t lista_cantidad(lista_t *lista)
{
	if (lista == NULL) {
		return 0;
	}

	return lista->cantidad_nodos;
}

bool lista_agregar(lista_t *lista, void *dato)
{
	if (lista == NULL) {
		return false;
	}

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL) {
		return false;
	}
	inicializar_nodo(nuevo_nodo, dato, NULL);

	if (lista_vacia(lista)) {
		lista->inicio = nuevo_nodo;
		lista->fin = nuevo_nodo;
		lista->cantidad_nodos++;
		return true;
	}

	lista->fin->siguiente_nodo = nuevo_nodo;
	lista->fin = nuevo_nodo;
	lista->cantidad_nodos++;
	return true;
}

bool lista_insertar(lista_t *lista, void *elemento, size_t posicion)
{
	if (lista == NULL) {
		return false;
	}
	if (posicion == 0 && lista_cantidad(lista) == 0) {
		return false;
	}
	if (posicion >= lista_cantidad(lista)) {
		return false;
	}

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL) {
		return false;
	}
	inicializar_nodo(nuevo_nodo, elemento,
			 lista_buscar_nodo(lista, posicion));

	if (posicion == 0) {
		lista->inicio = nuevo_nodo;
		lista->cantidad_nodos++;
		return true;
	}

	nodo_t *anterior = lista_buscar_nodo(lista, posicion - 1);
	anterior->siguiente_nodo = nuevo_nodo;
	lista->cantidad_nodos++;
	return true;
}

void *lista_buscar_elemento(lista_t *lista, size_t posicion)
{
	if (lista == NULL) {
		return NULL;
	}
	if (posicion >= lista_cantidad(lista)) {
		return NULL;
	}
	if (posicion == lista_cantidad(lista) - 1) {
		return lista->fin->contenido;
	}

	nodo_t *actual = lista->inicio;
	for (size_t i = 0; i < posicion; i++) {
		actual = actual->siguiente_nodo;
	}
	return actual->contenido;
}

void *lista_eliminar_inicio(lista_t *lista)
{
	nodo_t *nodo_a_eliminar = lista->inicio;
	void *ptr_contenido = nodo_a_eliminar->contenido;

	lista->inicio = nodo_a_eliminar->siguiente_nodo;
	free(nodo_a_eliminar);
	if (lista_cantidad(lista) == 1) {
		lista->fin = NULL;
	}
	lista->cantidad_nodos--;

	return ptr_contenido;
}

void *lista_eliminar_fin(lista_t *lista)
{
	nodo_t *nodo_a_eliminar = lista->fin;
	nodo_t *anterior = lista_buscar_nodo(lista, lista_cantidad(lista) - 2);
	void *ptr_contenido = nodo_a_eliminar->contenido;

	lista->fin = anterior;
	ptr_contenido = nodo_a_eliminar->contenido;
	free(nodo_a_eliminar);
	lista->fin->siguiente_nodo = NULL;
	lista->cantidad_nodos--;

	return ptr_contenido;
}

void *lista_eliminar_elemento(lista_t *lista, size_t posicion)
{
	if (lista == NULL) {
		return NULL;
	}
	if (posicion >= lista_cantidad(lista)) {
		return NULL;
	}

	if (posicion == 0) {
		return lista_eliminar_inicio(lista);
	}
	if (posicion == lista_cantidad(lista) - 1) {
		return lista_eliminar_fin(lista);
	}

	nodo_t *nodo_a_eliminar = lista_buscar_nodo(lista, posicion);
	nodo_t *anterior = lista_buscar_nodo(lista, posicion - 1);
	void *ptr_contenido = nodo_a_eliminar->contenido;

	anterior->siguiente_nodo = nodo_a_eliminar->siguiente_nodo;
	free(nodo_a_eliminar);
	lista->cantidad_nodos--;

	return ptr_contenido;
}

int lista_buscar_posicion(lista_t *lista, void *elemento,
			  int (*comparador)(const void *, const void *))
{
	if (lista == NULL || comparador == NULL) {
		return -1;
	}

	int pos = -1;
	int i = 0;
	bool buscando = true;
	nodo_t *actual = lista->inicio;
	while (i < lista_cantidad(lista) && buscando) {
		if (comparador(actual->contenido, elemento) == 0) {
			pos = i;
			buscando = false;
		}
		actual = actual->siguiente_nodo;
		i++;
	}

	return pos;
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*f)(void *, void *),
			       void *extra)
{
	size_t i = 0;

	if (lista == NULL || f == NULL) {
		return i;
	}

	bool iterando = true;
	nodo_t *actual = lista->inicio;
	while (i < lista_cantidad(lista) && iterando) {
		if (!f(actual->contenido, extra)) {
			iterando = false;
		}
		i++;
		actual = actual->siguiente_nodo;
	}

	return i;
}

void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))
{
	if (lista == NULL) {
		return;
	}
	if (destructor == NULL) {
		lista_destruir(lista);
		return;
	}

	nodo_t *actual = lista->inicio;

	for (size_t i = 0; i < lista_cantidad(lista); i++) {
		destructor(actual->contenido);
		actual = actual->siguiente_nodo;
	}

	lista_destruir(lista);
}

void lista_destruir(lista_t *lista)
{
	if (lista == NULL) {
		return;
	}

	nodo_t *actual = lista->inicio;
	nodo_t *aux = actual;

	for (size_t i = 0; i < lista_cantidad(lista); i++) {
		aux = actual->siguiente_nodo;
		free(actual);
		actual = aux;
	}

	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (lista == NULL) {
		return NULL;
	}

	lista_iterador_t *it = malloc(sizeof(lista_iterador_t));
	if (it == NULL) {
		return NULL;
	}

	it->lista = lista;
	it->actual = lista->inicio;

	return it;
}

bool lista_iterador_hay_mas_elementos(lista_iterador_t *it)
{
	if (it == NULL) {
		return false;
	}

	return it->actual != NULL;
}

void lista_iterador_siguiente(lista_iterador_t *it)
{
	if (it == NULL) {
		return;
	}
	if (it->actual == NULL) {
		return;
	}

	it->actual = it->actual->siguiente_nodo;
}

void *lista_iterador_obtener_actual(lista_iterador_t *it)
{
	if (it == NULL) {
		return NULL;
	}
	if (it->actual == NULL) {
		return NULL;
	}

	return it->actual->contenido;
}

void lista_iterador_destruir(lista_iterador_t *it)
{
	if (it == NULL) {
		return;
	}

	free(it);
}