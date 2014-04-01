/** --- Librerías utilizadas --- **/

#include <stdio.h>             // Declaraciones utilizadas para entrada y salida de datos
#include <stdlib.h>            // Libreria estándar, utilizada en manejo de hileras
#include <unistd.h>            // Llamadas al sistema ---> fork ()
#include <string.h>            // Definiciones utilizadas para la manipulacion de cadenas de caracteres
#include <sys/types.h>         // Definiciones de estructuras utilizadas por la funcion socket
#include <sys/socket.h>        // Definiciones de estructuras utilizadas por la funcion socket
#include <netinet/in.h>        // Definiciones para el manejo de red
#include <netdb.h>             // Definiciones para el manejo de la base de datos de la red

/** Macros utilizadas **/

#define escape "Chao\n"        // Define la palabra de cierre de la conversación: Chao

/** --- Variables globales a utilizar --- **/

// Usuario

char user[30];                 // Contiene el nombre del usuario con el que se registro en el sistema
char port[8];                  // COntiene el puerto del usuario con el que se registro en el sistema


// Contacto

char ip[16];                   // Contiene la IP del contacto inmediato al que se le va a enviar un mensaje
char puerto[8];                // Contiene el puerto del contacto al que se va a enviar el mensaje





/** Declaración de las funciones a utilizar  **/


// Las funciones devuelven un entero como buena practica de programacion (variables de estado)

// Menu y metodos de entrada al sistema

int Menu();
int Ingresar();
int NuevoUsuario();


// Carga de datos del usuario del sistema

int CargarPuerto();
int Verificar(char[],char[]);
int ExisteUsuario(char[]);


// Manejo de contactos

int NuevoContacto();
int ValidarContacto(char[]);
int MostrarContactos();
int BuscarContacto(char[],char[]);


// Envio y recepcion de mensajes

int CargarDatosContacto(char[]);
int Messenger();
int FServidor(int);
int Usuario(const char[], int);


/*
    Funcion de impresion de errores.
    Brinca a ciertas funcionalidades del programa dependiendo del tipo de error
*/

void Error(char *msj_error, int tipo){                            // Recibe un arreglo de caracteres como mensaje de error y un tipo de error
	printf("%s\nPor favor intentelo nuevamente\n",msj_error);
	
	if (tipo == 0){
		exit(0);             // - Cierra el programa
	}
	
	else if (tipo == 1){
		system("clear");
		Menu();              // Se llama a la funcion Menu		
	}
	
	else if (tipo == 2){
		system("clear");
		Ingresar();	         // Se llama a la funcion Ingresar		
	}

}

/** Inicialización del Main **/

void main () {
	printf("\033[37m Bienvenido al Messenger para C        \n");
	Menu ();              // Se carga el Menu Principal e inicia el programa
	
}


/** #######    Menu principal    ####### **/


// Se le pregunta al usuario si desea registrarse en el sistema o acceder con un usuario existente


int Menu(){
	printf("\033[0m                Menú principal                  \n Seleccione la opcion que desea:\n 1)Ingresar con un usuario existente\n 2)Regitrarse en el sistema \n Digite 0 para salir del programa\n");
	
	int salir = 0;
	int opcion;
	
	while(salir == 0){
		
		opcion = -1;
		fflush(stdin);
		
		scanf("%d",&opcion);       // Se lee la opcion ingresada por el usuario
			
		if (opcion == 1){
			system("clear");       // Se llama a la función Ingresar
			Ingresar();
			Menu();}
			
		else if (opcion == 2){
			system("clear");
			NuevoUsuario();        // Se llama a la función NuevoUsuario
			Menu();}
			
		else exit(0);
	}
	
	return 0;    // Finaliza exitosamente
}


/** Opciones del Menu principal **/




// 1. Inicio de sesion con un usuario existente

int Ingresar(){
	
	printf("\033[32m Ingrese su nombre de usuario y presione la tecla Enter");
	
	
	scanf("%s",user);   // Se asigna a la variable global 'user' el nombre ingresado por el usuario
	
	
	// Se verifica que existe el usuario en el sistema
	
	if(!ExisteUsuario(user)){   // Si NO existe
		Error("No existe el usuario ingresado",1);
	}
	
	
	// Se ejecuta la funcion para cargar el puerto del usuario registrado.
	
	CargarPuerto();
	
	
	// Se ejecuta la funcion para iniciar con el envio y recepcion de mensajes
	
	Messenger();
	
}

