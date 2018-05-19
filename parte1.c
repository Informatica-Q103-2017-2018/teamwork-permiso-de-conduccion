#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <time.h>    

int main()
{
// Es la primera funcion que va a salir al ejecutar el programa.
void introducir_datos(char nombre[], char apellidos[], char dni[], char autoescuela[], char nombreArchivo[])
{	
	printf("Introduzca el Nombre: ");
	scanf("%s", nombre);
	printf("Introduce Apellido: ");
	scanf("%s", apellidos);
	printf("Introduzca el DNI: ");
	scanf("%s", dni);
	printf("Introduzca el nombre de la  Autoescuela: ");
	scanf("%s", autoescuela);
	
	if(strlen(nombre) != 0 && strlen(apellidos) != 0 && strlen(dni) != 0 && strlen(autoescuela) != 0)
	{
		printf("Usuario %s %s, introducido correctamente\n", nombre, apellidos);
		leer_archivo_usuario(nombre, dni, nombreArchivo);// se creara en txt cada usuario introducido que sea diferente// Cada archivo estara 
		   //creado por el nombre del usuario y por el DNI. 
	}
	else
	{
		printf("Datos del usuario incompleto, por favor vuelva a introducir los datos.\n");
	}
}
}
