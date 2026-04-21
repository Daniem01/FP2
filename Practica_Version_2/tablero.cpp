#include "tablero.h"

// Constructores
Tablero::Tablero(){
    dimension = 0;
}
Tablero::Tablero(int dimension){
    this->dimension = dimension;
}

// Metodos
int Tablero::get_dimension()const{
    return dimension;
}

Celda Tablero::get_celda(int fila, int col)const{
    return tablero[fila][col];
}

// Metodos modificadores
void Tablero::set_celda(int fila, int columna, const Celda &celda){
    tablero[fila][columna] = celda;
}