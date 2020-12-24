/*
	Name: Proyecto final
	Copyright: 
	Author: Medina Delgado Emiliano 
	Date: 07/12/20 11:02 Actualizado el 22/12/2020
	Description: por medio de colas de prioridad crear un programa que pueda organizar el acceso a un establecimiento por medio de filtros 
	para mantener la sana distancia y un control de acceso de las personas, para esto se debe contar con un registro previo
	estableciendo prioridades por Hora, edad y casos especiales (como embarazo, obesidad morfida o problemas respiratorios) en la que se planea ingresar al establecimiento,
	 formando 3 prioridades basicas basadas en el programa de personas de alto, medio o bajo riesgo
	
	
	Prioridad 1: por horario, la hora de ingreso se le pide al usuario, se darán 2 horas de margen entre cada horario usando un formato de 24 hrs
					(8:00 - 10:00, 10:00 - 12:00, 12:00 - 14:00, 14:00 - 16:00, 16:00 - 18:00, 18:00 - 20:00, 20:00 - 22:00)
					considerando las 08:00 como el primer ingreso y las 22:00 como el ultimo
					
	Prioridad 2: 
		Por edades, los de mayor edad entran primero, se pregunta si hay algun padecimiento medico que los pueda hacer mas suceptibles a una enfermedad
		y queda a consideración del usuario si pasa primero a las personas medicamente expuestas
		
		
		2.1 RIESGO ALTO: De acuerdo al programa de salud de la ciudad de mexico las mujeres embazadas, las personas con obesidad morfida, 
		con problemas respiratorios no controlados  y los adultos mayores de 60 años son personas de alto riesgo
	
		2.2 RIESGO MEDIO: De acuerdo al programa de salud de la ciudad de mexico personas con problemas respiratorios controlados, sobre peso
		diabetes controlada y personas entre 40 y 59 años
		
		2.3 RIESGO BAJO: Personas entre 15 y 39 años que no cuenten con alguna enfermedad respiratoria o cardio bascular
*/


//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "dibujarCuadro.h"

//Tipos

typedef char Cadena[30];

typedef struct{
	
	Cadena Problema;
	int eRespuestaEnum;
    int gravedad ; 	
}TrProblemas;



typedef struct {
	
	Cadena Nombre, ApPaterno, ApMaterno;
	int eEdad;
	char Sexo;
	TrProblemas problema;
	
}TrDatosUsuario;

typedef struct cola{
	
	TrDatosUsuario Datos;
	struct cola *ApAtras;
	int Prioridad_Hrs;
}TrCola;

typedef struct colaPrioridad{
	
	 TrCola *ApCola;
	int horario;
	struct colaPrioridad *ApPrioridad;
	
}TrColaPrioridad;

typedef TrColaPrioridad *ApPrioridades;
typedef TrCola *ApColas;


//// prototipos
void asignarPrioridad(ApPrioridades *, ApColas *);
void leerDatos(ApPrioridades *h1,ApPrioridades *h2,ApPrioridades *h3,ApPrioridades *h4,ApPrioridades *h5,ApPrioridades *h6,ApPrioridades *h7);
void verUno(ApColas, int);
void verTodos(ApPrioridades hora1, ApPrioridades hora7 );
void menu();
void copiarDatos(ApColas *recibe, ApColas Dar);
ApColas DesencolarP(ApPrioridades *inicio, ApPrioridades Hora7);
void asignarHorario(ApPrioridades *h1,ApPrioridades *h2,ApPrioridades *h3,ApPrioridades *h4,ApPrioridades *h5,ApPrioridades *h6,ApPrioridades *h7, ApColas *Nuevo);

void acomodarPrioridades(ApPrioridades *p1, ApPrioridades *p2);

