#ifndef FUNCIONES_AUXILIARES_H_
#define FUNCIONES_AUXILIARES_H_
#include "tp1.h"
#include "lista.h"

bool str_son_iguales(const char *string1, const char *string2);

int controlar_argumentos_iniciales(int argc, char *argv[]);

tp1_t *procesar_pokedex(char *nombre);

bool agregar_pokemon_a_lista(struct pokemon *pokemon, void *lis);

int cargar_pokedex_en_lista(tp1_t *pokedex, lista_t *lista);

void imprimir_pokemon(struct pokemon pokemon);

int buscar_pos_pokemon_por_id(const void *poke, const void *id);

int buscar_pos_pokemon_por_nombre(const void *poke, const void *nombre);

#endif // FUNCIONES_AUXILIARES_H_
