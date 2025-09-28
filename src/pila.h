#ifndef PILA_H_
#define PILA_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct pila pila_t;

/**
 * Crea una pila vacía.
 * 
 * Devuelve NULL en caso de error.
 */
pila_t *pila_crear();

/**
 * Agrega un elemento al tope de la pila.
 * 
 * Devuelve true si se pudo agregar.
 */
bool pila_apilar(pila_t *pila, void *elemento);

/**
 * Elimina el elemento en el tope de la pila. Devuelve el elemento.
 * 
 * En caso de error devuelve NULL.
 */
void *pila_desapilar(pila_t *pila);

/**
 * Devuelve un puntero al elemento situado en el tope de la pila.
 * 
 * En caso de error devuelve NULL.
 */
void *pila_ver_primero(pila_t *pila);

/**
 * Devuelve la cantidad actual de elementos apilados.
 * 
 * Una pila nula se considera vacía.
 */
size_t pila_cantidad(pila_t *pila);

/**
 * Destruye la pila.
 * 
 * Los elementos existentes en memoria dinámica deberán ser liberados manualmente por el usuario después de eliminar.
 */
void pila_destruir(pila_t *pila);

#endif // PILA_H_
