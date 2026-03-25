#include "reglasSudoku.h"

// Constructor
ReglasSudoku::ReglasSudoku(){
    celdas_ocupadas = 0;
}

// Metodos
// Consultoras
int ReglasSudoku::dame_dimension()const{
    return tablero.get_dimension();
}

Celda ReglasSudoku::dame_celda(int fila, int columna)const{
    return tablero.get_celda(fila, columna);
}

bool ReglasSudoku::terminado()const{
    int dimension = tablero.get_dimension();

    return celdas_ocupadas == dimension * dimension;
}

bool ReglasSudoku::bloqueo()const{
    return num_bloqueadas > 0;
}

int ReglasSudoku::dame_num_celdas_bloqueadas()const{
    return num_bloqueadas;
}

void ReglasSudoku::dame_celda_bloqueada(int posicion, int &fila, int &columna)const{
    fila = bloqueadas[posicion].fila; 
    columna = bloqueadas[posicion].columna;
}

bool ReglasSudoku::es_valor_posible(int fila, int columna, int valor) const{

}

// Modificadoras
bool ReglasSudoku::pon_valor(int fila, int columna, int valor){

}

bool ReglasSudoku::quita_valor(int fila, int columna){
    // Falta terminar con comprobaciones
    Celda celda(0, VACIA);
    tablero.set_celda(fila, columna, celda);
}

void ReglasSudoku::reset(){

}

void ReglasSudoku::autocompletar(){

}
    
//Inicializadora
bool ReglasSudoku::carga_sudoku(ifstream& archivo){

}