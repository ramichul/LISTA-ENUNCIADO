#include "pa2m.h"
#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"

int comparador_enteros_son_iguales(const void *elemento1, const void *elemento2)
{
	bool enteros_son_iguales = *((int *)elemento1) == *((int *)elemento2);
	if (enteros_son_iguales) {
		return 0;
	}
	return -1;
}

bool funcion_generica_comparador_enteros(void *elemento1, void *elemento2)
{
	return *((int *)elemento1) == *((int *)elemento2);
}

bool funcion_generica_reemplazar_todos(void *elemento1, void *elemento2)
{
	*((int *)elemento1) = *((int *)elemento2);
	return true;
}

bool comprobar_array_verificaciones(bool *verificaciones, size_t tope)
{
	bool comprobado = true;

	for (size_t i = 0; i < tope; i++) {
		if (!verificaciones[i]) {
			comprobado = false;
		}
	}

	return comprobado;
}

void lista_crear_devuelve_lista_vacia()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_vacia(lista),
		     "lista_crear() devuelve una lista vacía");
	lista_destruir(lista);
}

void lista_vacia_toma_lista_nula_como_vacia()
{
	pa2m_afirmar(
		lista_vacia(NULL),
		"lista_vacia() recibe una lista nula y la asume como vacía");
}

void lista_vacia_reconoce_lista_vacia()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(
		lista_vacia(lista),
		"lista_vacia() recibe una lista vacía y la reconoce como tal");
	lista_destruir(lista);
}

void lista_vacia_reconoce_lista_no_vacia()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	pa2m_afirmar(
		!lista_vacia(lista),
		"lista_vacia() recibe una lista no vacía y la reconoce como tal");
	lista_destruir(lista);
}

void lista_cantidad_toma_lista_nula_como_vacia()
{
	pa2m_afirmar(
		lista_cantidad(NULL) == 0,
		"lista_cantidad() recibe una lista nula y la asume como vacía");
}

void lista_cantidad_devuelve_0_con_lista_vacia()
{
	lista_t *lista_vacia = lista_crear();

	pa2m_afirmar(lista_cantidad(lista_vacia) == 0,
		     "lista_cantidad() recibe una lista vacía y devuelve 0");
	lista_destruir(lista_vacia);
}

void lista_cantidad_devuelve_valor_correcto()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	pa2m_afirmar(
		lista_cantidad(lista) == 3,
		"lista_cantidad() devuelve el valor correspondiente de elementos presentes");
	lista_destruir(lista);
}

void lista_agregar_no_agrega_elementos_a_lista_nula()
{
	int dato = 50;
	bool resultado_agregar = lista_agregar(NULL, &dato);

	pa2m_afirmar(
		!resultado_agregar,
		"lista_agregar() no intenta agregar elementos a una lista nula");
}

void lista_agregar_agrega_elemento_a_lista_vacia()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	bool resultado_agregar = lista_agregar(lista, &dato);
	int *elemento_inicio = lista_buscar_elemento(lista, 0);

	pa2m_afirmar(
		resultado_agregar && *elemento_inicio == 50,
		"lista_agregar() agrega un elemento correctamente a una lista vacía");
	lista_destruir(lista);
}

void lista_agregar_agrega_elemento_a_lista_no_vacia()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	bool resultado_agregar;
	for (size_t i = 0; i < 3; i++) {
		resultado_agregar = lista_agregar(lista, &elementos[i]);
	}

	int *elemento_fin =
		lista_buscar_elemento(lista, lista_cantidad(lista) - 1);

	pa2m_afirmar(
		resultado_agregar && *elemento_fin == 3,
		"lista_agregar() agrega un elemento correctamente a una lista no vacía");
	lista_destruir(lista);
}

void lista_agregar_cambia_cantidad_de_elementos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	pa2m_afirmar(
		lista_cantidad(lista) == 3,
		"lista_agregar() cambia la cantidad de elementos correctamente");
	lista_destruir(lista);
}

