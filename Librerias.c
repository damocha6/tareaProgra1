//________________________Librer�s necesarias__________________________________

#include <stdio.h> // Librer�a para entrada y salida de datos

#include <sys/socket.h> // Librer�a para uso de sockets

#include <stdlib.h> // Salida del programa en caso de error    
#include <sys/types.h>

#include <netdb.h> // Librer�a para el uso de base de datos en red	
#include <signal.h>

#include <unistd.h> // Librer�a para uso de fork()

#include <netinet/in.h> // Librer�a que posee los headers para resoluci�n de DNS 

#include <string.h>   // Librer�a para el uso de bzero y bcopy 
 
#define escape "Chao\n" // Define la palabra de cierre de la conversaci�n: Chao