// 2. Registro de un nuevo usuario


int NuevoUsuario{
	
	// Variables locales
	
	char usuario[30];
	char puerto[8];
	
	printf("\033[32m Ingrese los datos que se le solicitan a continuacion\n");
	
	printf("\033[39m Nombre de usuario:");
	scanf(" %[^\n]",usuario);
	
    printf("Puerto a utilizar:");
	scanf(" %[^\n]",puerto);
	
	strcat(usuario, ".txt");             // Se agrega la extension del archivo a crear utilizando el nombre del usuario
	
	// Se verifica si ya el usuario existe
	
	if(ExisteUsuario(usuario)){   // Si existe
		Error("Ya existe el usuario ingresado",2);
	}
	
	FILE *archivo;		
	
	archivo = fopen(usuario,"wb");       // Crea el archivo correspondiente al usuario
	
	fprintf(archivo,"%s",puerto);        // Nota: REVISAR si se debe de agregar el salto de linea 
	fclose(archivo);
	
	printf("\033[30m Se ha creado el usuario exitosamente");
	
	if(access  )
	
	// Se le pregunta al usuario si desea ingresar al sistema con su nueva cuenta o desea cerrar el programa
	
	int opcion;
	
	scanf("Presione 1 para ingresar al sistema con su usuario u otra tecla para Salir del programa:\n%d",&opcion);
	
	if (opcion == 1){
		system("clear");
		Ingresar();
	}
	else {
		exit(0);
		}

		
	return 0;  // Ejecucion finaliza con exito
	
}

// Funcion que verifica si existe un archivo asignado al usuario en el sistema, es decir, si este esta registrado

int ExisteUsuario(char *nombre_archivo)
{
  struct stat   buffer;   
  return (stat (nombre_archivo, &buffer) == 0);
}

/** !!!!! Manejo de contactos !!!!! **/



// Mostrar la lista de contactos de un usuario

int MostrarContactos( ){
	
	FILE *archivo;         // Se apunta a la dirección del archivo
	
	// Revisar las 2 opciones de hacer este paso
	
	// 1. Opcion
	char *archivo_usuario = strcat(user, ".txt"); // Apunta al archivo correspondiente al usuario
	
	/* 2. Opcion
	
	char archivo_usuario[30] = user;
	strcat(archivo_usuario, ".txt");
	
	*/
	     
    archivo = fopen(archivo_usuario,"r");  // Almacena la dirección del archivo
    
    char caracteres[50];   // Buffer de caracteres a leer
    
    // Se verifica que el usuario tenga contactos
    
    int ch;
	int lines = 0;
	
	while (EOF != (ch=getchar()))
	if (ch=='\n')
	++lines; 
	
	if (lines < 2)  {
		 printf("\033[31m No se tiene ningun contacto registrado\n");
		 Menu();                        // Se regresa al Menu principal
	 }
	
	// Se muestran los contactos existentes 
     
    while (feof(archivo) == 0) {        // Mientras que no sea el final del documento
        fgets(caracteres,50,archivo);
        
        if(feof(archivo) == 0)
		printf("\033[33m %s",caracteres);       
        }
        fclose(archivo);   // Cierra el documento
        
        return 0;  // Ejecucion finaliza con exito
	 
}




// Añadir un nuevo contacto

int NuevoContacto( ){
	
	FILE *archivo;
	char *usuarios = strcat(user, ".txt");   // Apunta al archivo correspondiente al usuario
	
			
	// Variables locales
	
	char usuario[30];
	char ip[16];
	char puerto[8];
		
	archivo = fopen(usuarios,"a");           // Agrega los datos al final del archivo
	if(archivo == NULL) return -1;
			
		
	printf("\033[34m Ingrese el nombre del usuario a agregar:");
	scanf(" %[^\n]",usuario);
	
	if(!ValidarContacto(usuario))Menu();    // Si el usuario ya existe se devuelve al menu
	
	printf("Ingrese el IP:");
	scanf(" %[^\n]",ip);
	printf("Ingrese el Puerto:");
	scanf(" %[^\n]",puerto);
		
	fprintf(archivo,"%s\n",usuario);
	fprintf(archivo,"%s\n",ip);
	fprintf(archivo,"%s\n",puerto);
	fclose(archivo);
		
	return 0;  // Ejecucion finaliza con exito
		
}


