#ifndef COLA_H_
#define COLA_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct cola cola_t;

/**
 * Crea una cola vacía.
 * 
 * Devuelve NULL en caso de error.
 */
cola_t *cola_crear();

/**
 * Agrega un elemento al final de la cola.
 * 
 * Devuelve true si se pudo agregar.
 */
bool cola_encolar(cola_t *cola, void *elemento);

/**
 * Elimina el elemento al frente de la cola. Devuelve el elemento.
 * 
 * Devuelve NULL en caso de error.
 */
void *cola_desencolar(cola_t *cola);

/**
 * Devuelve un puntero al elemento al frente de la cola.
 * 
 * En caso de error devuelve NULL.
 */
void *cola_ver_primero(cola_t *cola);

/**
 * Devuelve la cantidad actual de elementos encolados.
 * 
 * Una cola nula se considera vacía.
 */
size_t cola_cantidad(cola_t *cola);

/**
 * Destruye la cola.
 * 
 * Los elementos existentes en memoria dinámica deberán ser liberados manualmente por el usuario después de eliminar.
 */
void cola_destruir(cola_t *cola);

#endif // COLA_H_
