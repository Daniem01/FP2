#include "reglasSudoku.h"

// Constructor
Reglas::Reglas(){
    contador.celdas = 0;
    contador.tam = 0;
    contador.bloqueadas[MAX_TAM];
}

// Metodos

int Reglas::dameDimension(){
    return tablero.get_dimension();
}

int Reglas::dameCelda(int fila, int columna){
    return tablero.get_valor(fila, columna);
}

bool Reglas::terminado(){
    int dimension = tablero.get_dimension();

    return contador.celdas == dimension * dimension;
}

bool Reglas::bloqueo(){
    return contador.tam != 0;
}

int Reglas::dame_num_celdas_bloqueadas(){
    return contador.tam;
}

Celda Reglas::dame_celda_bloqueada(int posicion, int &fila, int &columna){
    Celda celda = contador.bloqueadas[posicion - 1];  
}