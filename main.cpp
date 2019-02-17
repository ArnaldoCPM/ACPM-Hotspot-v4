#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

	int s_n, op2, cont, c_c = 0;
	unsigned char opcion; 

	char opc_1[]="Ejecutar la red hospedada", opc_2[]="Parar la red hospedada";
	char opc_3[]="Editar red hospedada",      opc_4[]="Ver estado y propiedades";		
	char opc_5[]="Salir del programa";

	bool EsOpcion(int opc);	
	int inicio(void);
	void confirmar(int );
	bool ver_contrasena(char contrasena[64]);


int main (){
	
	do{
		c_c = 0;
		confirmar( inicio() );
		
		printf("\n\t");
	
		switch(opcion) {
			/********** Ejecuta la red hospedada **************/
			case '1': 
				printf("\n\n\t\t\t");
				system("netsh wlan start hostednetwork");
				system("color 20");
				break;
				
			/********** Para la red hospedada  **************/
			case '2':
				printf("\n\n\t\t");
				system("netsh wlan stop hostednetwork");
				break;
				
			/********** Edita la red hospedada **************/
			case '3':
				char nombre_w[ 30 ];
				char contrasena_w [ 64 ];
				
				FILE *apuntador;
				
				if ((apuntador = fopen( "ed_hot.cmd", "w")) == NULL){
					printf("\n\n\tError, no se pudo crear el archivo de edicion...\n");
				}
				else {
					char c; int i = 0;
					
					do{
						
						printf("\n\nIntroduzca el nombre nuevo:\n");
						printf("---------------------------\n  > ");
						//scanf("%s", nombre_w);
						i = 0; c = 0;
						fflush(stdin);
						while ( ( c = getchar() ) != '\n') {
							if(c==32)	c = '_';
							nombre_w[ i++ ] = c;
						} 

						nombre_w[ i ] = '\0';
						
						printf("\nIntroduzca la contrase%ca nueva (8 a 64 caracteres):\n", 164);
						printf("---------------------------------------------------\n  > ");
						scanf("%s", contrasena_w);
						while( ver_contrasena(contrasena_w) ){
							printf("\a\n   Faltan m%cs caracteres, 8 a 64 caracteres por favor...", 160);
							printf("\n\nIntroduzca la contrase%ca nueva:\n", 164);
							printf("-------------------------------\n  > ");
							scanf("%s", contrasena_w);
						}
						
						printf("\n\n-----------------------------------------------");
						printf("\n   SSID:         %s", nombre_w);
						printf("\n   Contrase%ca:   %s", 164, contrasena_w);
						printf("\n-----------------------------------------------");
						
						do{
							printf("\n\n\t   %cDeseas...?", 168);
							printf("\n   (a) Confirmar datos\n   (b) Cambiar datos\n   (c) Cancelar todo\n > ");
							cont = getche();
						}while(cont < 97 || cont > 99 );

					}while(cont == 98);
					
					if(cont == 97){
						fprintf( apuntador, "@echo off \ncolor 70 \nnetsh wlan set hostednetwork "
						"ssid=%s key=%s keyUsage=persistent\npause\n exit", nombre_w, contrasena_w);
						
						fclose( apuntador );
						system("start ed_hot.cmd");
						
						/***** Guarda los datos *****/						
						if((apuntador = fopen("datos_wifi.dat", "w")) == NULL)
							printf("\n\n\tError al guardar datos...\n");
						else{
							fprintf(apuntador, "%s\n%s", nombre_w, contrasena_w);
						}
						
						fclose( apuntador );
					}
					
					printf("\n\n");
				}
				break;
				
			/********** Ver ultima configuracion **************/
			case '4':
				if((apuntador=fopen("datos_wifi.dat", "r"))==NULL)
					printf("\n\nArchivo de la ultima configuracion guardado por ACPM Hotspot no encontrado...\n");
				else{
					int i=0, c;
					while ( ( c = fgetc(apuntador) ) != '\n') {
						nombre_w[ i++ ] = c;
					} 
					nombre_w[ i ] = '\0';
		
					fscanf(apuntador, "%s", &contrasena_w);
					printf("\n\nUltimos datos guardados correctamente:\n");
					printf("--------------------------------------\n");
					printf("\n   SSID:         %s\n   Contrase%ca:   %s\n", nombre_w, 164, contrasena_w);
					printf("\nOb.: Los datos mostrados arriba corresponden a un archivo guardado por este \n"
						   "programa, esto quiere decir si cambiaste la configuracion en otro programa, los "
					 	   "datos de arriba no serian correctos. Sin embargo, los datos que se mostrar%cn \n"
						   "abajo ser%cn actuales de la red hospeda.\n\n", 160, 160);
				}
				system("pause");
				printf("\n");
				system("netsh wlan show hostednetwork");
				
				break;
			
			/**********    Sale del programa     **************/
			case '5':
				return 0;
		}
		
		do{
			printf("\n    %cDeseas realizar otra accion? (S)i o (N)o \n > ",168);
			opcion = tolower( getche () );
		}while(opcion!='s' && opcion!='n' );
		
	}while( opcion != 'n');
		
}