void lista_insertar_no_agrega_elementos_a_lista_nula()
{
	int dato = 50;
	bool resultado_insertar = lista_insertar(NULL, &dato, 0);

	pa2m_afirmar(
		!resultado_insertar,
		"lista_insertar() no intenta agregar elementos a una lista nula");
}

void lista_insertar_no_agrega_elementos_en_una_posicion_invalida()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	bool resultado_insertar = lista_insertar(lista, &dato, 5);

	pa2m_afirmar(
		!resultado_insertar,
		"lista_insertar() no intenta agregar elementos en una posición inválida");
	lista_destruir(lista);
}

void lista_insertar_no_agrega_elemento_a_lista_vacia()
{
	lista_t *lista = lista_crear();
	int dato = 50;
	bool resultado_agregar = lista_insertar(lista, &dato, 0);

	pa2m_afirmar(
		!resultado_agregar,
		"lista_insertar() no agrega un elemento a una lista vacía");
	lista_destruir(lista);
}

void lista_insertar_agrega_elemento_al_principio_correctamente()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int dato = 50;
	bool resultado_insertar = lista_insertar(lista, &dato, 0);
	int *elemento_inicio = lista_buscar_elemento(lista, 0);

	pa2m_afirmar(
		resultado_insertar && *elemento_inicio == 50,
		"lista_insertar() agrega un elemento al principio correctamente");
	lista_destruir(lista);
}

void lista_insertar_agrega_elemento_en_el_medio_correctamente()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int dato = 50;
	size_t pos = 1;
	bool resultado_insertar = lista_insertar(lista, &dato, pos);

	int *elemento_anterior = lista_buscar_elemento(lista, pos - 1);
	int *elemento_insertado = lista_buscar_elemento(lista, pos);
	int *elemento_siguiente = lista_buscar_elemento(lista, pos + 1);

	pa2m_afirmar(
		resultado_insertar && *elemento_anterior == 1 &&
			*elemento_insertado == 50 && *elemento_siguiente == 2,
		"lista_insertar() agrega un elemento en el medio correctamente");
	lista_destruir(lista);
}

void lista_insertar_no_agrega_elemento_al_final()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int dato = 50;
	size_t pos = lista_cantidad(lista);
	bool resultado_insertar = lista_insertar(lista, &dato, pos);

	pa2m_afirmar(
		!resultado_insertar,
		"lista_insertar() no agrega un elemento al final de la lista");
	lista_destruir(lista);
}

void lista_insertar_cambia_cantidad_de_elementos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	lista_agregar(lista, &elementos[0]);
	lista_agregar(lista, &elementos[1]);
	lista_insertar(lista, &elementos[2], 1);

	pa2m_afirmar(
		lista_cantidad(lista) == 3,
		"lista_insertar() cambia la cantidad de elementos correctamente");
	lista_destruir(lista);
}

void lista_eliminar_elemento_no_intenta_eliminar_de_lista_nula()
{
	void *elemento_eliminado = lista_eliminar_elemento(NULL, 0);

	pa2m_afirmar(
		elemento_eliminado == NULL,
		"lista_eliminar_elemento() no intenta eliminar elementos de una lista nula");
}

void lista_eliminar_elemento_no_intenta_eliminar_de_lista_vacia()
{
	lista_t *lista_vacia = lista_crear();
	void *elemento_eliminado = lista_eliminar_elemento(lista_vacia, 0);

	pa2m_afirmar(
		elemento_eliminado == NULL,
		"lista_eliminar_elemento() no intenta eliminar elementos de una lista vacía");
	lista_destruir(lista_vacia);
}

void lista_eliminar_elemento_no_intenta_eliminar_elemento_en_posicion_invalida()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	void *elemento_eliminado = lista_eliminar_elemento(lista, 5);

	pa2m_afirmar(
		elemento_eliminado == NULL,
		"lista_eliminar_elemento() no intenta eliminar un elemento en una posición inválida");
	lista_destruir(lista);
}

