#include "tp1.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORMATO_LECTURA_LINEA "%i,%[^,],%[^,],%i,%i,%i\n"
#define FORMATO_ESCRITURA_ARCHIVO "%i,%s,%s,%i,%i,%i\n"

#define MAX_TIPOS 8
#define MAX_NOM_TIPO 10

const char IDS_TIPOS[MAX_TIPOS][MAX_NOM_TIPO] = { "ELEC", "FUEG", "PLAN",
						  "AGUA", "NORM", "FANT",
						  "PSI",  "LUCH" };
const int CANT_DESEADA_LECTURA = 6;
const unsigned long TAM_INICIAL_BUFFER = 5;
const unsigned long AJUSTE_TAM_BUFFER = 2;
const char INDICADOR_NUEVA_LINEA = '\n';

const int SIN_ERRORES = 0;
const int ERR_REDIMENSIONAR = -1;
const int ERR_LEER_LINEA = -2;
const int ERR_PARSEAR_LINEA = -3;
const int ERR_COPIA = -4;

struct tp1 {
	struct pokemon *pokemones;
	int cantidad_pokemones;
};

void inicializar_tp1(tp1_t *tp1)
{
	if (tp1 == NULL) {
		return;
	}

	tp1->pokemones = NULL;
	tp1->cantidad_pokemones = 0;
}

void inicializar_pokemon(struct pokemon *pokemon)
{
	if (pokemon == NULL) {
		return;
	}

	pokemon->id = -1;
	pokemon->nombre = NULL;
	pokemon->tipo = -1;
	pokemon->ataque = -1;
	pokemon->defensa = -1;
	pokemon->velocidad = -1;
}

int tipo_string_a_id(char *tipo)
{
	int i = 0;
	int id_tipo = -1;
	bool buscando = true;

	while (buscando && i < MAX_TIPOS) {
		if (strcmp(IDS_TIPOS[i], tipo) == 0) {
			id_tipo = i;
			buscando = false;
		}
		i++;
	}

	return id_tipo;
}

void tp1_ordenar_pokemon_id(tp1_t *tp1)
{
	if (tp1 == NULL) {
		return;
	}
	if (tp1->cantidad_pokemones <= 1) {
		return;
	}

	for (int i = 0; i < tp1->cantidad_pokemones - 1; i++) {
		for (int j = 0; j < tp1->cantidad_pokemones - i - 1; j++) {
			if (tp1->pokemones[j].id > tp1->pokemones[j + 1].id) {
				struct pokemon poke_aux = tp1->pokemones[j + 1];
				tp1->pokemones[j + 1] = tp1->pokemones[j];
				tp1->pokemones[j] = poke_aux;
			}
		}
	}
}

int redimensionar_buffer_linea(unsigned long *tam_actual_buffer, int cantidad,
			       char **buffer, char **ptr_aux_buffer)
{
	if (*tam_actual_buffer <= 0 || cantidad < 0 || *buffer == NULL) {
		return ERR_REDIMENSIONAR;
	}

	if (cantidad >= *tam_actual_buffer - 1) {
		*tam_actual_buffer *= AJUSTE_TAM_BUFFER;
		*ptr_aux_buffer =
			realloc(*buffer, *tam_actual_buffer * sizeof(char));
		if (*ptr_aux_buffer == NULL) {
			return ERR_REDIMENSIONAR;
		} else {
			*buffer = *ptr_aux_buffer;
		}
	}

	return SIN_ERRORES;
}

int redimensionar_buffer_pokemones(unsigned long *tam_actual_buffer,
				   int cantidad, struct pokemon **buffer,
				   struct pokemon **ptr_aux_buffer)
{
	if (*tam_actual_buffer <= 0 || cantidad < 0 || *buffer == NULL) {
		return ERR_REDIMENSIONAR;
	}

	if (cantidad >= *tam_actual_buffer) {
		*tam_actual_buffer *= AJUSTE_TAM_BUFFER;
		*ptr_aux_buffer = realloc(
			*buffer, *tam_actual_buffer * sizeof(struct pokemon));
		if (*ptr_aux_buffer == NULL) {
			return ERR_REDIMENSIONAR;
		} else {
			*buffer = *ptr_aux_buffer;
		}
	}

	return SIN_ERRORES;
}