int main(){
	
	
	
	ApPrioridades hora1,hora2,hora3,hora4,hora5,hora6,hora7;
	int eOpcion;

	hora1 = (ApPrioridades) malloc (sizeof(TrColaPrioridad));
	hora2 = (ApPrioridades) malloc (sizeof(TrColaPrioridad));
	hora3 = (ApPrioridades) malloc (sizeof(TrColaPrioridad));
	hora4 = (ApPrioridades) malloc (sizeof(TrColaPrioridad));
	hora5 = (ApPrioridades) malloc (sizeof(TrColaPrioridad));
	hora6 = (ApPrioridades) malloc (sizeof(TrColaPrioridad));
	hora7 = (ApPrioridades) malloc (sizeof(TrColaPrioridad));
	
	hora1->horario = 1;
	hora2->horario = 2;
	hora3->horario = 3;
	hora4->horario = 4;
	hora5->horario = 5;
	hora6->horario = 6;
	hora7->horario = 7;
	acomodarPrioridades(&hora1,&hora2);
	acomodarPrioridades(&hora2,&hora3);
	acomodarPrioridades(&hora3,&hora4);
	acomodarPrioridades(&hora4,&hora5);
	acomodarPrioridades(&hora5,&hora6);
	acomodarPrioridades(&hora6,&hora7);

	do{
			dibujarCuadro(0,0,90,20);
	system("color 30");
		menu();
		scanf("%d", &eOpcion);
	
		switch(eOpcion){
		
			case 1:
					leerDatos(&hora1,&hora2,&hora3,&hora4,&hora5,&hora6,&hora7);
					Gotoxy(5,30);
					system("pause");
					break;
			case 2:
					verTodos(hora1,hora7);
					break;
		
			case 3: system("cls");
					dibujarCuadro(0,0,115,20);
					Gotoxy(20,4);
					printf("La persona que salio es:");
					verUno(DesencolarP(&hora1,hora7),0);
					Gotoxy(5,19);
					system("pause");
					break; 
		
			case 0: Gotoxy(20,17);
					printf("Adios");
					break;
				
			default:Gotoxy(20,17); 
					printf("Opcion invalida");
					break;
		
		
		}	
	
	}while (eOpcion != 0);


	free(hora1);
	free(hora2);
	free(hora3);
	free(hora4);
	free(hora5);
	free(hora6);
	free(hora7);
	return 0;
	
}

//Definiciones


void acomodarPrioridades(ApPrioridades *p1, ApPrioridades *p2){
	
	(*p1)->ApCola = NULL;
	(*p1)->ApPrioridad = *p2;
	(*p2)->ApCola = NULL;
	(*p2)->ApPrioridad = NULL;
	
}

void menu(){
	system("cls");
	dibujarCuadro(0,0,90,20);
	dibujarCuadro(19,2,50,4);
	system("color 30");
	Gotoxy(20,3);
	printf("BIENVENIDO AL SISTEMA DE EMI");
	Gotoxy(20,6);
	printf("MENU");
	Gotoxy(20,8);
	printf("Ingresar datos = 1");
	Gotoxy(20,9);
	printf("Mostrar = 2");
	Gotoxy(20,10);
	printf("Sacar = 3");
	Gotoxy(20,11);
	printf("Salir = 0");
	Gotoxy(20,13);
	printf("Ingresa una opcion: ___\b\b");	
}

