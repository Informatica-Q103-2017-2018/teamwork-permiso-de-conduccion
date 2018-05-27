#include <stdio.h>
#include <string.h> 
#include <stdlib.h>  // para  rand(), srand()
#include <time.h>    // para generar el test aleatorio
#define SIZE 456    // 

struct Pregunta {
   int numero;
   char pregunta[456];
   char opcion1[456];
   char opcion2[456];
   char opcion3[456];
   int correcta;
   int respuesta;
};
void escribir_test_archivo(char nombreArchivo[], int aciertos, char resultado[]);
void mostrar_resultados_test(struct Pregunta newTest[]);
void menu_test(struct Pregunta bancops[], int size, char nombreArchivo[]);
void generar_test(struct Pregunta bancops[], int size, struct Pregunta newTest[]);
void realizar_test(struct Pregunta newTest[], char nombreArchivo[]);
void leer_archivo_usuario(const char nombre[], const char dni[], char nombreArchivo[]);
void mostrar_pregunta(struct Pregunta pregunta);
void leer_archivo_preguntas(struct Pregunta bancops[], int *length);
struct Pregunta leer_pregunta(char str1[]);
void introducir_datos(char nombre[], char apellidos[], char dni[], char autoescuela[], char nombreArchivo[]);
void imprimir_datos(const char nombre[], const char apellidos[], const char dni[], const char autoescuela[]);
void menu_autoescuela(struct Pregunta bancops[], int size);

int main()
{
	struct Pregunta bancops[SIZE];
	int length;
	leer_archivo_preguntas(bancops, &length);
	printf("Longitud del Banco de Preguntas: %d\n", length);
	menu_autoescuela(bancops, length);

    return 0;
}

void escribir_test_archivo(char nombreArchivo[], int aciertos, char resultado[])
{
	FILE *fout;
	
	printf("Nombre Archivo: %s\n", nombreArchivo);
	fout = fopen(nombreArchivo, "r");
   	fprintf(fout, "Test, aciertos %d, %s\n", &aciertos, resultado);
   	fclose(fout);
}

void mostrar_resultados_test(struct Pregunta newTest[30])
{
	int i;
   	for (i = 0; i < 30; ++i) {
   		printf("\n");
		mostrar_pregunta(newTest[i]);
		printf("Respuesta correcta = %d\n", newTest[i].correcta);
		printf("Respuesta usuario = %d\n", newTest[i].respuesta);
		printf("\n");
   	}
   	printf("\n");
}

