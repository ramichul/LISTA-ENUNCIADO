#include "lista.h"
#include "tp1.h"
#include "constantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool str_son_iguales(const char *string1, const char *string2)
{
	size_t long_1 = strlen(string1);
	size_t long_2 = strlen(string2);

	if (long_1 != long_2) {
		return false;
	}

	size_t contador = 0;

	while (contador < long_1) {
		if (tolower(string1[contador]) != tolower(string2[contador])) {
			return false;
		}
		contador++;
	}

	return true;
}

int controlar_argumentos_iniciales(int argc, char *argv[])
{
	if (argc != CANT_ESPERADA_ARGUMENTOS) {
		printf(MSJ_INSTRUCCIONES);
		return ERR_CONTROL;
	}
	if (!str_son_iguales(argv[2], COMANDO_VALIDO)) {
		printf(MSJ_ERR_COMANDO, argv[2]);
		printf(MSJ_INSTRUCCIONES);
		return ERR_CONTROL;
	}
	if (!str_son_iguales(argv[3], INSTRUCCION_VALIDA_1) &&
	    !str_son_iguales(argv[3], INSTRUCCION_VALIDA_2)) {
		printf(MSJ_ERR_INSTRUCCION, argv[3]);
		printf(MSJ_INSTRUCCIONES);
		return ERR_CONTROL;
	}
	if (str_son_iguales(argv[3], INSTRUCCION_VALIDA_1) &&
	    atoi(argv[4]) == 0) {
		printf(MSJ_ERR_PARAM, argv[4]);
		printf(MSJ_INSTRUCCIONES);
		return ERR_CONTROL;
	}

	return 0;
}

tp1_t *procesar_pokedex(char *nombre)
{
	printf(MSJ_PROCESAMIENTO, nombre);
	tp1_t *pokedex = tp1_leer_archivo(nombre);
	if (pokedex == NULL) {
		printf(MSJ_ERR_LECTURA);
		return NULL;
	}
	printf(MSJ_PROCESAMIENTO_EXITOSO);
	return pokedex;
}

bool agregar_pokemon_a_lista(struct pokemon *pokemon, void *lis)
{
	lista_t *lista = (lista_t *)lis;

	return lista_agregar(lista, pokemon);
}

int cargar_pokedex_en_lista(tp1_t *pokedex, lista_t *lista)
{
	if (tp1_con_cada_pokemon(pokedex, agregar_pokemon_a_lista, lista) !=
	    tp1_cantidad(pokedex)) {
		printf(MSJ_ERR_CARGA);
		return ERR_CARGA;
	}

	return 0;
}

void imprimir_pokemon(struct pokemon pokemon)
{
	printf(MSJ_DATOS, pokemon.id, pokemon.nombre,
	       NOMBRES_COMPLETOS_TIPOS[pokemon.tipo], pokemon.ataque,
	       pokemon.defensa, pokemon.velocidad);
}

int buscar_pos_pokemon_por_id(const void *poke, const void *id)
{
	struct pokemon *pokemon = (struct pokemon *)poke;
	int id_buscado = atoi((char *)id);

	if (pokemon->id == id_buscado) {
		return 0;
	}

	return -1;
}

int buscar_pos_pokemon_por_nombre(const void *poke, const void *nombre)
{
	struct pokemon *pokemon = (struct pokemon *)poke;
	char *nombre_buscado = (char *)nombre;

	if (str_son_iguales(pokemon->nombre, nombre_buscado)) {
		return 0;
	}

	return -1;
}
