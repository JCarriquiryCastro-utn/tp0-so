#include "client.h"


int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "Hola! Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */
	// Usando el config creado previamente, leemos los valores del config y los
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	// Loggeamos el valor de config

	config = iniciar_config();
	ip = config_get_string_value (config, "IP");
	puerto = config_get_string_value (config, "PUERTO");
	valor = config_get_string_value (config, "VALOR");
	log_info(logger, "La IP %s , el puerto %s y el valor %s fueron leidos\n", ip, puerto, valor);




	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);
	//

	// Armamos y enviamos el paquete
	paquete(conexion);
	// enviar_paquete( , conexion);
	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "TP0", 1, LOG_LEVEL_INFO);
	if (!nuevo_logger){
		printf("El logger no pudo ser creado\n");
		exit(1);
	}
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	if((nuevo_config = config_create("./tp0.config")) == NULL){
		printf("La config no pudo ser leída\n");
		exit(2);
	}
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido = readline(">");;


	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	 while(!logger || strcmp(leido, "")) {
	        leido =
	        printf("%s\n", leido);
	        log_info(logger, leido);
	        free(leido);
	 }
	 // ¡No te olvides de liberar las lineas antes de regresar!
}

void paquete(int conexion)
{
	char* leido = readline("> ");
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete

	while (!strcmp(leido, "")) {
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
	}

	 enviar_paquete(paquete, conexion);

	 eliminar_paquete(paquete);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	if (logger != NULL){
		log_destroy(logger);
	}
	if (config != NULL){
		config_destroy(config);
	}
	if (conexion != NULL){
		liberar_conexion(conexion);
	}


}
