/***********************************************************

   _________         _________
  /         \       /         \
 /  /~~~~~\  \     /  /~~~~~\  \
 |  |     |  |     |  |     |  |
 |  |     |  |     |  |     |  |         /
 |  |     |  |     |  |     |  |       //
(o  o)    \  \_____/  /     \  \_____/ /
 \__/      \         /       \        /
  |         ~~~~~~~~~         ~~~~~~~~
  ^

            Juego:      Snake
            Version:    1.0 - Final
            Fecha:      20/01/2017

            Alejandro Ruiz Rubio


*************************************************************/
//---------------------------------------------------------------------
#include <iostream>
#include "ioconsole.hpp"
//#include "misc.hpp"
using namespace std;
//---------------------------------------------------------------------
string version = "Version 1.0 - Final";
//---------------------------------------------------------------------
const int MAX = 50;

typedef int filas [MAX];
typedef filas columnas [MAX];
//---------------------------------------------------------------------
unsigned Menu ()
{
	unsigned opcion;

	cio << endl;
	cio << endl;
	cio << "\tSNAKE \t\t (" << version << ")" << endl;
	cio << endl << endl;
	cio << "\t1. - Jugar" << endl;
	cio << endl;
	cio << "\t2. - Dificultad" << endl;
	cio << endl;
	cio << "\t3. - Salir" << endl;
	cio << endl << endl << endl << endl;
	cio << "CREADO POR:" << endl;
	cio << "Alejandro Ruiz" << endl;
	while(opcion < '1' || opcion > '3'){
        if(cio.kbhit())
            cio >> key(opcion);
	}
    return opcion;
}
//---------------------------------------------------------------------
unsigned Menu2()
{
    unsigned opcion;

	cio << endl;
	cio << endl;
	cio << "\tSNAKE \t\t (" << version << ")" << endl;
	cio << endl << endl;
	cio << "-----------------------" << endl;
	cio << "    - DIFICULTAD -  " << endl;
	cio << "-----------------------" << endl;
	cio << endl;
	cio << "\t1.- Facil" << endl;
	cio << endl;
	cio << "\t2.- Medio" << endl;
	cio << endl;
	cio << "\t3.- Dificil" << endl;
	cio << endl;
	while(opcion < '1' || opcion > '3'){
        if(cio.kbhit())
            cio >> key(opcion);
	}
    return opcion;
}
//---------------------------------------------------------------------
bool colision(columnas a, int x, int y, int dir)
{
    bool res = false;
    switch(dir)
    {
        case 0:
            if(a[x + 1][y] != 0 && (a[x + 1][y] != -2))
        res = true;
            break;
        case 1:
            if(a[x - 1][y] != 0 && (a[x - 1][y] != -2))
        res = true;
            break;
        case 2:
            if(a[x][y - 1] != 0 && (a[x][y - 1] != -2))
        res = true;
            break;
        case 3:
            if(a[x][y + 1] != 0 && (a[x][y + 1] != -2))
        res = true;
            break;
    }
    return res;
}
//---------------------------------------------------------------------
bool colision_manzana(columnas a, int x, int y, int dir)
{
    bool res = false;
    switch(dir)
    {
        case 0:
            if(a[x + 1][y] == -2)
        res = true;
            break;
        case 1:
            if(a[x - 1][y] == -2)
        res = true;
            break;
        case 2:
            if(a[x][y - 1] == -2)
        res = true;
            break;
        case 3:
            if(a[x][y + 1] == -2)
        res = true;
            break;
    }
    return res;
}
//---------------------------------------------------------------------
void direccion(int dir , int &x, int &y)
{
    switch (dir)
    {
        case 0:
            x++;
            break;
        case 1:
            x--;
            break;
        case 2:
            y--;
            break;
        case 3:
            y++;
            break;
    }
}
//---------------------------------------------------------------------
void rellenar_matriz(columnas &a)               //inicializar matriz
{
    for(int i = 0 ; i < MAX ; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            if(i == 0 || i == (MAX - 1))
                a[i][j] = -1;
            else if(j == 0 || j == (MAX - 1))
                a[i][j] = -1;
            else
                a[i][j] = 0;
        }
    }
}
//---------------------------------------------------------------------
void dibujar_matriz(columnas a) //Dibujar Pantalla
{
    for(int i = 0 ; i < MAX ; i++)
    {
        for(int j = 0 ; j < MAX ; j++)
        {
            if(a[i][j] == 0)
                cio << " ";
            else
                cio << char(219);
        }
        cio << endl;
    }
    cio << endl;
    cio << "Controles: " << char(30) << " " << char(31) << " " << char(17) << " " << char(16) << endl;
    cio << endl;
    cio << "Pusla la tecla  P  para pausar el Juego" << endl;
    cio << endl;
    cio << "Pulse la tecla ESC para volver al Menu" << endl;
    cio << endl;
    cio << cursorxy(MAX + 5, 3) << "SCORE: 0" << endl;
}
//---------------------------------------------------------------------
void pase()     //funcion "PAUSE"
{
    unsigned p = 1, tecla;
    while (p != 0)
    {
        if (cio.kbhit())
            cio >> key(tecla);
        if (tecla == 'p')
            p = 0;
    }
}
//---------------------------------------------------------------------
void reducir_matriz_entera(columnas &a)
{
    for(int i = 1; i < (MAX - 1); i++){
        for(int j = 1; j < (MAX - 1); j++){
            if(a[i][j] > 0){
                a[i][j] --;
            }
        }
    }
}
//---------------------------------------------------------------------
void dibujar_cola(columnas &a, int i, int j, int dir)
{
    for(int i = 1; i < (MAX - 1); i++){
        for(int j = 1; j < (MAX - 1); j++){
            if(a[i][j] == 1){
                cio << cursorxy(i + 1, j + 1) << " ";
            }
        }
    }
}
//---------------------------------------------------------------------
void snake(columnas &a,int i ,int j, int cola)
{
    a[i][j] = cola;
}
//---------------------------------------------------------------------
void manzana(columnas &a)
{
    int manx, many;
    do{
        manx = aleatorio(MAX - 2) + 1;
        many = aleatorio(MAX - 2) + 1;
    }while(a[manx][many] > 0);
    a[manx][many] = -2;
}
//---------------------------------------------------------------------
void dibujar_snake(columnas a)
{
    for(int i = 1; i < (MAX - 1); i++){
        for(int j = 1; j < (MAX - 1); j++){
            if(a[i][j] != 0 && a[i][j] != -2){
                cio << cursorxy(i + 1, j + 1) << char(219);
            }else if(a[i][j] == -2)
                cio << cursorxy(i + 1, j + 1) << "O";
        }
    }
}
//---------------------------------------------------------------------

