# TDA LISTA/PILA/COLA

## Repositorio de Ramiro Carrattini - 113212 - rcarrattini@fi.uba.ar

- Para compilar:

```bash
gcc src/*.c main.c -o lista
gcc src/*.c pruebas_alumno.c -o pruebas
```

- Para ejecutar:

```bash
./lista [archivo] buscar [id/nombre] [parametro a buscar]
./pruebas
```

- Para ejecutar con valgrind:
```bash
valgrind ./lista [archivo] buscar [id/nombre] [parametro a buscar]
valgrind ./pruebas
```
##  Funcionamiento
### Lista
La estructura principal de la lista contiene un puntero tanto al nodo inicial como al final, junto con un simple conteo para la cantidad de nodos existentes. Al ser simplemente enlazada, los nodos que la componen están formados únicamente por su contenido y una referencia al siguiente nodo de la lista. Se adjunta una visualización de la estructura:
![](https://i.imgur.com/jKBdEp3.png)

Estos dos punteros, junto con la cantidad de nodos, se mantienen dinámicamente a medida que se manipula la lista.
Existen varias operaciones para realizar:
-- **lista_crear()**: Crea una lista vacía. Internamente, se realiza una reserva de memoria y se inicializan los 3 campos de la estructura mediante asignaciones simples. Su complejidad es O(1).
-- **lista_vacia()**: Comprueba si la lista tiene elementos. Internamente, se realizan chequeos simples relacionados a la cantidad y los dos punteros. Su complejidad es O(1).
-- **lista_cantidad()**: Devuelve la cantidad actual de elementos presentes en la lista. Simplemente se devuelve el valor actual de *cantidad_nodos*, por lo que su complejidad es O(1).
-- **lista_agregar()**: Agrega un elemento al final de la lista. Se reserva memoria para un nuevo nodo, se utiliza el puntero *fin* para obtener el último nodo, y luego se coloca el nuevo nodo despúes de este mediante asignaciones simples. Se actualiza el puntero *fin*. Su complejidad es O(1). Una visualización simplificada de lo que hace la función se puede ver en el siguiente diagrama:
![](https://i.imgur.com/BuPatCF.png)
-- **lista_insertar()**: Agrega un elemento en una posición especifica de la lista. Esta acción implíca encontrar tanto al nodo que está en la posición a insertar como su anterior, para poder actualizar sus referencias y mantener un orden. Para esto es necesario iterar sobre la lista, por lo que su complejidad es O(n). Una visualización simplificada de lo que hace la función se puede ver en el siguiente diagrama:
![](https://i.imgur.com/NQIOwGa.png)
-- **lista_eliminar_elemento()**: Elimina un elemento en una posición especifica de la lista. Similar a la función anterior, requiere iterar sobre la lista para encontrar nodos especificos. Su complejidad es O(n). Una visualización simplificada de lo que hace la función se puede ver en el siguiente diagrama:
![](https://i.imgur.com/NYqYwUm.png)
-- **lista_buscar_posicion()**: Devuelve la posición dentro de la lista del elemento buscado. Itera sobre cada nodo de la lista hasta que el comparador devuelva un valor que indique que se ha encontrado el elemento. Su complejidad es O(n).
-- **lista_buscar_elemento()**: Devuelve el elemento que está en una posición especifica de la lista. Itera sobre cada nodo de la lista hasta encontrar el elemento buscado, similar a la función anterior. Su complejidad es O(n).
-- **lista_con_cada_elemento()**: Empieza a aplicar la función pasada por parametro a cada elemento de la lista, parando si la esta devuelve false. Su complejidad depende de que función se está aplícando: si se piensa a *x* como la complejidad individual de la esta, y teniendo en cuenta que la iteración en si tiene una complejidad de O(n), su complejidad final es O(n*x*).
-- **lista_destruir_todo()**: Destruye la lista y aplíca la función destructora pasada por parametro al contenido de cada nodo. Su complejidad es O(n*x*), siguiendo la misma idea que la función anterior.
-- **lista_destruir()**: Itera sobre cada nodo de la lista, liberando la memoria que ocupan las estructuras individuales. Su complejidad es O(n).
-- **lista_iterador_crear()**: Crea un iterador externo. Internamente, se realiza una reserva de memoria y una asignación simple de valores.  Su complejidad es O(1).
-- **lista_iterador_hay_mas_elementos()**: Verifica si se ha iterado sobre todos los elementos de la lista. Esto se hace con un chequeo simple: si el nodo actual no es nulo, no se ha llegado al final de la lista. Su complejidad es O(1).
-- **lista_iterador_siguiente()**: Avanza al siguiente nodo. Se hace con una asignación simple de valores. Su complejidad es O(1).
-- **lista_iterador_obtener_actual()**: Devuelve el contenido del nodo actual. Su complejidad es O(1).
-- **lista_iterador_destruir()**: Destruye el iterador externo. Siendo un simple *free*, su complejidad es O(1).

### Pila
La pila fue implementada a partir de una lista, por lo que su estructura principal es simplemente un puntero a *lista_t*. Se detallará como se manipuló la lista para que se comporte como una pila.
Se pueden realizar las siguientes operaciones sobre la pila:
-- **pila_crear()**: Crea una pila vacía. Internamente, se reserva memoria para la estructura principal, luego se crea una nueva lista a la que apuntar mediante *lista_crear()*. Su complejidad es de O(1).
-- **pila_apilar()**: Apila un elemento sobre el tope. El llamado que realiza está función depende de la cantidad de elementos presentes:
```bash
bool  pila_apilar(pila_t  *pila,  void  *elemento){
	if  (pila  ==  NULL){
		return  false;
	}
	if  (pila_cantidad(pila)  ==  0){
		return  lista_agregar(pila->lista,  elemento);
	}
	return  lista_insertar(pila->lista,  elemento,  0);
}
```
Si la pila está vacía, se llama a *lista_agregar()* y se hereda su complejidad de O(1). Caso contrario, se llama a *lista_insertar()*, con la posición 0. Esta función normalmente es O(n), pero como no es necesario iterar para buscar un nodo anterior (no existe) o siguiente (es al que apunta *inicio*), se puede insertar mediante asignaciones simples. Teniendo en cuenta estos dos casos, la complejidad resultante de la función es de O(1).
-- **pila_desapilar()**: Desapila el elemento en el tope. Internamente, se realiza un llamado a *lista_eliminar_elemento()*, con la posición 0. Similar a la función anterior, esta función reconoce el caso y llama a *lista_eliminar_inicio()*, la cual es O(1).
-- **pila_ver_primero()**: Devuelve el elemento en el tope de la pila. Esto es equivalente a mostrar el primer elemento de la lista, y se realiza con un llamado a *lista_buscar_elemento()*. A esta función se le pasa la posición 0, por lo que en este caso no necesita iterar y es O(1).
-- **pila_cantidad()**: Devuelve la cantidad de elementos en la pila. Es un llamado simple a lista_cantidad(). Su complejidad es O(1).
-- **pila_destruir()**: Destruye la pila. Los elementos existentes en memoria dinámica deberán ser liberados manualmente por el usuario después de eliminar. Internamente, se llama a *pila_desapilar()* para cada elemento de la pila, y luego se libera la memoria que ocupan las estructuras. Su complejidad es O(n).

### Cola
La cola, similar a la pila, también es una versión modificada de la lista. Comparten la misma estructura principal. Se detallará como se manipuló la lista para que se comporte como una cola.
Se pueden realizar las siguientes operaciones sobre la cola:
-- **cola_crear()**: Crea una cola vacía. Internamente, se reserva memoria para la estructura principal, luego se crea una nueva lista a la que apuntar mediante *lista_crear()*. Su complejidad es de O(1).
-- **cola_encolar()**: Agrega un elemento al final de la cola. Esto se hace con una llamada a lista_agregar(). Se hereda su complejidad de O(1).
-- **cola_desencolar()**: Elimina el elemento al frente de la cola. Se realiza un llamado a *lista_eliminar_elemento()*, con la posición 0. Esta función reconoce el caso y llama a *lista_eliminar_inicio()*, la cual es O(1).
-- **cola_ver_primero()**: Devuelve un puntero al elemento al frente de la cola. Esto es equivalente a mostrar el primer elemento de la lista, y se realiza con un llamado a *lista_buscar_elemento()*. A esta función se le pasa la posición 0, por lo que en este caso no necesita iterar y es O(1).
-- **cola_cantidad()**: Devuelve la cantidad de elementos en la cola. Es un llamado simple a lista_cantidad(). Su complejidad es O(1).
-- **cola_destruir()**: Destruye la cola. Los elementos existentes en memoria dinámica deberán ser liberados manualmente por el usuario después de eliminar. Internamente, se llama a *cola_desencolar()* para cada elemento de la pila, y luego se libera la memoria que ocupan las estructuras. Su complejidad es O(n).

## Flujo del programa
El programa empieza por imprimir un mensaje de bienvenida. Luego, controla que lo ingresado por línea de comando sea lo esperado. Si se llega a detectar una falla, se imprime un error detallando que sucedió mal, y se muestran las instrucciones por pantalla:
![](https://i.imgur.com/FINv5Lr.png)
Si se pasan los controles iniciales, se empiezan a leer los Pokémon del archivo especificado, y se guardan dentro de un tp1_t utilizando *tp1_leer_archivo()* (Proceso detallado en [este proyecto](https://github.com/ramichul/TP1-ENUNCIADO/settings)). 
Se crea la lista, y se cargan los Pokémon utilizando la función *cargar_pokedex_en_lista()*:
#### cargar_pokedex_en_lista()
1. Se empieza a iterar utilizando *tp1_con_cada_pokemon()* con la función *agregar_pokemon_a_lista()*. Esta función llama a *lista_agregar()* con el Pokémon como parámetro.
2. Si ocurre algún error, se imprime un mensaje avisandole al usuario y se aborta la carga. Se libera la memoria y termina el funcionamiento del programa.
3. Se sigue el ciclo hasta lograr cargar todos los Pokémon de la Pokédex.
4. Una vez logrado, se termina el proceso sin errores y continua el flujo del programa.

Cuando finaliza el proceso de carga de Pokémon a la lista, la siguiente función que se llama es *ejecutar_comando_busqueda()*:

#### ejecutar_comando_busqueda()
1. Se procesan los argumentos pasados por línea de comando para identificar que tipo de busqueda se debe realizar.
2. Se llama a *lista_buscar_posicion()* con el dato y comparador aptos para la tarea.
3. Si no se encuentra el Pokémon, se imprime un mensaje avisandole de este error al usuario. Se libera la memoria y termina el funcionamiento del programa.
4. Caso contrario, se imprimen los datos del Pokémon por pantalla y continua el flujo del programa.

Al finalizar la busqueda, se considera finalizado el uso del programa, se libera la memoria utilizada y se sale del programa sin errores.

## Respuestas a las preguntas teóricas
   - **Explicar qué es una lista, lista enlazada y lista doblemente enlazada.**
     - **Explicar las características de cada una.**
 Una lista es un *Tipo de Dato Abstracto* (TDA de ahora en adelante) que permite almacenar distintos elementos dentro de ella. Su principal carácteristica es que no sigue ningún "*principio de manipulación*" de elementos: para el usuario, todo elemento está disponible para su acceso, y en ningún momento se restringe este mismo. Los elementos dentro de esta lista siguen un orden especificado, y el lugar de cada elemento es numerado con un *índice*.
Ambas listas simplemente y doblemente enlazadas se implementan mediante otro TDA, el *nodo*, un contenedor para los datos que ademas dispone de una referencia a su siguiente (en caso de una lista *simplemente* enlazada) y su anterior (si es una lista *doblemente* enlazada). La lista en sí siempre mantiene una referencia a su primer nodo.

     - **Explicar las diferencias internas de implementación.**
    Existen varias maneras de implementar una lista, sea con un vector estático o dinámico o mediante nodos. Estos dos primeros se podrían considerar los más faciles de implementar, ya que no implícan un TDA separado como lo hacen las listas simple y doblemente enlazadas. El último método de implementación puede resultar mucho más complejo porque requiere un entendimiento sólido de los nodos, su manipulación y su comportamiento bajo diferentes casos.
    En los siguientes diagramas se pueden ver como quedan dispuestos los elementos en la memoria para cada implementación de una lista:
  ![](https://i.imgur.com/CIPWkRJ.png)
    
     - **Explicar ventajas y desventajas de cada una, si existen.**
     La ventaja principal de las listas enlazadas es que no requieren reservas de regiones *contiguas*  dentro de la memoria, si no que se reserva una pequeña región dentro de la memoria cada vez que se crea un nodo. Esto puede sumar a las desventajas de una lista implementada mediante un vector, ya que esta siempre requiere la reserva de una región contigua dentro de la memoria. En cambio, la ventaja que tiene esta sobre sus alternativas es la simplicidad de su implementación.
     Dentro de las listas implementadas con vectores, la lista basada en un vector estático es la mas desventajosa por su espacio *limitado* de almacenamiento, cosa que puede resultar contraproducente en las situaciones donde se suele usar una lista. Una lista que utiliza un vector dinámico no tiene esta desventaja, aunque sigue sufriendo necesitar espacio contiguo en la memoria.
     Dentro de las listas enlazadas, la lista simplemente enlazada tiene una ventaja sobre la doblemente enlazada también por su simplicidad, mientras que la lista doblemente enlazada gana en el frente de facilidad de manipulación al poder navegarse en ambas direcciones.
     
   - **Explicar qué es una lista circular y de qué maneras se puede implementar**.
Una lista circular es una implementación alternativa en donde el elemento final y el primer elemento de la lista tienen algún tipo de vínculo. En el caso de una lista simplemente enlazada, el último nodo podría contener una referencia al primer nodo de la lista, en vez de tener un siguiente nodo nulo. Si se trata de una lista doblemente enlazada, el primer y ultimo nodo podrían estar conectados entre sí de dos formas posibles. De esta manera la lista realmente no tiene un "fin", si no que se presenta como una especie de anillo.
En el siguiente diagrama se puede observar una lista circular dentro de la memoria, con dos puntos de vista diferentes: La vista estándar horizontal de una lista circular y simplemente enlazada dentro de la memoria, y la vista "*anillo*" para representar bien el concepto de el inicio y fin conectados. En el último diagrama se omiten los espacios entre casillas de memoria y se asume un orden para la facilidad de interpretación.
![](https://i.imgur.com/oRDklNC.png)

   - **Explicar la diferencia de funcionamiento entre cola y pila.**
Una cola y una pila son ambas una colección de elementos en orden, como lo es la lista. La diferencia entre como funcionan radíca en como se pueden manipular y/o acceder a sus elementos:
Una cola sigue el principio *FIFO* (First In, First Out), es decir, el primer elemento en entrar es además es el primero en salir, como ocurriria por ejemplo con una cola en un supermercado. Se encola por el final, y se desencola por el frente.
Por otro lado, una pila sigue el principio *LIFO* (Last In, First Out). El ultimo elemento en entrar es el primero en salir: si se piensa, por ejemplo, en una pila de papeles a revisar, generalmente los primeros en ser vistos son los más recientes. Se apila y desapila por el elemento de arriba, o el *tope*.
Se puede observar como se mueven los elementos dentro de una cola o una pila en los siguientes diagramas:
![](https://i.imgur.com/mDnPLu0.png)

- **Explicar la diferencia entre un iterador interno y uno externo.**
Un iterador interno es aquel que recibe únicamente una función del usuario, y luego se encarga de aplicarla sobre cada elemento de la colección. Es decir, la iteración no está a cargo del usuario, solo que se hace con ella. 
Por otro lado, cada paso del iterador externo está a cargo del usuario: el usuario elige cuando avanzar y cuando no, cuando aplicar una función y cuando no, que funciones aplicar sobre que elementos, etc.. Se dá la libertad total al usuario de iterar sobre la lista como lo necesite.