int tp1_leer_linea(FILE *archivo, char **linea)
{
	if (archivo == NULL) {
		return ERR_LEER_LINEA;
	}

	char *buffer = malloc(TAM_INICIAL_BUFFER * sizeof(char));
	if (buffer == NULL) {
		return ERR_LEER_LINEA;
	}

	int i = 0;
	int leido = 0;
	unsigned long tam_actual_buffer = TAM_INICIAL_BUFFER;
	char *ptr_aux_buffer = NULL;

	while (((leido = fgetc(archivo)) != INDICADOR_NUEVA_LINEA) &&
	       (leido != EOF)) {
		if (redimensionar_buffer_linea(&tam_actual_buffer, i, &buffer,
					       &ptr_aux_buffer) ==
		    ERR_REDIMENSIONAR) {
			free(buffer);
			return ERR_LEER_LINEA;
		}
		buffer[i] = (char)leido;
		i++;
	}

	buffer[i] = '\0';
	*linea = buffer;

	if (i == 0 && leido == EOF) {
		free(buffer);
		return EOF;
	}

	return i;
}

bool pokemon_es_valido(struct pokemon pokemon, int tipo_aux)
{
	return pokemon.id > 0 && pokemon.nombre != NULL && tipo_aux >= 0 &&
	       tipo_aux <= 7 && pokemon.ataque > 0 && pokemon.defensa > 0 &&
	       pokemon.velocidad > 0;
}

int tp1_parsear_linea(char *linea, struct pokemon *nuevo_pokemon)
{
	if (linea == NULL || nuevo_pokemon == NULL) {
		return ERR_PARSEAR_LINEA;
	}

	char buffer_tipo[MAX_NOM_TIPO];
	char *buffer_nombre = malloc(strlen(linea) * sizeof(char));
	if (buffer_nombre == NULL) {
		return ERR_PARSEAR_LINEA;
	}

	int leido = sscanf(linea, FORMATO_LECTURA_LINEA, &(nuevo_pokemon->id),
			   buffer_nombre, buffer_tipo, &(nuevo_pokemon->ataque),
			   &(nuevo_pokemon->defensa),
			   &(nuevo_pokemon->velocidad));
	if (leido != CANT_DESEADA_LECTURA) {
		free(buffer_nombre);
		return ERR_PARSEAR_LINEA;
	}
	nuevo_pokemon->nombre = buffer_nombre;
	nuevo_pokemon->tipo = tipo_string_a_id(buffer_tipo);
	int tipo_aux = tipo_string_a_id(buffer_tipo);

	if (!pokemon_es_valido(*nuevo_pokemon, tipo_aux)) {
		free(buffer_nombre);
		return ERR_PARSEAR_LINEA;
	}
	return SIN_ERRORES;
}

void tp1_agregar_pokemon(tp1_t **tp1, struct pokemon nuevo_pokemon)
{
	if (tp1 == NULL || *tp1 == NULL) {
		return;
	}
	if ((*tp1)->cantidad_pokemones < 0) {
		return;
	}

	(*tp1)->pokemones[(*tp1)->cantidad_pokemones] = nuevo_pokemon;
	(*tp1)->cantidad_pokemones++;
}

void manejar_pokemones_repetidos(tp1_t **tp1, struct pokemon nuevo_pokemon)
{
	if (tp1 == NULL || *tp1 == NULL) {
		return;
	}

	bool es_repetido = false;
	int i = 0;

	if ((*tp1)->cantidad_pokemones > 0) {
		while (i < (*tp1)->cantidad_pokemones && !es_repetido) {
			if (nuevo_pokemon.id == (*tp1)->pokemones[i].id) {
				es_repetido = true;
			}
			i++;
		}

		if (es_repetido) {
			free(nuevo_pokemon.nombre);
		} else {
			tp1_agregar_pokemon(tp1, nuevo_pokemon);
		}
	} else if ((*tp1)->cantidad_pokemones == 0) {
		tp1_agregar_pokemon(tp1, nuevo_pokemon);
	}
}