/** @@@@@@@  Funciones auxiliares @@@@@@@ **/

// Función auxiliar para comparar una linea del archivo con el usuario que se recibe

int BuscarContacto(char contacto[],char linea[]){
		int a = strlen(contacto);
		int b = strlen(linea);
		int cont=0; 
		if(a!=b-1){
			return 0;   // No se encuentra
		}
		else{
			while(cont+1!=a){
				contacto[cont]!=linea[cont]){
					    // No se encuentra
				return 0;
								
				}cont++;
			} 
			return 1; // Se encontro el contacto
					
		}
	}
	
// Funcion auxiliar para cargar el puerto del usuario

int CargarPuerto(){
	
	// Se carga el puerto del usuario ingresado (a ser utilizado por el servidor)
	
	FILE *archivo;
	char *usuario_archivo = strcat(user, ".txt");   // Apunta al archivo correspondiente al usuario
	
	archivo = fopen(usuario_archivo,"r");           
	
	fgets(port,9,archivo);                          // Se lee el puerto de usuario (solo la primer linea del archivo) y es asignado a la variable global 'port'
	
	fclose(archivo);
		
	return 0;  // Ejecucion finaliza con exito
		
}

/** ^^^^^^ Manejo de mensajes ^^^^^^ **/


// Cargar las variables de IP y puerto ingresando el nombre de usuario

int CargarDatosContacto(char[] contacto){
	
	FILE *archivo;
	char caracteres[40];
	
	char *usuario = contacto;
	strcat(usuario, ".txt");
	
	int i=0;  // Recorrido de lineas
	archivo = fopen(usuario,"r");  // Se trata de abrir el archivo del usuario registrado
        			
	while (feof(archivo) == 0)  // Recorre el archivo buscando el contacto solicitado
	{
		fgets(caracteres,30,archivo);    // Buffer
		
		if(((BuscarContacto(usuario,caracteres))==1)||(i>0)){
			if(i==1)strcpy(ip,caracteres);           // Se copia la IP del contacto
			if(i==2){strcpy(puerto,caracteres);      // Se copia el puerto del contacto
			i=0;
			break;}
						
			i++;
		}
						
	}
	
	fclose(archivo);
	return 0;
	 
}
	
// Funcion general para el envio y recepcion de mensajes

int Messenger(){
	
	char usuario[40];
	
	printf("\nBienvenido al Chat C\n\n");
	printf("\033[34m Ingrese el nombre del contacto con el que se desea comunicar:");
	scanf("%s",usuario);
	
	CargarDatosContacto(usuario);
	
	int proceso = fork();                  // Se lleva a cabo la bifurcacion
	
	// Funcion atoi cambia de tipo string a int para el manejo interno de los puertos
	
	int puertoServidor = atoi(port);       // Puerto del servidor
    int puertoUsuario = atoi(puerto);      // Puerto del cliente
    const char *IP = ip;                   // Se le asigna la ip del contacto ingresado a una nueva variable constante


    if(proceso == 0){                       // Si aun no hay un proceso padre creado
	FServidor(puertoServidor);
    }
    else{                                   // Crea el proceso hijo
	Usuario(IP, puertoUsuario);
    }   
	
	
}

/* #############################  
 *     Funcion del Cliente
 * #############################
*/