void lista_eliminar_elemento_elimina_elemento_y_extrae_datos_correctamente()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int *elemento_eliminado = lista_eliminar_elemento(lista, 1);

	pa2m_afirmar(
		*elemento_eliminado == 2,
		"lista_eliminar_elemento() elimina un elemento y extrae sus datos correctamente");
	lista_destruir(lista);
}

void lista_eliminar_elemento_elimina_elemento_y_mantiene_orden()
{
	lista_t *lista = lista_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	size_t pos = 1;
	int *elemento_siguiente = lista_buscar_elemento(lista, pos + 1);
	lista_eliminar_elemento(lista, pos);
	int *nuevo_elemento_siguiente = lista_buscar_elemento(lista, pos);

	pa2m_afirmar(
		*elemento_siguiente == *nuevo_elemento_siguiente,
		"lista_eliminar_elemento() elimina un elemento y mantiene el orden correcto dentro de la lista");
	lista_destruir(lista);
}

void lista_eliminar_elemento_cambia_cantidad_de_elementos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	lista_eliminar_elemento(lista, 1);

	pa2m_afirmar(
		lista_cantidad(lista) == 2,
		"lista_eliminar_elemento() cambia la cantidad de elementos correctamente");
	lista_destruir(lista);
}

void lista_buscar_posicion_ignora_lista_nula()
{
	int dato = 5;
	int resultado_busqueda = lista_buscar_posicion(
		NULL, &dato, comparador_enteros_son_iguales);

	pa2m_afirmar(
		resultado_busqueda == -1,
		"lista_buscar_posicion() no intenta buscar en una lista nula");
}

void lista_buscar_posicion_ignora_comparador_nulo()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int dato = 5;
	int resultado_busqueda = lista_buscar_posicion(NULL, &dato, NULL);

	pa2m_afirmar(
		resultado_busqueda == -1,
		"lista_buscar_posicion() no intenta utilizar un comparador nulo");
	lista_destruir(lista);
}

void lista_buscar_posicion_encuentra_elemento_presente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int dato = 3;
	int resultado_busqueda = lista_buscar_posicion(
		lista, &dato, comparador_enteros_son_iguales);

	pa2m_afirmar(
		resultado_busqueda == 2,
		"lista_buscar_posicion() logra encontrar un elemento presente");
	lista_destruir(lista);
}

void lista_buscar_posicion_devuelve_error_buscando_elemento_no_presente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int dato = 5;
	int resultado_busqueda = lista_buscar_posicion(
		lista, &dato, comparador_enteros_son_iguales);

	pa2m_afirmar(
		resultado_busqueda == -1,
		"lista_buscar_posicion() devuelve error al intentar buscar un elemento no presente");
	lista_destruir(lista);
}

void lista_buscar_elemento_ignora_lista_nula()
{
	void *resultado_busqueda = lista_buscar_elemento(NULL, 0);

	pa2m_afirmar(
		resultado_busqueda == NULL,
		"lista_buscar_elemento() no intenta buscar en una lista nula");
}

void lista_buscar_elemento_ignora_posicion_invalida()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	void *resultado_busqueda = lista_buscar_elemento(lista, 5);

	pa2m_afirmar(
		resultado_busqueda == NULL,
		"lista_buscar_elemento() no intenta buscar el elemento en una posición inválida");
	lista_destruir(lista);
}

void lista_buscar_elemento_encuentra_elemento_presente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int *resultado_busqueda = lista_buscar_elemento(lista, 1);

	pa2m_afirmar(
		*resultado_busqueda == 2,
		"lista_buscar_elemento() logra encontrar un elemento en una posición válida y extrae sus datos correctamente");
	lista_destruir(lista);
}

