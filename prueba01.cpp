#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

int main (){
	char nombre_w[40], contrasena_w[60], c;
	int i=0;
	
	FILE *A;
	if ((A = fopen( "prueba.dat", "r")) == NULL){
		printf("\n\n\tError, no se pudo abrir el archivo...\n");
	}
	else {
		while ( ( c = fgetc(A) ) != '\n') {
			nombre_w[ i++ ] = c;
		} 
		nombre_w[ i ] = '\0';
		
		fscanf(A, "%s", &contrasena_w);
		
		printf("%s            %s", nombre_w, contrasena_w);
	}
}