void verUno(ApColas Aux, int acumulador){
	
	/*Respiratorio = 1\nObesidad = 2\nSobrepeso = 3\nEmbarazo = 4\nDiabetes = 5"
		"\n\tEn caso de tener 2 o mas de ellas, ingresa el #6"
		8:00 - 10:00, 10:00 - 12:00, 12:00 - 14:00, 14:00 - 16:00, 16:00 - 18:00, 18:00 - 20:00, 20:00 - 22:00*/
	switch(Aux->Prioridad_Hrs){
		
		case 1:Gotoxy(4,8 + acumulador);
				printf("Horario: 8:00 - 10:00");
				break;
		case 2:Gotoxy(4,8 + acumulador);
				printf("Horario: 10:00 - 12:00");
				break;
		case 3:Gotoxy(4,8+ acumulador);
				printf("Horario: 12:00 - 14:00");
				break;
		case 4:Gotoxy(4,8+ acumulador);
				printf("Horario: 14:00 - 16:00");
				break;
		case 5:Gotoxy(4,8+ acumulador);
				printf("Horario: 16:00 - 18:00");
				break;
		case 6:Gotoxy(4,8+ acumulador);
				printf("Horario: 18:00 - 20:00");
				break;
		case 7:Gotoxy(4,8+ acumulador);
				printf("Horario: 20:00 - 22:00");
				break;
		default: break;	
	}
		Gotoxy(4,10+ acumulador);
		printf("Nombre: %s", Aux->Datos.Nombre);
		Gotoxy(24,10+ acumulador);
		printf("Apellido paterno: %s", Aux->Datos.ApPaterno);
		Gotoxy(53,10+ acumulador);
		printf("Apellido materno: %s", Aux->Datos.ApMaterno);
		Gotoxy(86,10+ acumulador);
		printf("Edad: %d", Aux->Datos.eEdad);
		Gotoxy(95,10+ acumulador);
		printf("Sexo [F o M]: %c", Aux->Datos.Sexo);
		Gotoxy(4,12+ acumulador);
		printf("SITUACIÓN MEDICA:  ");
		if(strcmp(Aux->Datos.problema.Problema,"no")== 0 || strcmp(Aux->Datos.problema.Problema,"NO")== 0 ||strcmp(Aux->Datos.problema.Problema,"No")== 0){
			Gotoxy(26,12+ acumulador);
			printf("No aplica\n");
		} else 
		
		
		switch (Aux->Datos.problema.eRespuestaEnum){
			
			case 1: Gotoxy(26,12+ acumulador);
					printf("Respiratorio");
					Gotoxy(40,12+ acumulador);
					printf("Gravedad [1-10]: %d", Aux->Datos.problema.gravedad);
					break;
			
			case 2:	Gotoxy(26,12+ acumulador);
					printf("Obesidad");
					Gotoxy(40,12+ acumulador);
					printf("Gravedad [1-10]: %d", Aux->Datos.problema.gravedad);
					break;
			
			case 3:	Gotoxy(26,12+ acumulador);
					printf("Sobrepeso");
					Gotoxy(40,12+ acumulador);
					printf("Gravedad [1-10]: %d", Aux->Datos.problema.gravedad);
					break;
				
			case 4:	Gotoxy(26,12+ acumulador);
					printf("Embarazo");
					Gotoxy(40,12+ acumulador);
					printf("Meses: %d", Aux->Datos.problema.gravedad);
					break;
			
				
			case 5:	Gotoxy(26,12+ acumulador);
					printf("Diabetes");
					Gotoxy(40,12+ acumulador);
					printf("Gravedad [1-10]: %d", Aux->Datos.problema.gravedad);
					break;
				
			case 6:	Gotoxy(26,12+ acumulador);
					printf("dos o mas");
					break;
				
			default: Gotoxy(26,12+ acumulador);
					 printf("No aplica");
						break;
			
		} 
		printf("\n");
}

void copiarDatos(ApColas *recibe, ApColas Dar){
	
	(*recibe)->Datos.eEdad = Dar->Datos.eEdad;
		strcpy((*recibe)->Datos.Nombre, Dar->Datos.Nombre);
		strcpy((*recibe)->Datos.ApPaterno, Dar->Datos.ApPaterno);
		strcpy((*recibe)->Datos.ApMaterno, Dar->Datos.ApMaterno);
		(*recibe)->Datos.Sexo = Dar->Datos.Sexo;
		(*recibe)->Datos.problema.eRespuestaEnum = Dar->Datos.problema.eRespuestaEnum;
		(*recibe)->Datos.problema.gravedad = Dar->Datos.problema.gravedad;
		
	
	
}

ApColas DesencolarP(ApPrioridades *inicio, ApPrioridades Hora7){
	
	ApColas Aux; 
	ApPrioridades AuxIni, AuxP2;
	ApColas Regreso;
	int eContador = 0;
	Regreso = (ApColas) calloc(1, sizeof(TrCola));
	
	AuxIni = *inicio;
	
	
	while(AuxIni != Hora7->ApPrioridad){
		
		if(AuxIni->ApCola == NULL){
			eContador++;
		}
		AuxIni = AuxIni->ApPrioridad;
	}
	
//	printf("Contador %d", eContador);
	if(eContador == 7){
		
		
		printf("\tNo hay personas registradas");
		return Regreso;

	} else {
		
		AuxIni = *inicio;
		AuxP2 = AuxIni->ApPrioridad;
		
		while(AuxP2 != NULL){
			
			 if(AuxIni->ApCola != NULL) {
		
				Aux = AuxIni->ApCola;
				AuxIni->ApCola = Aux->ApAtras;
		
				copiarDatos(&Regreso,Aux);
		
				free(Aux);
				return Regreso;
	
			} else {
				
				AuxIni = AuxP2;
				AuxP2 = AuxIni->ApPrioridad;
			}
			
			
			
		}
	}
	
}