void lista_con_cada_elemento_ignora_lista_nula()
{
	int dato = 5;
	size_t cnt_comparaciones = lista_con_cada_elemento(
		NULL, funcion_generica_comparador_enteros, &dato);

	pa2m_afirmar(
		cnt_comparaciones == 0,
		"lista_con_cada_elemento() no intenta iterar sobre una lista nula");
}

void lista_con_cada_elemento_ignora_funcion_nula_sobre_lista_valida()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int dato = 5;
	size_t cnt_comparaciones = lista_con_cada_elemento(lista, NULL, &dato);

	pa2m_afirmar(
		cnt_comparaciones == 0,
		"lista_con_cada_elemento() no intenta iterar sobre una lista válida con una función nula");
	lista_destruir(lista);
}

void lista_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int dato = 1;
	size_t cnt_elementos_afectados = lista_con_cada_elemento(
		lista, funcion_generica_comparador_enteros, &dato);

	pa2m_afirmar(
		cnt_elementos_afectados == 2,
		"lista_con_cada_elemento() devuelve la cantidad correcta de elementos a los cuales se le aplíco la función");
	lista_destruir(lista);
}

void lista_con_cada_elemento_aplica_la_funcion_sobre_todo_elemento()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 5, 2, 9 };
	for (size_t i = 0; i < 3; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	int dato = 1;
	size_t cnt_elementos_afectados = lista_con_cada_elemento(
		lista, funcion_generica_reemplazar_todos, &dato);
	int *primer_elemento = lista_buscar_elemento(lista, 0);
	int *segundo_elemento = lista_buscar_elemento(lista, 1);
	int *tercer_elemento = lista_buscar_elemento(lista, 2);

	pa2m_afirmar(
		cnt_elementos_afectados == 3 && *primer_elemento == dato &&
			*segundo_elemento == dato && *tercer_elemento == dato,
		"lista_con_cada_elemento() aplíca una función genérica sobre todos los elementos correctamente");
	lista_destruir(lista);
}

void lista_iterador_crear_no_crea_un_iterador_para_lista_nula()
{
	lista_iterador_t *it = lista_iterador_crear(NULL);

	pa2m_afirmar(
		it == NULL,
		"lista_iterador_crear() no intenta crear un iterador para una lista nula");
	lista_iterador_destruir(it);
}

void lista_iterador_hay_mas_elementos_toma_iterador_nulo()
{
	pa2m_afirmar(
		lista_iterador_hay_mas_elementos(NULL) == false,
		"lista_iterador_hay_mas_elementos() toma un iterador nulo y lo considera como finalizado");
}

void lista_iterador_hay_mas_elementos_reconoce_fin_de_lista()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2 };
	for (size_t i = 0; i < 2; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	lista_iterador_t *it = lista_iterador_crear(lista);
	bool hay_mas_al_principio = lista_iterador_hay_mas_elementos(it);
	lista_iterador_siguiente(it);
	lista_iterador_siguiente(it);
	bool hay_mas_al_final = lista_iterador_hay_mas_elementos(it);

	pa2m_afirmar(
		hay_mas_al_principio && !hay_mas_al_final,
		"lista_iterador_hay_mas_elementos() reconoce el final de la lista correctamente");
	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void lista_iterador_obtener_actual_extrae_datos_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[] = { 1, 2 };
	for (size_t i = 0; i < 2; i++) {
		lista_agregar(lista, &elementos[i]);
	}

	lista_iterador_t *it = lista_iterador_crear(lista);
	int *elemento_actual = lista_iterador_obtener_actual(it);

	pa2m_afirmar(
		*elemento_actual == 1,
		"lista_iterador_obtener_actual() extrae los datos del elemento actual correctamente");
	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void pila_crear_devuelve_pila_vacia()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "pila_crear() devuelve una pila vacía");
	pila_destruir(pila);
}

void pila_cantidad_toma_pila_nula_como_vacia()
{
	pa2m_afirmar(
		pila_cantidad(NULL) == 0,
		"pila_cantidad() recibe una pila nula y la asume como vacía");
}

