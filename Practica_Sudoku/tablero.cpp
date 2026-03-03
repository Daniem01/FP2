#include "tablero.h"

// Constructores
Tablero::Tablero(){
    dimension = 0;
    tMatriz tablero[dimension][dimension];
}
Tablero::Tablero(int dimension){
    this->dimension = dimension;
    tMatriz tablero[dimension][dimension];
}

// Metodos
int Tablero::get_dimension()const{
    return dimension;
}

int Tablero::get_valor(int fila, int col)const{
    return tablero[fila][col].dame_valor();
}

// Metodos modificadores
void Tablero::set_celda(int fila, int columna, int valor){
    tablero[fila][columna].set_valor(valor);
}