tp1_t *tp1_leer_archivo(const char *nombre)
{
	if (nombre == NULL) {
		return NULL;
	}

	FILE *archivo = fopen(nombre, "r");
	if (archivo == NULL) {
		return NULL;
	}

	tp1_t *tp1 = malloc(sizeof(tp1_t));
	if (tp1 == NULL) {
		fclose(archivo);
		return NULL;
	}

	inicializar_tp1(tp1);

	unsigned long tam_actual_pokemones = TAM_INICIAL_BUFFER;
	struct pokemon *ptr_aux_pokemones = NULL;
	tp1->pokemones = malloc(tam_actual_pokemones * sizeof(struct pokemon));
	if (tp1->pokemones == NULL) {
		fclose(archivo);
		tp1_destruir(tp1);
		return NULL;
	}

	int resultado_lectura = 0;
	char *linea = NULL;

	while ((resultado_lectura = (tp1_leer_linea(archivo, &linea))) != EOF) {
		if (resultado_lectura == ERR_LEER_LINEA) {
			fclose(archivo);
			tp1_destruir(tp1);
			return NULL;
		}

		struct pokemon nuevo_pokemon;
		inicializar_pokemon(&nuevo_pokemon);
		if (tp1_parsear_linea(linea, &nuevo_pokemon) == SIN_ERRORES) {
			manejar_pokemones_repetidos(&tp1, nuevo_pokemon);
			if (redimensionar_buffer_pokemones(
				    &tam_actual_pokemones,
				    tp1->cantidad_pokemones, &(tp1->pokemones),
				    &ptr_aux_pokemones) == ERR_REDIMENSIONAR) {
				free(linea);
				fclose(archivo);
				tp1_destruir(tp1);
				return NULL;
			}
		}

		free(linea);
	}

	fclose(archivo);

	if (tp1->cantidad_pokemones == 0) {
		free(tp1->pokemones);
		tp1->pokemones = NULL;
		return tp1;
	}

	tp1_ordenar_pokemon_id(tp1);

	return tp1;
}

void tp1_destruir(tp1_t *tp1)
{
	if (tp1 == NULL) {
		return;
	}

	for (size_t i = 0; i < tp1_cantidad(tp1); i++) {
		free(tp1->pokemones[i].nombre);
	}
	free(tp1->pokemones);
	free(tp1);
}

size_t tp1_cantidad(tp1_t *tp1)
{
	if (tp1 == NULL || tp1->cantidad_pokemones < 0) {
		return 0;
	}

	return (size_t)tp1->cantidad_pokemones;
}

tp1_t *tp1_guardar_archivo(tp1_t *tp1, const char *nombre)
{
	if (tp1 == NULL || nombre == NULL) {
		return NULL;
	}

	FILE *archivo = fopen(nombre, "w");
	if (archivo == NULL) {
		return NULL;
	}

	for (int i = 0; i < tp1->cantidad_pokemones; i++) {
		fprintf(archivo, FORMATO_ESCRITURA_ARCHIVO,
			tp1->pokemones[i].id, tp1->pokemones[i].nombre,
			IDS_TIPOS[tp1->pokemones[i].tipo],
			tp1->pokemones[i].ataque, tp1->pokemones[i].defensa,
			tp1->pokemones[i].velocidad);
	}

	fclose(archivo);
	return tp1;
}

struct pokemon *tp1_buscar_nombre(tp1_t *tp, const char *nombre)
{
	if (tp == NULL || nombre == NULL) {
		return NULL;
	}
	if (tp->cantidad_pokemones <= 0) {
		return NULL;
	}

	int i = 0;
	bool encontrado = false;
	while (i < tp->cantidad_pokemones && !encontrado) {
		if (strcmp(tp->pokemones[i].nombre, nombre) == 0) {
			encontrado = true;
		} else if (!encontrado) {
			i++;
		}
	}

	if (encontrado) {
		return &(tp->pokemones[i]);
	}
	return NULL;
}

struct pokemon *tp1_buscar_id(tp1_t *tp, int id)
{
	if (tp == NULL || id <= 0) {
		return NULL;
	}
	if (tp->cantidad_pokemones <= 0) {
		return NULL;
	}

	size_t inicio = 0;
	size_t fin = tp1_cantidad(tp) - 1;

	while (inicio <= fin) {
		size_t centro = (inicio + fin) / 2;

		if (tp->pokemones[centro].id == id) {
			return &(tp->pokemones[centro]);
		} else if (tp->pokemones[centro].id < id) {
			inicio = centro + 1;
		} else {
			fin = centro - 1;
		}
	}

	return NULL;
}