void pila_cantidad_devuelve_valor_correcto()
{
	pila_t *pila = pila_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	pa2m_afirmar(
		pila_cantidad(pila) == 3,
		"pila_cantidad() devuelve el valor correspondiente de elementos presentes");
	pila_destruir(pila);
}

void pila_ver_primero_sobre_pila_nula_devuelve_null()
{
	void *elemento_tope = pila_ver_primero(NULL);
	pa2m_afirmar(
		elemento_tope == NULL,
		"pila_ver_primero() devuelve puntero nulo al usarse sobre una pila nula");
}

void pila_ver_primero_sobre_pila_vacia_devuelve_null()
{
	pila_t *pila = pila_crear();
	void *elemento_tope = pila_ver_primero(pila);

	pa2m_afirmar(
		elemento_tope == NULL,
		"pila_ver_primero() devuelve puntero nulo al usarse sobre una pila vacía");
	pila_destruir(pila);
}

void pila_ver_primero_extrae_datos_correctamente()
{
	pila_t *pila = pila_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	int *elemento_tope = pila_ver_primero(pila);
	pa2m_afirmar(
		*elemento_tope == 3,
		"pila_ver_primero() extrae correctamente los datos del elemento tope");
	pila_destruir(pila);
}

void pila_apilar_no_agrega_elementos_a_pila_nula()
{
	int dato = 50;
	bool resultado_apilar = pila_apilar(NULL, &dato);

	pa2m_afirmar(
		!resultado_apilar,
		"pila_apilar() no intenta agregar elementos a una pila nula");
}

void pila_apilar_agrega_elemento_a_pila_vacia()
{
	pila_t *pila = pila_crear();
	int dato = 50;
	bool resultado_apilar = pila_apilar(pila, &dato);
	int *elemento_inicio = pila_ver_primero(pila);

	pa2m_afirmar(
		resultado_apilar && *elemento_inicio == 50,
		"pila_apilar() agrega un elemento correctamente a una pila vacía");
	pila_destruir(pila);
}

void pila_apilar_agrega_elemento_a_pila_no_vacia()
{
	pila_t *pila = pila_crear();
	int elementos[] = { 1, 2, 3 };
	bool resultado_apilar;
	for (size_t i = 0; i < 3; i++) {
		resultado_apilar = pila_apilar(pila, &elementos[i]);
	}
	int *elemento_tope = pila_ver_primero(pila);

	pa2m_afirmar(
		resultado_apilar && *elemento_tope == 3,
		"pila_apilar() agrega un elemento correctamente a una pila no vacía");
	pila_destruir(pila);
}

void pila_apilar_cambia_cantidad_de_elementos_correctamente()
{
	pila_t *pila = pila_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	pa2m_afirmar(
		pila_cantidad(pila) == 3,
		"pila_apilar() cambia la cantidad de elementos correctamente");
	pila_destruir(pila);
}

void pila_apilar_siempre_agrega_al_tope_de_la_pila()
{
	pila_t *pila = pila_crear();
	int elementos[] = { 1, 2, 3 };
	bool verificaciones[] = { false, false, false };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}
	for (size_t i = 0; i < 3; i++) {
		int *desapilado = pila_desapilar(pila);
		if (*desapilado == elementos[2 - i]) {
			verificaciones[i] = true;
		}
	}

	pa2m_afirmar(
		comprobar_array_verificaciones(verificaciones, 3),
		"pila_apilar() siempre agrega elementos al tope de la pila");
	pila_destruir(pila);
}

void pila_desapilar_no_intenta_eliminar_de_pila_nula()
{
	void *elemento_desapilado = pila_desapilar(NULL);
	pa2m_afirmar(
		elemento_desapilado == NULL,
		"pila_desapilar() no intenta eliminar elementos de una pila nula");
}