/**********  Presenta al programa y pregunta la accion deseada  ************************/
int inicio(void){
	
	system("color 70");
	system("cls");
	printf("\n\t\t\t***** ACPM HOTSPOT V3 *****\n");
	printf("\n  *--------------------------------------------------------------------------*");
	printf("\n  | Este es un sencillo programa que te ayuda a administrar la red hospedada |\n" 
		     "  | de tu equipo. Para realizar una accion, presione las flechas (%c%c) o      |\n" 
		     "  | ingrese el numero o letra (en otro caso), que le corresponde a la accion |\n"
		     "  | deseada.                                                                 |\n"
		     "  *--------------------------------------------------------------------------*\n", 24, 25);
		
	printf("\n\t%cQue deseas hacer?\n\n",168);
	if(c_c == 1) 	printf(" -> (1) %s\n", opc_1);
	else 			printf("   (1) %s\n", opc_1);
	if(c_c == 2) 	printf(" -> (2) %s\n", opc_2);
	else 			printf("   (2) %s\n", opc_2);
	if(c_c == 3) 	printf(" -> (3) %s\n", opc_3);
	else 			printf("   (3) %s\n", opc_3);
	if(c_c == 4) 	printf(" -> (4) %s\n", opc_4);
	else 			printf("   (4) %s\n", opc_4);
	if(c_c == 5) 	printf(" -> (5) %s\n > ", opc_5);
	else 			printf("   (5) %s\n > ", opc_5);

	opcion = getch ();
	if ( EsOpcion(opcion) ){
		printf("%c",opcion);
		return (opcion);	 
	}
	else if(opcion == 224){		//Si si introdujo flechas
		opcion = getch();
		if (opcion == 80 && c_c < 5){	//80 fleja abajo
			c_c++;
			inicio();
		}	
		else if(opcion == 72 && c_c > 1){	//72 flecha arriba
			c_c--;
			inicio();
		} 
		else{
			printf("\a");
			inicio();			
		}
	}
	else if(opcion == 13 && c_c <= 5 && c_c >= 1){		//si enter (13) y contador de caracter es 1-5
		switch (c_c){
			case 1:	opcion = '1'; return ('1'); //break;
			case 2:	opcion = '2'; return ('2'); //break;
			case 3:	opcion = '3'; return ('3'); //break;
			case 4:	opcion = '4'; return ('4'); //break;
			case 5:	opcion = '5'; return ('5'); //break;
		}
	}
	else{
		printf("\a");
		inicio();
	} 
		
}


/*************** Pide confirmación para continuar **************************/
void confirmar(int opc){
	do{
		if(opc != '3' && opc != '4'){
			printf("\n\n\t  %c",168);
			switch(opc){
				case '1':printf("%s",opc_1);break;
				case '2':printf("%s",opc_2);break;		
				case '5':printf("%s",opc_5);break;
			}
			printf("? (S)i o (N)o \n    > ");
			s_n = tolower( getche () );
			
			if (s_n == 'n'){		
				//confirmar( inicio() );
				main();
			}
		}
		else s_n = 's';
	}while(s_n != 's' && s_n!='n');
}


/************* Verifica si se ingresó del 1 hasta 5 ************************/
bool EsOpcion(int opc){
	return (opc >= 49 && opc <= 53);
}


/****** Cuenta la cantidad de caracteres introducidos para la contraseña ******/
bool ver_contrasena(char contrasena[64]){
	int i; 
	for(i=0; i<=64 && (contrasena[i] != '\0'); i++);
	return !(8<=i && i<=64);
}
