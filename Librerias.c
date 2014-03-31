//________________________Librerís necesarias__________________________________

#include <stdio.h> // Librería para entrada y salida de datos

#include <sys/socket.h> // Librería para uso de sockets

#include <stdlib.h> // Salida del programa en caso de error    
#include <sys/types.h>

#include <netdb.h> // Librería para el uso de base de datos en red	
#include <signal.h>

#include <unistd.h> // Librería para uso de fork()

#include <netinet/in.h> // Librería que posee los headers para resolución de DNS 

#include <string.h>   // Librería para el uso de bzero y bcopy 
 
#define escape "Chao\n" // Define la palabra de cierre de la conversación: Chao