void pila_desapilar_no_intenta_eliminar_de_pila_vacia()
{
	pila_t *pila = pila_crear();
	void *elemento_desapilado = pila_desapilar(pila);

	pa2m_afirmar(
		elemento_desapilado == NULL,
		"pila_desapilar() no intenta eliminar elementos de una pila vacía");
	pila_destruir(pila);
}

void pila_desapilar_elimina_elemento_y_extrae_datos_correctamente()
{
	pila_t *pila = pila_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	int *elemento_eliminado = pila_desapilar(pila);

	pa2m_afirmar(
		*elemento_eliminado == 3,
		"pila_desapilar() elimina un elemento del tope y extrae sus datos correctamente");
	pila_destruir(pila);
}

void pila_desapilar_cambia_cantidad_de_elementos_correctamente()
{
	pila_t *pila = pila_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		pila_apilar(pila, &elementos[i]);
	}

	pila_desapilar(pila);

	pa2m_afirmar(
		pila_cantidad(pila) == 2,
		"pila_desapilar() cambia la cantidad de elementos correctamente");
	pila_destruir(pila);
}

void cola_crear_devuelve_cola_vacia()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "cola_crear() devuelve una cola vacía");
	cola_destruir(cola);
}

void cola_cantidad_toma_cola_nula_como_vacia()
{
	pa2m_afirmar(
		cola_cantidad(NULL) == 0,
		"cola_cantidad() recibe una cola nula y la asume como vacía");
}

void cola_cantidad_devuelve_valor_correcto()
{
	cola_t *cola = cola_crear();
	cola_t *cola_vacia = cola_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	pa2m_afirmar(
		cola_cantidad(cola) == 3 && cola_cantidad(cola_vacia) == 0,
		"cola_cantidad() devuelve el valor correspondiente de elementos presentes");
	cola_destruir(cola);
	cola_destruir(cola_vacia);
}

void cola_ver_primero_sobre_cola_nula_devuelve_null()
{
	void *elemento_tope = cola_ver_primero(NULL);
	pa2m_afirmar(
		elemento_tope == NULL,
		"cola_ver_primero() devuelve puntero nulo al usarse sobre una cola nula");
}

void cola_ver_primero_sobre_cola_vacia_devuelve_null()
{
	cola_t *cola = cola_crear();
	void *elemento_tope = cola_ver_primero(cola);

	pa2m_afirmar(
		elemento_tope == NULL,
		"cola_ver_primero() devuelve puntero nulo al usarse sobre una cola vacía");
	cola_destruir(cola);
}

void cola_ver_primero_extrae_datos_correctamente()
{
	cola_t *cola = cola_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	int *elemento_frente = cola_ver_primero(cola);
	pa2m_afirmar(
		*elemento_frente == 1,
		"cola_ver_primero() extrae correctamente los datos del elemento del frente");
	cola_destruir(cola);
}

void cola_encolar_no_agrega_elementos_a_cola_nula()
{
	int dato = 50;
	bool resultado_encolar = cola_encolar(NULL, &dato);

	pa2m_afirmar(
		!resultado_encolar,
		"cola_encolar() no intenta agregar elementos a una cola nula");
}

void cola_encolar_agrega_elemento_a_cola_vacia()
{
	cola_t *cola = cola_crear();
	int dato = 50;
	bool resultado_encolar = cola_encolar(cola, &dato);
	int *elemento_frente = cola_ver_primero(cola);

	pa2m_afirmar(
		resultado_encolar && *elemento_frente == 50,
		"cola_encolar() agrega un elemento correctamente a una cola vacía");
	cola_destruir(cola);
}

void cola_encolar_agrega_elemento_a_cola_no_vacia()
{
	cola_t *cola = cola_crear();
	int elementos[] = { 1, 2, 3 };
	bool resultado_encolar;
	for (size_t i = 0; i < 3; i++) {
		resultado_encolar = cola_encolar(cola, &elementos[i]);
	}

	cola_desencolar(cola);
	cola_desencolar(cola);
	int *elemento_final = cola_desencolar(cola);

	pa2m_afirmar(
		resultado_encolar && *elemento_final == 3,
		"cola_encolar() agrega un elemento correctamente a una cola no vacía");
	cola_destruir(cola);
}