//---------------------------------------------------------------------
int main()
{
    columnas matriz;
    int cont, dir, vel = 50, cabeza;
    int x, y, score;
    unsigned tecla, opcion, opcion2;

    cio << no_cursor;

    do{
        opcion = Menu();

        dir = 0;
        x = 10;
        y = 10;
        cont = 1;
        score = 0;
        cabeza = 4;

        switch(opcion){
            case '1':
            {
            cio << clear_screen;
            rellenar_matriz(matriz);
            dibujar_matriz(matriz);
            manzana(matriz);

            while (cont != 0)
            {
                if(colision(matriz, x, y, dir)){
                    cio << cursorxy((MAX / 2) - 5, MAX / 2) << "Game Over";
                    Sleep(2000);
                    cont = 0;
                }

                if(colision_manzana(matriz, x, y, dir)){
                    score = score + 10;
                    manzana(matriz);
                    cio << cursorxy(MAX + 12, 3) << score;
                    cabeza++;
                }
                direccion(dir , x , y);
                snake(matriz, x, y, cabeza);
                dibujar_snake(matriz);
                dibujar_cola(matriz,x,y,dir);
                reducir_matriz_entera(matriz);

                if (cio.kbhit())
                {
                    cio >> key(tecla);
                    switch (tecla)
                    {
                        case KEY_LEFT:
                            if(dir != 0)
                                dir = 1;
                        break;
                        case KEY_RIGHT:
                            if(dir != 1)
                                dir = 0;
                        break;
                        case KEY_UP:
                            if(dir != 3)
                                dir = 2;
                        break;
                        case KEY_DOWN:
                            if(dir != 2)
                                dir = 3;
                        break;
                        case KEY_ESC:
                            cont = 0;
                        break;
                        case 'p':
                        {
                            cio << cursorxy(MAX + 5, 6) << "Juego Pausado";
                            pase();
                            cio << cursorxy(MAX + 5 ,6) << "             ";
                        }break;
                    }
                }
                Sleep(vel);
            }
        }break;
        case '2':
            {
                cio << clear_screen;
                opcion2 = Menu2();
                switch(opcion2){
                    case '1':
                        vel = 100;
                        break;
                    case '2':
                        vel = 50;
                        break;
                    case '3':
                        vel = 25;
                        break;
                }
            }break;
        }
        cio << clear_screen;
   }while(opcion != '3');

    return 0;
}