int copiar_pokemon(struct pokemon src, struct pokemon *dest)
{
	if (dest == NULL) {
		return ERR_COPIA;
	}

	*dest = src;
	dest->nombre = malloc((strlen(src.nombre) + 1) * sizeof(char));
	if (dest->nombre == NULL) {
		return ERR_COPIA;
	}
	strcpy(dest->nombre, src.nombre);

	return SIN_ERRORES;
}

tp1_t *armar_union(tp1_t *un_tp, tp1_t *otro_tp)
{
	size_t total_temp_pokemones =
		tp1_cantidad(un_tp) + tp1_cantidad(otro_tp);

	tp1_t *tp1_union = malloc(sizeof(tp1_t));
	if (tp1_union == NULL) {
		return NULL;
	}
	inicializar_tp1(tp1_union);

	tp1_union->pokemones =
		malloc(total_temp_pokemones * sizeof(struct pokemon));
	if (tp1_union->pokemones == NULL) {
		tp1_destruir(tp1_union);
		return NULL;
	}

	size_t conteo_1 = 0;
	size_t conteo_2 = 0;

	while (conteo_1 < tp1_cantidad(un_tp) &&
	       conteo_2 < tp1_cantidad(otro_tp)) {
		if (un_tp->pokemones[conteo_1].id ==
		    otro_tp->pokemones[conteo_2].id) {
			if (copiar_pokemon(
				    un_tp->pokemones[conteo_1],
				    &(tp1_union->pokemones
					      [tp1_union->cantidad_pokemones])) ==
			    ERR_COPIA) {
				tp1_destruir(tp1_union);
				return NULL;
			}
			conteo_1++;
			conteo_2++;
		} else if (un_tp->pokemones[conteo_1].id >
			   otro_tp->pokemones[conteo_2].id) {
			if (copiar_pokemon(
				    otro_tp->pokemones[conteo_2],
				    &(tp1_union->pokemones
					      [tp1_union->cantidad_pokemones])) ==
			    ERR_COPIA) {
				tp1_destruir(tp1_union);
				return NULL;
			}
			conteo_2++;
		} else {
			if (copiar_pokemon(
				    un_tp->pokemones[conteo_1],
				    &(tp1_union->pokemones
					      [tp1_union->cantidad_pokemones])) ==
			    ERR_COPIA) {
				tp1_destruir(tp1_union);
				return NULL;
			}
			conteo_1++;
		}
		tp1_union->cantidad_pokemones++;
	}
	if (conteo_1 == tp1_cantidad(un_tp)) {
		while (conteo_2 < tp1_cantidad(otro_tp)) {
			if (copiar_pokemon(
				    otro_tp->pokemones[conteo_2],
				    &(tp1_union->pokemones
					      [tp1_union->cantidad_pokemones])) ==
			    ERR_COPIA) {
				tp1_destruir(tp1_union);
				return NULL;
			}
			tp1_union->cantidad_pokemones++;
			conteo_2++;
		}
	}
	if (conteo_2 == tp1_cantidad(otro_tp)) {
		while (conteo_1 < tp1_cantidad(un_tp)) {
			if (copiar_pokemon(
				    un_tp->pokemones[conteo_1],
				    &(tp1_union->pokemones
					      [tp1_union->cantidad_pokemones])) ==
			    ERR_COPIA) {
				tp1_destruir(tp1_union);
				return NULL;
			}
			tp1_union->cantidad_pokemones++;
			conteo_1++;
		}
	}

	return tp1_union;
}

tp1_t *copiar_tp1(tp1_t src)
{
	tp1_t *copia = malloc(sizeof(tp1_t));
	inicializar_tp1(copia);

	if (copia == NULL) {
		return NULL;
	}
	copia->pokemones = malloc(tp1_cantidad(&src) * sizeof(struct pokemon));
	if (copia->pokemones == NULL) {
		free(copia);
		return NULL;
	}

	int i = 0;
	while (i < tp1_cantidad(&src)) {
		if (copiar_pokemon(src.pokemones[i], &(copia->pokemones[i])) ==
		    SIN_ERRORES) {
			copia->cantidad_pokemones++;
			i++;
		} else {
			tp1_destruir(copia);
			return NULL;
		}
	}

	return copia;
}