void menu_test(struct Pregunta bancops[], int size, char nombreArchivo[])
{
	struct Pregunta newTest[30];
	char opcionPrincipal = 0;
	
	generar_test(bancops, size, newTest);
	realizar_test(newTest, nombreArchivo);
	
	printf("a - Desea repetir el test?\n");
	printf("b - Desea ver los fallos?\n");
	printf("c - Desea hacer otro test?\n");
	printf("q - Salir.\n");

	do
	{
		scanf_s("%c", &opcionPrincipal);

		switch (opcionPrincipal)
		{
			case 'a':
				realizar_test(newTest, nombreArchivo);
				printf("Opcion deseada ?:\n");
				break;
			case 'b':
				mostrar_resultados_test(newTest);
				printf(" Opcion deseada ?:\n");
				break;
			case 'c':
				generar_test(bancops, size, newTest);
				realizar_test(newTest, nombreArchivo);
				printf(" Opcion deseada ?:\n");
				break;
			case 'q':
				printf("Saliendo del test.\n");
				break;
		}
	} while (opcionPrincipal != 'q');
}
void generar_test(struct Pregunta bancops[], int size, struct Pregunta newTest[30])
{
	int random, i, j;
     srand(time(0));  
     //// Planta el generador de números aleatorios con la hora actual
     //srand (tiempo (0)); // necesita encabezado <cstdlib> y <ctime>
     // Genera 10 números pseudoaleatorios
     // Obtendrás una secuencia diferente en diferentes ejecuciones,
     // porque la hora actual es diferente
   	for (i = 0; i < 30; ++i) {
		random = rand() % size;
		for(j = 0; j <= i; ++j)
		{
			if(newTest[j].numero == random)
			{
				random = rand() % size;
				j = 0;
			}
		}
		printf("%d ", random);
      	newTest[i].numero = bancops[random].numero;
      	strcpy (newTest[i].pregunta, bancops[random].pregunta);
      	strcpy (newTest[i].opcion1, bancops[random].opcion1);
      	strcpy (newTest[i].opcion2, bancops[random].opcion2);
      	strcpy (newTest[i].opcion3, bancops[random].opcion3);
      	newTest[i].correcta = bancops[random].correcta;
   	}
   	printf("\n");
}
void realizar_test(struct Pregunta newTest[], char nombreArchivo[])
{
	int aciertos = 0;
	int i = 0, respuesta = 0;
	
	printf("---------------------------------------------------------\n");
	printf("El Test consta de 30 preguntas. Estara aprobado es si logra .\n");
	printf("acertar 27 o más preguntas correctamente. Debe introducir \n");
	printf("1, 2 o 3 para seleccionar su respuesta. Comienza el Test!\n");
	printf("---------------------------------------------------------\n");
	printf("\n");

	for(i = 0; i < 30; i++)
	{
		mostrar_pregunta(newTest[i]);
		scanf("%d", &respuesta);
		newTest[i].respuesta = respuesta;
		if(respuesta == newTest[i].correcta)
		{
			aciertos++;
		}
	}
	
	if(aciertos >= 27)
	{
		printf("*********** Aprobado con %d preguntas correctas! **************\n", aciertos);
		escribir_test_archivo(nombreArchivo, aciertos, "Aprobado");
	}
	else
	{
		printf("Insuficiente con %d preguntas correctas :(\n", aciertos);
		escribir_test_archivo(nombreArchivo, aciertos, "Suspendido");
	}
	printf("\n");
}
void leer_archivo_usuario(const char nombre[], const char dni[], char nombreArchivo[])
{
   FILE *fin, *fout;
   char line[] = " "; 
   char buffer[SIZE];
   
   strcat(nombreArchivo, nombre);
   strcat(nombreArchivo, dni);
   strcat(nombreArchivo, ".txt");
   printf("Nombre archivo: %s\n", nombreArchivo);

   fin = fopen(nombreArchivo, "r");
   
   if (fin == NULL) {
    	fout = fopen(nombreArchivo, "w");
    	strcat(line, nombre);
    	strcat(line, " ");
    	strcat(line, dni);
   		fprintf(fout, "%s\n", line);
   		fclose(fout);
   } else {
      while (!feof(fin)) {
         if (fgets(buffer, SIZE, fin) == NULL) break;
         fputs (buffer , stdout);
      }
      fclose(fin);
   }
}
void mostrar_pregunta(struct Pregunta pregunta)
{
	printf("%d.-", pregunta.numero);
	printf("%s\n", pregunta.pregunta);
	printf(" %s\n", pregunta.opcion1);
	printf(" %s\n", pregunta.opcion2);
	printf(" %s\n", pregunta.opcion3);
}

void leer_archivo_preguntas(struct Pregunta bancops[] , int *length)
{
   FILE * pFile;
   char buffer[SIZE];
 
   pFile = fopen("BancoPreguntas.txt" , "r");
   if (pFile == NULL) {
      perror("Error");
   } else {
   		int i = 0;
      while (!feof(pFile)) {
         if (fgets(buffer, SIZE, pFile) == NULL) break;
         bancops[i] = leer_pregunta(buffer);
         i++;
      }
      fclose(pFile);
      *length = i;
   }
}
struct Pregunta leer_pregunta(char str1[])
{
	char tmp[256];
    char *p;
    int dos_punto = 0;
    int coma = 0;
    int i = 0;
    struct Pregunta pregunta;
 