void cola_encolar_cambia_cantidad_de_elementos_correctamente()
{
	cola_t *cola = cola_crear();
	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	pa2m_afirmar(
		cola_cantidad(cola) == 3,
		"cola_encolar() cambia la cantidad de elementos correctamente");
	cola_destruir(cola);
}

void cola_desencolar_no_intenta_eliminar_de_cola_nula()
{
	void *elemento_desencolado = cola_desencolar(NULL);
	pa2m_afirmar(
		elemento_desencolado == NULL,
		"cola_desencolar() no intenta eliminar elementos de una cola nula");
}

void cola_desencolar_no_intenta_eliminar_de_cola_vacia()
{
	cola_t *cola = cola_crear();
	void *elemento_desencolado = cola_desencolar(cola);

	pa2m_afirmar(
		elemento_desencolado == NULL,
		"cola_desencolar() no intenta eliminar elementos de una cola vacía");
	cola_destruir(cola);
}

void cola_desencolar_elimina_elemento_y_extrae_datos_correctamente()
{
	cola_t *cola = cola_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	int *elemento_desencolado = cola_desencolar(cola);

	pa2m_afirmar(
		*elemento_desencolado == 1,
		"cola_desencolar() elimina un elemento del frente y extrae sus datos correctamente");
	cola_destruir(cola);
}

