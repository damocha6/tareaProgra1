void FServidor(int puertoServidor){  //Crea el servidor en el sistema, recibe el puerto desde el main

char buffer[256]; //Mensaje a enviar, Tamaño definido en 256 


struct sockaddr_in DirServidor;  //Referencia a los elementos del socket nativo
struct sockaddr_in DirUsuario;  //Referencia a los elementos del socket del usuario


int SSer = socket(AF_INET, SOCK_STREAM, 0);

if (SSer < 0) {  //Manejo de errores si no se logra la creación del socket
fprintf(stderr,"Fallo en la Creación del Socket\n\a");
exit(1);
}

//Conexion entrante (usuario)

DirServidor.sin_family = AF_INET; //Protocolo ARPA
DirServidor.sin_addr.s_addr = INADDR_ANY; //Protocolo para el uso de la IP definida

DirServidor.sin_port = htons(puertoServidor); //Asignación del puerto servidor al socket nativo con htons, htons: Nodo a variable corta de Red

bind(SSer, (struct sockaddr *) &DirServidor,sizeof(DirServidor)); //Unión del socket servidor con el socket entrante

listen(SSer,2); //función listen() se usa si se estÃ¡n esperando conexiones entrantes

socklen_t largoDirUsuario;  //Variable de dirección de tipo socket
largoDirUsuario = sizeof(DirUsuario); //Asignación a la variable del largo de la direccion del socket


int SUsu = accept(SSer, (struct sockaddr *) &DirUsuario, &largoDirUsuario);


while(1){ // ciclo de lectura del buffer del socket para su muestra en consola
bzero (buffer,256);

read(SUsu, buffer, 255);