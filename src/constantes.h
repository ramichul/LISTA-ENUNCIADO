#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#define MSJ_BIENVENIDA \
	"\033[38;5;222;1m\n🔴⚪ ¡Bienvenido al traductor de Pokédex a lista! ⚪🔴\n\n\033[0m"
#define MSJ_INSTRUCCIONES \
	"El modo de uso es \033[38;5;223m./lista [archivo] buscar [id/nombre] [parametro a buscar]\033[0m.\n\nVuelva a correr el programa por terminal utilizando el formato especificado.\n\n"
#define MSJ_PROCESAMIENTO "Procesando archivo: \033[38;5;223m%s\033[0m...\n"
#define MSJ_ERR_LECTURA \
	"\n\033[38;5;202;1mERROR\033[0m: Ocurrió un error al leer el archivo. Por favor, vuelva a intentar.\n\n"
#define MSJ_ERR_LISTA \
	"\n\033[38;5;202;1mERROR\033[0m: Ocurrió un error al reservar memoria para la lista. Por favor, vuelva a intentar.\n\n"
#define MSJ_ERR_COMANDO \
	"\n\033[38;5;202;1mERROR\033[0m: Nombre inválido de comando: \033[38;5;223m%s\033[0m. "
#define MSJ_ERR_INSTRUCCION \
	"\n\033[38;5;202;1mERROR\033[0m: Nombre inválido de instrucción: \033[38;5;223m%s\033[0m. "
#define MSJ_ERR_PARAM \
	"\n\033[38;5;202;1mERROR\033[0m: Parámetro inválido: \033[38;5;223m%s\033[0m. La busqueda por ID solo acepta enteros positivos. "
#define MSJ_ERR_CARGA \
	"\n\033[38;5;202;1mERROR\033[0m: No se pudo cargar todos los Pokémon en la lista. Por favor, vuelva a intentar.\n\n"
#define MSJ_ERR_BUSQUEDA \
	"\n\033[38;5;202;1mERROR\033[0m: El Pokémon buscado no está presente en la lista. Por favor, vuelva a intentar.\n\n"
#define MSJ_PROCESAMIENTO_EXITOSO "Procesado con éxito!\n"
#define MSJ_DATOS \
	"\n\033[38;5;223;1mDATOS DEL POKÉMON:\033[0m\n\n\033[38;5;223mID:\033[0m %i\n\033[38;5;223mNOMBRE:\033[0m %s\n\033[38;5;223mTIPO:\033[0m %s\n\033[38;5;223mATAQUE:\033[0m %i\n\033[38;5;223mDEFENSA:\033[0m %i\n\033[38;5;223mVELOCIDAD:\033[0m %i\n\n"

#define COMANDO_VALIDO "buscar"
#define INSTRUCCION_VALIDA_1 "id"
#define INSTRUCCION_VALIDA_2 "nombre"

extern const int CANT_ESPERADA_ARGUMENTOS;
extern const int ERR_CONTROL, ERR_LECTURA, ERR_LISTA, ERR_COMANDO, ERR_CARGA,
	ERR_BUSQUEDA;
extern const char *NOMBRES_COMPLETOS_TIPOS[];

#endif // CONSTANTES_H_