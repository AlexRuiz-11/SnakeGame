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
            Version:    1.0

            Alejandro Ruiz Rubio


*************************************************************/
//---------------------------------------------------------------------
#include <iostream>
#include "ioconsole.hpp"
//#include "misc.hpp"
using namespace std;

const int MAX = 50;

typedef char filas [MAX];
typedef filas columnas [MAX];

//---------------------------------------------------------------------
unsigned Menu ()
{
	unsigned opcion;

	cio << endl;
	cio << endl;
	cio << "\tSNAKE \t\t (Version 1.0)" << endl;
	cio << endl << endl;
	cio << "\t1. - Jugar" << endl;
	cio << endl;
	cio << "\t2. - Dificultad" << endl;
	cio << endl;
	cio << "\t3. - Salir" << endl;
	cio << endl << endl << endl << endl;
	cio << "Creado por:" << endl;
	cio << "Alejandro Ruiz" << endl;
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
            if(a[x + 1][y] != ' ' && (a[x + 1][y] != 'O'))
        res = true;
            break;
        case 1:
            if(a[x - 1][y] != ' ' && (a[x - 1][y] != 'O'))
        res = true;
            break;
        case 2:
            if(a[x][y - 1] != ' ' && (a[x][y - 1] != 'O'))
        res = true;
            break;
        case 3:
            if(a[x][y + 1] != ' ' && (a[x][y + 1] != 'O'))
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
            if(a[x + 1][y] == 'O')
        res = true;
            break;
        case 1:
            if(a[x - 1][y] == 'O')
        res = true;
            break;
        case 2:
            if(a[x][y - 1] == 'O')
        res = true;
            break;
        case 3:
            if(a[x][y + 1] == 'O')
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
void rellenar_matriz(columnas &a)
{
    for(int i = 0 ; i < MAX ; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            if(i == 0 || i == (MAX - 1))
                a[i][j] = 219;
            else if(j == 0 || j == (MAX - 1))
                a[i][j] = 219;
            else
                a[i][j] = ' ';
        }
    }
}
//---------------------------------------------------------------------
void dibujar_matriz(columnas a)
{
    for(int i = 0 ; i < MAX ; i++)
    {
        for(int j = 0 ; j < MAX ; j++)
        {
            cio << a[j][i];     // j e i cambiados
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
    cio << cursorxy(MAX + 5, 3) << "SCORE: " << endl;
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
void dibujar_snake(columnas a,int i ,int j, int dir)
{
    int x = 0, y = 0;
    switch (dir)
    {
        case 0:
        {
            x = -1;
        }break;
        case 1:
        {
            x = 1;
        }break;
        case 2:
        {
            y = 1;
        }break;
        case 3:
        {
            y = -1;
        }
    }
        a[i][j] = 219;
        a[i + x][j + y] = ' ';
        cio << cursorxy(i + 1, j + 1) << a[i][j];
        cio << cursorxy(i + x + 1, j + y + 1) << a[i + x][j + y];
}
//---------------------------------------------------------------------
void manzana(columnas &a)
{
    int manx, many;

    manx = aleatorio(MAX - 2) + 1;
    many = aleatorio(MAX - 2) + 1;
    a[manx][many] = 'O';
    cio << cursorxy(manx + 1, many + 1) << a[manx][many];
}
//---------------------------------------------------------------------
int main()
{
    columnas matriz;
    int cont, dir, vel = 50;
    int x, y, score;
    unsigned tecla, opcion;

    do{
        opcion = Menu();

        dir = 0;
        x = 10;
        y = 10;
        cont = 1;
        score = 0;

        switch(opcion)
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
                }

                direccion(dir , x , y);
                dibujar_snake(matriz, x, y, dir);

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
                        }
                        break;
                    }
                }
                Sleep(vel);
            }
        }

        cio << clear_screen;

   }while(opcion != '3');

    return 0;
}
