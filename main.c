#include "src/lista.h"
#include "src/tp1.h"
#include "src/funciones_auxiliares.h"
#include "src/constantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int ejecutar_comando_busqueda(lista_t *lista, char *argv[])
{
	bool busqueda_es_por_id =
		str_son_iguales(argv[3], INSTRUCCION_VALIDA_1);
	struct pokemon *buscado = NULL;
	int pos = -1;

	if (busqueda_es_por_id) {
		pos = lista_buscar_posicion(lista, argv[4],
					    buscar_pos_pokemon_por_id);
	} else {
		pos = lista_buscar_posicion(lista, argv[4],
					    buscar_pos_pokemon_por_nombre);
	}

	if (pos == -1) {
		printf(MSJ_ERR_BUSQUEDA);
		return ERR_BUSQUEDA;
	}

	buscado = lista_buscar_elemento(lista, (size_t)pos);
	imprimir_pokemon(*buscado);

	return 0;
}

int main(int argc, char *argv[])
{
	printf(MSJ_BIENVENIDA);
	if (controlar_argumentos_iniciales(argc, argv) == ERR_CONTROL) {
		return ERR_CONTROL;
	}

	tp1_t *pokedex = procesar_pokedex(argv[1]);
	if (pokedex == NULL) {
		return ERR_LECTURA;
	}

	lista_t *lista = lista_crear();
	if (lista == NULL) {
		printf(MSJ_ERR_LISTA);
		tp1_destruir(pokedex);
		return ERR_LISTA;
	}

	if (cargar_pokedex_en_lista(pokedex, lista) == ERR_CARGA) {
		tp1_destruir(pokedex);
		lista_destruir(lista);
		return ERR_CARGA;
	}
	if (ejecutar_comando_busqueda(lista, argv) == ERR_BUSQUEDA) {
		tp1_destruir(pokedex);
		lista_destruir(lista);
		return ERR_BUSQUEDA;
	}

	tp1_destruir(pokedex);
	lista_destruir(lista);
	return 0;
}
