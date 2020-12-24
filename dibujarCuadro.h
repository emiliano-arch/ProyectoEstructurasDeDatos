/****************************************************************************************
*   Modulo	: dibujar cuadros                                                           * 
*   Autores : Medina Delgado Emiliano												    *
*   Fecha   : 18/04/2020																*
*   Objetivo: dibujar los cuadros de contorno para cada sistema				 			*
****************************************************************************************/

void dibujarCuadro(int x1,int y1,int x2,int y2){
	
	HANDLE salida;
	COORD coord;
    int i;
    
    salida = GetStdHandle(STD_OUTPUT_HANDLE);
		coord.X = x1;
		coord.Y = y1;
		SetConsoleCursorPosition(salida, coord);
		printf("%c", 218);
    
    for (i=x1+1;i<x2;i++){
    	salida = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = i;
	coord.Y = y1;
	SetConsoleCursorPosition(salida, coord);
	printf("%c", 196);//linea horizontal superior
        
	salida = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = i;
	coord.Y = y2;
	SetConsoleCursorPosition(salida, coord);	
		printf("%c", 196);//linea horizontal inferior
    }
 	salida = GetStdHandle(STD_OUTPUT_HANDLE);
		coord.X = x1;
		coord.Y = y2;
		SetConsoleCursorPosition(salida, coord);
		printf("%c", 192);
		
	salida = GetStdHandle(STD_OUTPUT_HANDLE);
		coord.X = x2;
		coord.Y = y1;
		SetConsoleCursorPosition(salida, coord); 
 		printf("%c", 191);
 		
 		
    for (i=y1+1;i<y2;i++){
		 salida = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = x1;
	coord.Y = i;
	SetConsoleCursorPosition(salida, coord);
		 printf("%c", 179) ;//linea vertical izquierda
		salida = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = x2;
	coord.Y = i;
	SetConsoleCursorPosition(salida, coord); 
		printf("%c", 179) ;//linea vertical derecha
    }
    
    salida = GetStdHandle(STD_OUTPUT_HANDLE);
		coord.X = x2;
		coord.Y = y2;
		SetConsoleCursorPosition(salida, coord);
		printf("%c", 217);
}

void Gotoxy(int x, int y){
	
	HANDLE Manipulador;
	COORD Coordenadas;
	Manipulador = GetStdHandle(STD_OUTPUT_HANDLE);
	Coordenadas.X = x;
	Coordenadas.Y = y;
	SetConsoleCursorPosition(Manipulador,Coordenadas);

}