void Usuario (const char *IP, int puertoUsuario){ //Función que crea el proceso usuario (recibe la IP y el puerto del usuario)

int Conexion;                             //  Variable de Identificacion del Estado de Conexion

struct sockaddr_in DirServidor;
struct hostent *servidor;
char buffer[256];


int socketServidor = socket(AF_INET, SOCK_STREAM, 0);

if (socketServidor < 0){
fprintf(stderr,"Fallo en la Creación del Socket. \n\a");
exit(1);
}



servidor = gethostbyname(IP);


if (servidor == NULL) {
Error("El Servidor solicitado no está disponible. \a\n",2);
}

DirServidor.sin_family = AF_INET;


bcopy((char *)servidor->h_addr,(char *)&DirServidor.sin_addr.s_addr, servidor->h_length);   //  Copia características del Socket Servidor

DirServidor.sin_port = htons(puertoUsuario);


int contador = 0;

while(1){                                    //  Espera la conexion con el Usuario

if (Conexion >= 0){
	printf("Conexión Habilitada\n");
	break;
}
else{
	Conexion = connect(socketServidor,(struct sockaddr *) &DirServidor,sizeof(DirServidor));
}
}


while(1){

bzero(buffer,256); //Limpieza del buffer con bzero

fgets(buffer,255,stdin);//Se obtiene del bash la información

printf("\033[A\033[2K\033[01;34m""ENVIADO:\033[00;36m %s",buffer);//Imprime datos en pantalla. Colores 033[01;34m -> Azul, \033[00;36m -> Cyan				


if(strcmp(buffer,escape)==0){ //Busca del proceso hijo-usuario y lo finaliza cuando se escribe la palabra Chao

write(socketServidor, buffer, strlen(buffer));//Escribe Chao en el buffer para cerrar el proceso

int identhij = getpid();//Se obtiene el ID del proceso usuario
identhij++;
printf("\nConversación Terminada. ¡Qué tenga buen día!\n");
kill(identhij, SIGKILL);//Funcion que termina el proceso de acuerdo al numero establecido
break;
}

else{
write(socketServidor, buffer, strlen(buffer));//sino se escribe normalmente en el socket la cadena a enviar
}
}

close(socketServidor);
}


/* #############################  
 *     Funcion del Servidor
 * #############################
*/


void FServidor(int puertoServidor){                       // Crea el servidor en el sistema, recibe el puerto desde el main

char buffer[256];                                         // Mensaje a enviar, Tamaño definido en 256 


struct sockaddr_in DirServidor;                           // Referencia a los elementos del socket nativo
struct sockaddr_in DirUsuario;                            // Referencia a los elementos del socket del usuario


int SSer = socket(AF_INET, SOCK_STREAM, 0);

if (SSer < 0) {                                           // Manejo de errores si no se logra la creación del socket
Error("Fallo en la Creación del Socket\n",2);
}

// Conexion entrante (usuario)

DirServidor.sin_family = AF_INET;                                   // Protocolo ARPA
DirServidor.sin_addr.s_addr = INADDR_ANY;                           // Protocolo para el uso de la IP definida

DirServidor.sin_port = htons(puertoServidor);                       // Asignación del puerto servidor al socket nativo con htons, htons: Nodo a variable corta de Red

bind(SSer, (struct sockaddr *) &DirServidor,sizeof(DirServidor));   // Unión del socket servidor con el socket entrante

listen(SSer,2);                                                     // función listen() se usa si se están esperando conexiones entrantes

socklen_t largoDirUsuario;                                          // Variable de dirección de tipo socket
largoDirUsuario = sizeof(DirUsuario);                               // Asignación a la variable del largo de la direccion del socket


int SUsu = accept(SSer, (struct sockaddr *) &DirUsuario, &largoDirUsuario);


while(1){ // ciclo de lectura del buffer del socket para su muestra en consola
bzero (buffer,256);

read(SUsu, buffer, 255);

		
printf(	"\033[2K\r\033[01;31m""RECIBIDO:\033[00;36m %s",buffer); // Colores 033[01;31m -> Rojo, \033[00;36m -> Cyan

if(strcmp(buffer, escape)==0){        //  Busca el proceso padre-servidor y lo finaliza cuando se escribe la palabra "Chao"

int idenPad = getpid();

idenPad--;

printf("\nConversación Terminada. ¡Qué tenga buen día!\n");
kill(idenPad, SIGKILL);
break;
}

} // Se cierran los sockets utilizados (Servidor y Cliente)
close(SSer);
close(SUsu);
}