void verTodos(ApPrioridades hora1, ApPrioridades hora7){
	
	ApColas Aux;
	ApPrioridades AuxP;
	int eContador, acumulador = 0, eContador2 = 0;
	AuxP = hora1;
	Aux = AuxP->ApCola;
	system("cls");
	dibujarCuadro(0,0,110,90);
	dibujarCuadro(4,4,80,6);
		
		Gotoxy(5,5);
		printf("LISTA DE HORARIOS");
		
	for(eContador = 1; eContador < 8; eContador++){
		
		if(AuxP->ApCola == NULL){
			eContador2 ++;
			if(eContador2 == 7){
				Gotoxy(20,20);
				printf("No hay personas registradas");
			}
			
		} else {
		
			while(Aux != NULL){
				
				verUno(Aux,acumulador);
				acumulador += 5;
				Aux = Aux->ApAtras;
	
			}
		}
		
		if(AuxP->ApPrioridad != NULL){
			
			AuxP = AuxP->ApPrioridad;
			Aux = AuxP->ApCola;
		}
		
		
	}
	Gotoxy(15,7);
	system("pause");
}

//Asignamos la prioridad de implementación 1
void asignarPrioridad(ApPrioridades *prioridad, ApColas *Nuevo){
	
		ApColas aux, aux2;

			// si es la primer persona
			if((*prioridad)->ApCola == NULL){
			
				(*prioridad)->ApCola = *Nuevo;
				(*Nuevo)->ApAtras = NULL;
			 // si es el segundo en adelante
			} else {
				
				aux = (*prioridad)->ApCola;
				
				//si es el segundo elemento
				if(aux->ApAtras == NULL){
					
					//En caso de que el segundo sea menor al primer
					if(aux->Datos.eEdad >= (*Nuevo)->Datos.eEdad){
						//ingresa normal
						aux->ApAtras = *Nuevo;
						(*Nuevo)->ApAtras = NULL;
					} else {
						//de lo contrario, el mayor se pone al inicio
						(*prioridad)->ApCola = *Nuevo;
						(*Nuevo)->ApAtras = aux;
					}
					
				//Si es el tercer numero en ingresar en adelante
				//3 a N
				} else {
				
					aux2 = aux->ApAtras;
					
					while((*Nuevo)->Datos.eEdad < aux->Datos.eEdad && (*Nuevo)->Datos.eEdad < aux2->Datos.eEdad && aux2->ApAtras != NULL){
						aux = aux2;
						aux2 = aux2->ApAtras;
					}
					
					if((*Nuevo)->Datos.eEdad > aux->Datos.eEdad){
					//insertamos el elemento antes del pAux y actualizamos el ini
						(*Nuevo)->ApAtras = aux;
						(*prioridad)->ApCola = *Nuevo;
						
					} else if((*Nuevo)->Datos.eEdad <= aux->Datos.eEdad && (*Nuevo)->Datos.eEdad > aux2->Datos.eEdad){
						//insertamos el elemento despues del pAux y antes del pAux2
					//ingresa enmedio de 2 elementos, por lo tanto NO se actualiza el inicio ni el final 
						aux->ApAtras = *Nuevo;
						(*Nuevo)->ApAtras = aux2;
						
					} else if((*Nuevo)->Datos.eEdad <= aux2->Datos.eEdad && aux2->ApAtras == NULL){
						//insertamos el elemento al final
						aux2->ApAtras = *Nuevo;
						(*Nuevo)->ApAtras = NULL;
					}
				}//Fin ingresar elementos
			
			}//Fin validar si es el primer elemento
	
} //Fin asignar prioridad