    for (p = str1; *p != '\0'; ++p) {
	  tmp[i] = *p;
	  i++;
	  
	  if(*p == ':' && dos_punto < 1)
	  {
	  	dos_punto++;
      	tmp[--i] = '\0';
      	pregunta.numero = atoi(tmp);
      	i = 0;
	  }
	  else if(*p == ',' && coma == 0)
	  {
      	tmp[--i] = '\0';
      	strcpy (pregunta.pregunta, tmp);
      	coma++;
      	i = 0;
	  }
	  else if(*p == ',' && coma == 1)
	  {
      	tmp[--i] = '\0';
      	if(tmp[--i] == '@')
		{
			pregunta.correcta = coma;
			tmp[i] = ' ';
		}
      	strcpy (pregunta.opcion1, tmp);
      	coma++;
      	i = 0;
	  }
	  else if(*p == ',' && coma == 2)
	  {
      	tmp[--i] = '\0';
      	if(tmp[--i] == '@')
		{
			pregunta.correcta = coma;
			tmp[i] = ' ';
		}
      	strcpy (pregunta.opcion2, tmp);
      	coma++;
      	i = 0;
	  }
	  else if(*(p+1) == '\0')
	  {
		tmp[--i] = '\0';
		if(tmp[--i] == '@')
		{
			pregunta.correcta = coma;
			tmp[i] = ' ';
		}
      	strcpy (pregunta.opcion3, tmp);
	  }
	  
    }
    return pregunta;
}
void introducir_datos(char nombre[], char apellidos[], char dni[], char autoescuela[], char nombreArchivo[])
{	
	printf("Introduce el Nombre: ");
	scanf("%s", nombre);
	printf("Introduce Apellido: ");
	scanf("%s", apellidos);
	printf("Introduce el DNI: ");
	scanf("%s", dni);
	printf("Introduce el nombre de la Autoescuela: ");
	scanf("%s", autoescuela);
	
	if(strlen(nombre) != 0 && strlen(apellidos) != 0 && strlen(dni) != 0 && strlen(autoescuela) != 0)
	{
		printf("Usuario %s %s, introducido satisfactoriamente!\n", nombre, apellidos);
		leer_archivo_usuario(nombre, dni, nombreArchivo);
	}
	else
	{
		printf("Datos del usuario incompleto, por favor vuelva a introducir los datos.\n");
	}
}
void imprimir_datos(const char nombre[], const char apellidos[], const char dni[], const char autoescuela[])
{
	printf("Nombre: %s\n", nombre);
	printf("Apellidos: %s\n", apellidos);
	printf("DNI: %s\n", dni);
	printf("Autoescuela: %s\n", autoescuela);
}

void menu_autoescuela(struct Pregunta bancops[], int size) 
{
	char opcionPrincipal = 0;
	printf("---------------------------------------------------------\n");
	printf("Este programa realiza test a los estudiantes de autoescuela.\n");
	printf("---------------------------------------------------------\n");
	printf("A - Introducir Datos\n");
	printf("B - Realizar Test\n");
	printf("S - Salir.\n");
	
	char nombre[50]; 
	char apellidos[50]; 
	char dni[9];
	char autoescuela[50];
	char nombreArchivo[] = "U";

	do
	{
		scanf_s("%c", &opcionPrincipal);

		switch (opcionPrincipal)
		{
			case 'A':
				introducir_datos(nombre, apellidos, dni, autoescuela, nombreArchivo);
				printf("Opcion deseada ?:\n");
				break;
			case 'B':
				imprimir_datos(nombre, apellidos, dni, autoescuela);
				menu_test(bancops, size, nombreArchivo);
				printf(" Opcion deseada ?:\n");
				break;
			case 'S':
				printf("Saliendo del Programa.\n");
				printf("Gracias por su visita.\n");
				break;
		}
	} while (opcionPrincipal != 'S');
}