tp1_t *tp1_union(tp1_t *un_tp, tp1_t *otro_tp)
{
	if (un_tp == NULL || otro_tp == NULL) {
		return NULL;
	}

	if (un_tp->cantidad_pokemones == 0) {
		tp1_t *tp1_union = copiar_tp1(*otro_tp);
		if (tp1_union != NULL) {
			return tp1_union;
		}
		return NULL;
	}
	if (otro_tp->cantidad_pokemones == 0) {
		tp1_t *tp1_union = copiar_tp1(*un_tp);
		if (tp1_union != NULL) {
			return tp1_union;
		}
		return NULL;
	}

	tp1_t *tp1_union = armar_union(un_tp, otro_tp);
	if (tp1_union == NULL) {
		return NULL;
	}

	struct pokemon *ptr_aux_pokemones_union =
		realloc(tp1_union->pokemones,
			tp1_cantidad(tp1_union) * sizeof(struct pokemon));
	if (ptr_aux_pokemones_union == NULL) {
		tp1_destruir(tp1_union);
		return NULL;
	} else {
		tp1_union->pokemones = ptr_aux_pokemones_union;
	}

	return tp1_union;
}

size_t elegir_maximo(size_t cantidad_1, size_t cantidad_2)
{
	if (cantidad_1 >= cantidad_2) {
		return cantidad_1;
	}
	return cantidad_2;
}

tp1_t *armar_interseccion(tp1_t *un_tp, tp1_t *otro_tp)
{
	size_t total_temp_pokemones =
		elegir_maximo(tp1_cantidad(un_tp), tp1_cantidad(otro_tp));

	tp1_t *tp1_interseccion = malloc(sizeof(tp1_t));
	if (tp1_interseccion == NULL) {
		return NULL;
	}
	inicializar_tp1(tp1_interseccion);

	tp1_interseccion->pokemones =
		malloc(total_temp_pokemones * sizeof(struct pokemon));
	if (tp1_interseccion->pokemones == NULL) {
		tp1_destruir(tp1_interseccion);
		return NULL;
	}

	size_t conteo_1 = 0;
	size_t conteo_2 = 0;

	while (conteo_1 < tp1_cantidad(un_tp) &&
	       conteo_2 < tp1_cantidad(otro_tp)) {
		if (un_tp->pokemones[conteo_1].id ==
		    otro_tp->pokemones[conteo_2].id) {
			if (copiar_pokemon(
				    un_tp->pokemones[conteo_1],
				    &(tp1_interseccion->pokemones
					      [tp1_interseccion
						       ->cantidad_pokemones])) ==
			    ERR_COPIA) {
				tp1_destruir(tp1_interseccion);
				return NULL;
			}
			conteo_1++;
			conteo_2++;
			tp1_interseccion->cantidad_pokemones++;
		} else if (un_tp->pokemones[conteo_1].id >
			   otro_tp->pokemones[conteo_2].id) {
			conteo_2++;
		} else {
			conteo_1++;
		}
	}

	if (tp1_cantidad(tp1_interseccion) == 0) {
		free(tp1_interseccion->pokemones);
		tp1_interseccion->pokemones = NULL;
	}

	return tp1_interseccion;
}

tp1_t *tp1_interseccion(tp1_t *un_tp, tp1_t *otro_tp)
{
	if (un_tp == NULL || otro_tp == NULL) {
		return NULL;
	}
	if (un_tp->cantidad_pokemones == 0 ||
	    otro_tp->cantidad_pokemones == 0) {
		tp1_t *tp1_interseccion = malloc(sizeof(tp1_t));
		if (tp1_interseccion == NULL) {
			return NULL;
		}
		inicializar_tp1(tp1_interseccion);
		return tp1_interseccion;
	}

	tp1_t *tp1_interseccion = armar_interseccion(un_tp, otro_tp);
	if (tp1_interseccion == NULL) {
		return NULL;
	}

	if (tp1_cantidad(tp1_interseccion) == 0) {
		return tp1_interseccion;
	}

	struct pokemon *ptr_aux_pokemones_interseccion = realloc(
		tp1_interseccion->pokemones,
		tp1_cantidad(tp1_interseccion) * sizeof(struct pokemon));
	if (ptr_aux_pokemones_interseccion == NULL) {
		tp1_destruir(tp1_interseccion);
		return NULL;
	} else {
		tp1_interseccion->pokemones = ptr_aux_pokemones_interseccion;
	}

	return tp1_interseccion;
}

