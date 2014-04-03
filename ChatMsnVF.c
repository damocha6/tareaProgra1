/** --- Librerías utilizadas --- **/

#include <stdio.h>             // Declaraciones utilizadas para entrada y salida de datos
#include <stdlib.h>            // Libreria estándar, utilizada en manejo de hileras
#include <unistd.h>            // Llamadas al sistema ---> fork ()
#include <string.h>            // Definiciones utilizadas para la manipulacion de cadenas de caracteres
#include <sys/types.h>         // Definiciones de estructuras utilizadas por la funcion socket
#include <sys/socket.h>        // Definiciones de estructuras utilizadas por la funcion socket
#include <netinet/in.h>        // Definiciones para el manejo de red
#include <netdb.h>             // Definiciones para el manejo de la base de datos de la red
#include <signal.h>



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
int GuardarPuerto();

// Carga de datos del usuario del sistema

int Verificar(char[],char[]);
int CargarPuerto();

// Manejo de contactos

int ValidarContacto(char[]);
int NuevoContacto();
int MostrarContactos();
int BuscarContacto(char[],char[]);


// Envio y recepcion de mensajes

int CargarDatosContacto(char[]);
int Messenger();
void FServidor(int);
void Usuario(const char[], int);


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
		MostrarContactos();	         // Se llama a la funcion MostrarContactos		
	}

}

/** Inicialización del Main **/

void main () {
	printf("\033[37m Bienvenido al Messenger para C        \n");
	GuardarPuerto();              // Se le solicita el puerto a utilizar al usuario
	
}


/** #######    Menu principal    ####### **/


// Menu principal del programa


int Menu(){
	printf("\033[34m            Menú principal         \n \033[0m Seleccione la opcion que desea realizar\n1)Ver la lista de contactos\n2)Agregar un contacto\n3)Iniciar una conversacion \n Digite 0 para salir del programa\n");
	
	int salir = 0;
	int opcion;
	
	while(salir == 0){
		
		opcion = -1;
		fflush(stdin);
		
		scanf("%d",&opcion);       // Se lee la opcion ingresada por el usuario
			
		if (opcion == 1){
			system("clear");       // Se llama a la función MostrarContactos
			MostrarContactos();
			Menu();}
			
		else if (opcion == 2){
			system("clear");
			NuevoContacto();        // Se llama a la función NuevoContacto
			Menu();}
			
		else if (opcion == 3){
			system("clear");
			Messenger();        // Se llama a la función Messenger
			Menu();}
			
		else
		
		system("clear");
		exit(0);
	}
	
	return 0;    // Finaliza exitosamente
}


/** Opciones del Menu principal **/




// 1. Inicio de sesion con un usuario existente

int GuardarPuerto(){
	
	system("clear");
	
	printf("\033[32m Ingrese el puerto que va a utilizar\n");
	scanf(" %[^\n]",port);
	
	FILE *archivo;		
	
	archivo = fopen("Puerto.txt","w");       // Crea el archivo correspondiente al usuario
	
	fprintf(archivo,"%s",port);        
	fclose(archivo);
	
	printf("\033[36m Puerto registrado exitosamente\n");
	
	Menu();
	
	return 0;  // Ejecucion finaliza con exito
	
}

/** !!!!! Manejo de contactos !!!!! **/



// Mostrar la lista de contactos de un usuario

int MostrarContactos( ){
	
	FILE *archivo;//Es un buffer que almacena la dirección del archivo
    
    char caracteres[30];
    
    archivo = fopen("Contactos.txt","r");//Almacena la dirección del archivo
    
    if (archivo == NULL)  {
		 printf("\033[36m Usted aún no ha agregado ningun contacto\n");
		 Menu();
	 }
    
    
    printf("\033[40m Contactos:\n");
    
    while (feof(archivo) == 0) {                //   Mientras que no sea el final del documento
        fgets(caracteres,30,archivo);           //  Toma caracter por caracter del archivo y lo almacena en caracteres
        
        if(feof(archivo) == 0)
		printf("\033[33m %s",caracteres);       
        }
            
    fclose(archivo);//Cierra el documento
     
    printf("\033[36m \n");
        
    return 0;
	 
}
	 





// Añadir un nuevo contacto

int NuevoContacto( ){
	
	FILE *archivo;
		
	system("clear");
			
	// Variables locales
	
	char usuario[30];
	char ip[16];
	char puerto[8];
		
	archivo = fopen("Contactos.txt","a");           // Agrega los datos al final del archivo
	if(archivo == NULL) return -1;
	
		
	printf("\033[34m Ingrese el nombre del usuario a agregar:");
	scanf(" %[^\n]",usuario);
	
	if(!ValidarContacto(usuario))NuevoContacto();	
	
	printf("Ingrese el IP:");
	scanf(" %[^\n]",ip);
	printf("Ingrese el Puerto:");
	scanf(" %[^\n]",puerto);
		
	fprintf(archivo,"%s\n",usuario);
	fprintf(archivo,"%s\n",ip);
	fprintf(archivo,"%s\n",puerto);
	fclose(archivo);
	
	printf("\033[31m Usuario agregado con exito\n");
		
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
				if(contacto[cont]!=linea[cont]){
					// No se encuentra
				    return 0;
								
				}
				cont++;
			} 
			return 1; // Se encontro el contacto
					
		}
}

//Método para validar si el contacto que se desea agregar ya esta registrado 
	int ValidarContacto(char usuario[]){
		
		FILE *archivo;
		
        char caracteres[30];
        archivo = fopen("Contactos.txt","r");
 
        if (archivo == NULL)
                exit(1);
                
        while (feof(archivo) == 0) // Se recorre el archivo buscando el usuario
        {
                fgets(caracteres,30,archivo);
                if((BuscarContacto(usuario,caracteres))==1){ // Si se encuentra
					printf("\n \033[01;31mEl contacto ya se encuentra registrado. \n \n");
					return 0;
					}
					}
        
        fclose(archivo);
        return 1;
		}
	
// Funcion auxiliar para cargar el puerto del usuario

int CargarPuerto(){
	
	// Se carga el puerto del usuario ingresado (a ser utilizado por el servidor)
	
	FILE *archivo;
	
	char *buffer;
		
	archivo = fopen("Puerto.txt","r");           
	
	fgets(buffer,9,archivo);                           // Se lee el puerto de usuario (solo la primer linea del archivo) y es asignado a la variable global 'port'
	
	strcpy(port,buffer);
	
	fclose(archivo);
		
	return 0;  // Ejecucion finaliza con exito
		
}

/** ^^^^^^ Manejo de mensajes ^^^^^^ **/


// Cargar las variables de IP y puerto ingresando el nombre de usuario

int CargarDatosContacto(char contacto[]){
	
	FILE *archivo;
	char caracteres[40];
	
	int i=0;  // Recorrido de lineas
	archivo = fopen("Contactos.txt","r");  // Se trata de abrir el archivo del usuario registrado
        			
	while (feof(archivo) == 0)  // Recorre el archivo buscando el contacto solicitado
	{
		fgets(caracteres,30,archivo);    // Buffer
		
		if(((BuscarContacto(contacto,caracteres))==1)||(i>0)){
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
