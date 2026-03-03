#ifndef TABLERO_H
#define TABLERO_H
#include "celda.h"

const int MAX_TAM = 50;
typedef Celda tMatriz[MAX_TAM][MAX_TAM];

class Tablero
{
private:
    int dimension;
    tMatriz tablero;

public:
// Constructores
Tablero();
Tablero(int dimension);

// Metodos
int get_dimension()const;
int get_valor(int fila, int col)const;
// Metodos modificadores
void set_celda(int fila, int columna, int valor);
};

#endif