void asignarHorario(ApPrioridades *h1,ApPrioridades *h2,ApPrioridades *h3,ApPrioridades *h4,ApPrioridades *h5,ApPrioridades *h6,ApPrioridades *h7, ApColas *Nuevo){
	
	
	switch ((*Nuevo)->Prioridad_Hrs){
		
		case 1: asignarPrioridad(h1,Nuevo);
				break;
			
		case 2://Mandamos a la prioridad 2
				asignarPrioridad(h2,Nuevo);
				break;
				
		case 3: //Mandamos a la prioridad 3
				asignarPrioridad(h3,Nuevo);
				break;
			
		case 4://Mandamos a la prioridad 4
				asignarPrioridad(h4,Nuevo);
				break;
			
		case 5://Mandamos a la prioridad 5
				asignarPrioridad(h5,Nuevo);
				break;
			
		case 6://Mandamos a la prioridad 6
				asignarPrioridad(h6,Nuevo);
				break;
			
		case 7://Mandamos a la prioridad 7
				asignarPrioridad(h7,Nuevo);
				break;
				
		default: break;
	}
	
}

void leerDatos(ApPrioridades *h1,ApPrioridades *h2,ApPrioridades *h3,ApPrioridades *h4,ApPrioridades *h5,ApPrioridades *h6,ApPrioridades *h7){
	
	ApColas Nuevo;
	ApColas aux;
	
	Nuevo = (ApColas) malloc (sizeof(TrCola));
	
	do{
		system("cls");
		dibujarCuadro(0,0,110,90);
		system("color 30");
		Gotoxy(20,5);
		printf("\tIngresa los siguientes datos");
		Gotoxy(20,10);
		printf("[ 1 ]8:00 - 10:00    [ 2 ]10:00 - 12:00");
		Gotoxy(20,11);
		printf("[ 3 ]12:00 - 14:00   [ 4 ]14:00 - 16:00   [ 5 ]16:00 - 18:00");
		Gotoxy(20,12);
		printf("[ 6 ]18:00 - 20:00   [ 7 ]20:00 - 22:00");
		Gotoxy(20,14);
		printf("Selecciona un Horario : ");
		scanf("%d",&Nuevo->Prioridad_Hrs);
		if(Nuevo->Prioridad_Hrs < 1 || Nuevo->Prioridad_Hrs > 7){
			Gotoxy(20,30);
			printf("Ingresa una opcion valida");
			Sleep(500);
		}
		
	}while(Nuevo->Prioridad_Hrs < 1 || Nuevo->Prioridad_Hrs > 7);
	
	Gotoxy(20,16);
	printf("Nombre: ");
	fflush(stdin);
	gets(Nuevo->Datos.Nombre);
	Gotoxy(20,17);
	printf("Apellido paterno: ");
	fflush(stdin);
	gets(Nuevo->Datos.ApPaterno);
	Gotoxy(20,18);
	printf("Apellido materno: ");
	fflush(stdin);
	gets(Nuevo->Datos.ApMaterno);
	Gotoxy(20,19);
	printf("Edad: ");
	scanf("%d", &Nuevo->Datos.eEdad);
	Gotoxy(20,20);
	printf("Sexo [F o M]: ");
	fflush(stdin);
	Nuevo->Datos.Sexo = getchar();
	Gotoxy(22,21);
	printf("INFORMACIÓN MEDICA [problemas Respiratorios, obesidad, sobrepeso, diabetes o embarazo]");
	Gotoxy(22,22);
	printf("Cuenta con alguna de las situaciones medicas mencionadas? [Si - No]: ");
	fflush(stdin);
	gets(Nuevo->Datos.problema.Problema);
	
	// en caso de padecer una enfermedad
	if(strcmp(Nuevo->Datos.problema.Problema,"si")== 0 || strcmp(Nuevo->Datos.problema.Problema,"SI")== 0 ||strcmp(Nuevo->Datos.problema.Problema,"Si")== 0 ){
		Gotoxy(22,24);
		printf("Respiratorio = 1");
		Gotoxy(40,24);
		printf("Obesidad = 2");
		Gotoxy(22,25);
		printf("Sobrepeso = 3");
		Gotoxy(40,25);
		printf("Embarazo = 4");
		Gotoxy(22,26);
		printf("Diabetes = 5");
		Gotoxy(40,26);
		printf("Dos o mas de las anteriores = 6");
		Gotoxy(26,27);
		printf("Selecciona una opcion: ");
		scanf("%d", &Nuevo->Datos.problema.eRespuestaEnum);
		
		// si tiene 2 o mas de esas situaciones, en automatico le damos prioridad alta
		if(Nuevo->Datos.problema.eRespuestaEnum == 6){
			
			asignarHorario(h1,h2,h3,h4,h5,h6,h7,&Nuevo);
//			asignarPrioridad(alta,&Nuevo);
		//Fin caso dos o mas situaciones	
		} else if(Nuevo->Datos.problema.eRespuestaEnum <= 5 && Nuevo->Datos.problema.eRespuestaEnum == 4){ // si esta embarazada, preguntamos cuantos meses
			Gotoxy(22,28);
			printf("Cuantos meses de embarazo tiene ? ");
			scanf("%d", &Nuevo->Datos.problema.gravedad);
			
			// si tiene 3 o menos meses de embarazo, es prioridad media
			if(Nuevo->Datos.problema.gravedad <= 3){
				
				asignarHorario(h1,h2,h3,h4,h5,h6,h7,&Nuevo);
//				asignarPrioridad(media,&Nuevo);

			 // si es mayor de 3 meses el embarazo, la prioridad es alta
			 // fin caso menor a 3 meses
			} else{ 
			
			asignarHorario(h1,h2,h3,h4,h5,h6,h7,&Nuevo);
//				asignarPrioridad(alta,&Nuevo);
				
			}// Fin caso mayor a 3 meses
			
		} /* fin en caso de embarazo */else if(Nuevo->Datos.problema.eRespuestaEnum <= 5 && Nuevo->Datos.problema.eRespuestaEnum >= 1) { //En caso de no embarazo
		Gotoxy(22,28);
		printf("Cual es la gravedad de su problema ? [considera 10 como Maximo y 1 como leve]:  ");
			scanf("%d", &Nuevo->Datos.problema.gravedad);
			
			// si es mayor o igual a 1 y menor o igual a 5 se le da prioridad media
			if(Nuevo->Datos.problema.gravedad <= 5 && Nuevo->Datos.problema.gravedad >= 1){
				
				
				asignarHorario(h1,h2,h3,h4,h5,h6,h7,&Nuevo);
//				asignarPrioridad(media,&Nuevo);
			} // fin en caso de gravedad menor a 5
			
				// si es prioridad mayor a 5 y menor o igual 10 se le da prioridad alta
			else if(Nuevo->Datos.problema.gravedad <= 10 && Nuevo->Datos.problema.gravedad > 5){
				
				asignarHorario(h1,h2,h3,h4,h5,h6,h7,&Nuevo);
//				asignarPrioridad(alta,&Nuevo);
				
			} else { //Fin en caso de gravedad mayor a 5
				Gotoxy(22,40);
				printf("Los datos ingresados no corresponden con lo solicitado");
				
			} //Fin caso de que ingrese mal la gravedad
		
		} // fin en caso de no embarazo
//	fin en caso de padecer alguna situacion medica	
	} else { 	// en caso de no padecer ninguna situacion medica validamos la edad para asignar la prioridad
	
		//Asignamos prioridad Alta
		if(Nuevo->Datos.eEdad >= 60 && Nuevo->Datos.eEdad < 100){
			
			asignarHorario(h1,h2,h3,h4,h5,h6,h7,&Nuevo);
//			asignarPrioridad(alta,&Nuevo);
		} // Fin caso tercera edad
		
		// Asignamos prioridad media
		 else if (Nuevo->Datos.eEdad >= 40 && Nuevo->Datos.eEdad <= 59){
		 	asignarHorario(h1,h2,h3,h4,h5,h6,h7,&Nuevo);
//			 asignarPrioridad(media,&Nuevo);
		 	
		 } // Fin caso adultos de 40 a 60
		 
		 //Asignamos prioridad baja
		 else if(Nuevo->Datos.eEdad >= 15 && Nuevo->Datos.eEdad <= 39){
		 	asignarHorario(h1,h2,h3,h4,h5,h6,h7,&Nuevo);
//		 asignarPrioridad(baja,&Nuevo);
		 } // fin en caso de edades de 15 a 39
		  else {
		  	Gotoxy(22,40);
		 	printf("Los datos no fueron ingresados correctamente");
		 } // fin en caso de ingresar los datos incorrectos
		 
	} // fin en caso de no padecer ninguna enfermedad
	
} // fin procedimiento leer datos