void cola_desencolar_cambia_cantidad_de_elementos_correctamente()
{
	cola_t *cola = cola_crear();

	int elementos[] = { 1, 2, 3 };
	for (size_t i = 0; i < 3; i++) {
		cola_encolar(cola, &elementos[i]);
	}

	cola_desencolar(cola);

	pa2m_afirmar(
		cola_cantidad(cola) == 2,
		"cola_desencolar() cambia la cantidad de elementos correctamente");
	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("============== LISTA ===============");
	pa2m_nuevo_grupo(
		"============== Pruebas de funcionalidades básicas de lista ===============");
	lista_crear_devuelve_lista_vacia();
	lista_vacia_toma_lista_nula_como_vacia();
	lista_vacia_reconoce_lista_vacia();
	lista_vacia_reconoce_lista_no_vacia();
	lista_cantidad_toma_lista_nula_como_vacia();
	lista_cantidad_devuelve_0_con_lista_vacia();
	lista_cantidad_devuelve_valor_correcto();

	pa2m_nuevo_grupo(
		"============== Pruebas de manipulación de lista ===============");
	lista_agregar_no_agrega_elementos_a_lista_nula();
	lista_agregar_agrega_elemento_a_lista_vacia();
	lista_agregar_agrega_elemento_a_lista_no_vacia();
	lista_agregar_cambia_cantidad_de_elementos_correctamente();
	lista_insertar_no_agrega_elementos_a_lista_nula();
	lista_insertar_no_agrega_elementos_en_una_posicion_invalida();
	lista_insertar_no_agrega_elemento_a_lista_vacia();
	lista_insertar_agrega_elemento_al_principio_correctamente();
	lista_insertar_agrega_elemento_en_el_medio_correctamente();
	lista_insertar_no_agrega_elemento_al_final();
	lista_insertar_cambia_cantidad_de_elementos_correctamente();
	lista_eliminar_elemento_no_intenta_eliminar_de_lista_nula();
	lista_eliminar_elemento_no_intenta_eliminar_de_lista_vacia();
	lista_eliminar_elemento_no_intenta_eliminar_elemento_en_posicion_invalida();
	lista_eliminar_elemento_elimina_elemento_y_extrae_datos_correctamente();
	lista_eliminar_elemento_elimina_elemento_y_mantiene_orden();
	lista_eliminar_elemento_cambia_cantidad_de_elementos_correctamente();

	pa2m_nuevo_grupo(
		"============== Pruebas de funcionalidades de busqueda de lista ===============");
	lista_buscar_posicion_ignora_lista_nula();
	lista_buscar_posicion_ignora_comparador_nulo();
	lista_buscar_posicion_encuentra_elemento_presente();
	lista_buscar_posicion_devuelve_error_buscando_elemento_no_presente();
	lista_buscar_elemento_ignora_lista_nula();
	lista_buscar_elemento_ignora_posicion_invalida();
	lista_buscar_elemento_encuentra_elemento_presente();

	pa2m_nuevo_grupo(
		"============== Pruebas de iteradores externos y internos de lista ===============");
	lista_con_cada_elemento_ignora_lista_nula();
	lista_con_cada_elemento_ignora_funcion_nula_sobre_lista_valida();
	lista_con_cada_elemento_devuelve_cantidad_correcta_de_elementos_afectados();
	lista_con_cada_elemento_aplica_la_funcion_sobre_todo_elemento();
	lista_iterador_crear_no_crea_un_iterador_para_lista_nula();
	lista_iterador_hay_mas_elementos_toma_iterador_nulo();
	lista_iterador_hay_mas_elementos_reconoce_fin_de_lista();
	lista_iterador_obtener_actual_extrae_datos_correctamente();

	printf("\n\n\n\n");
	pa2m_nuevo_grupo("============== PILA ===============");
	pa2m_nuevo_grupo(
		"============== Pruebas de funcionalidades básicas de pila ===============");
	pila_crear_devuelve_pila_vacia();
	pila_cantidad_toma_pila_nula_como_vacia();
	pila_cantidad_devuelve_valor_correcto();
	pila_ver_primero_sobre_pila_nula_devuelve_null();
	pila_ver_primero_sobre_pila_vacia_devuelve_null();
	pila_ver_primero_extrae_datos_correctamente();

	pa2m_nuevo_grupo(
		"============== Pruebas de manipulación de pila ===============");
	pila_apilar_no_agrega_elementos_a_pila_nula();
	pila_apilar_agrega_elemento_a_pila_vacia();
	pila_apilar_agrega_elemento_a_pila_no_vacia();
	pila_apilar_cambia_cantidad_de_elementos_correctamente();
	pila_apilar_siempre_agrega_al_tope_de_la_pila();
	pila_desapilar_no_intenta_eliminar_de_pila_nula();
	pila_desapilar_no_intenta_eliminar_de_pila_vacia();
	pila_desapilar_elimina_elemento_y_extrae_datos_correctamente();
	pila_desapilar_cambia_cantidad_de_elementos_correctamente();

	printf("\n\n\n\n");
	pa2m_nuevo_grupo("============== COLA ===============");
	pa2m_nuevo_grupo(
		"============== Pruebas de funcionalidades básicas de cola ===============");
	cola_crear_devuelve_cola_vacia();
	cola_cantidad_toma_cola_nula_como_vacia();
	cola_cantidad_devuelve_valor_correcto();
	cola_ver_primero_sobre_cola_nula_devuelve_null();
	cola_ver_primero_sobre_cola_vacia_devuelve_null();
	cola_ver_primero_extrae_datos_correctamente();

	pa2m_nuevo_grupo(
		"============== Pruebas de manipulación de cola ===============");
	cola_encolar_no_agrega_elementos_a_cola_nula();
	cola_encolar_agrega_elemento_a_cola_vacia();
	cola_encolar_agrega_elemento_a_cola_no_vacia();
	cola_encolar_cambia_cantidad_de_elementos_correctamente();
	cola_desencolar_no_intenta_eliminar_de_cola_nula();
	cola_desencolar_no_intenta_eliminar_de_cola_vacia();
	cola_desencolar_elimina_elemento_y_extrae_datos_correctamente();
	cola_desencolar_cambia_cantidad_de_elementos_correctamente();

	return pa2m_mostrar_reporte();
}