tp1_t *armar_diferencia(tp1_t *un_tp, tp1_t *otro_tp)
{
	size_t total_temp_pokemones = tp1_cantidad(un_tp);

	tp1_t *tp1_diferencia = malloc(sizeof(tp1_t));
	if (tp1_diferencia == NULL) {
		return NULL;
	}
	inicializar_tp1(tp1_diferencia);

	tp1_diferencia->pokemones =
		malloc(total_temp_pokemones * sizeof(struct pokemon));
	if (tp1_diferencia->pokemones == NULL) {
		tp1_destruir(tp1_diferencia);
		return NULL;
	}

	size_t conteo_1 = 0;
	size_t conteo_2 = 0;

	while (conteo_1 < tp1_cantidad(un_tp) &&
	       conteo_2 < tp1_cantidad(otro_tp)) {
		if (un_tp->pokemones[conteo_1].id ==
		    otro_tp->pokemones[conteo_2].id) {
			conteo_1++;
			conteo_2++;
		} else if (un_tp->pokemones[conteo_1].id >
			   otro_tp->pokemones[conteo_2].id) {
			conteo_2++;
		} else {
			if (copiar_pokemon(
				    un_tp->pokemones[conteo_1],
				    &(tp1_diferencia->pokemones
					      [tp1_diferencia
						       ->cantidad_pokemones])) ==
			    ERR_COPIA) {
				tp1_destruir(tp1_diferencia);
				return NULL;
			}
			tp1_diferencia->cantidad_pokemones++;
			conteo_1++;
		}
	}
	if (conteo_2 == tp1_cantidad(otro_tp)) {
		while (conteo_1 < tp1_cantidad(un_tp)) {
			if (copiar_pokemon(
				    un_tp->pokemones[conteo_1],
				    &(tp1_diferencia->pokemones
					      [tp1_diferencia
						       ->cantidad_pokemones])) ==
			    ERR_COPIA) {
				tp1_destruir(tp1_diferencia);
				return NULL;
			}
			tp1_diferencia->cantidad_pokemones++;
			conteo_1++;
		}
	}

	if (tp1_cantidad(tp1_diferencia) == 0) {
		free(tp1_diferencia->pokemones);
		tp1_diferencia->pokemones = NULL;
	}

	return tp1_diferencia;
}

tp1_t *tp1_diferencia(tp1_t *un_tp, tp1_t *otro_tp)
{
	if (un_tp == NULL || otro_tp == NULL) {
		return NULL;
	}
	if (un_tp->cantidad_pokemones == 0) {
		tp1_t *tp1_diferencia = malloc(sizeof(tp1_t));
		if (tp1_diferencia == NULL) {
			return NULL;
		}
		inicializar_tp1(tp1_diferencia);
		return tp1_diferencia;
	}
	if (otro_tp->cantidad_pokemones == 0) {
		tp1_t *tp1_diferencia = copiar_tp1(*un_tp);
		if (tp1_diferencia != NULL) {
			return tp1_diferencia;
		}
		return NULL;
	}

	tp1_t *tp1_diferencia = armar_diferencia(un_tp, otro_tp);
	if (tp1_diferencia == NULL) {
		return NULL;
	}

	if (tp1_cantidad(tp1_diferencia) == 0) {
		return tp1_diferencia;
	}

	struct pokemon *ptr_aux_pokemones_diferencia =
		realloc(tp1_diferencia->pokemones,
			tp1_cantidad(tp1_diferencia) * sizeof(struct pokemon));
	if (ptr_aux_pokemones_diferencia == NULL) {
		tp1_destruir(tp1_diferencia);
		return NULL;
	} else {
		tp1_diferencia->pokemones = ptr_aux_pokemones_diferencia;
	}

	return tp1_diferencia;
}

size_t tp1_con_cada_pokemon(tp1_t *un_tp, bool (*f)(struct pokemon *, void *),
			    void *extra)
{
	size_t i = 0;

	if (un_tp == NULL || f == NULL) {
		return i;
	}

	bool iterando = true;

	while (i < tp1_cantidad(un_tp) && iterando) {
		if ((*f)(&(un_tp->pokemones[i]), extra) == false) {
			iterando = false;
		}
		i++;
	}

	return i;
}
