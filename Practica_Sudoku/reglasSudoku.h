#ifndef REGLAS_H
#define REGLAS_H

#include "tablero.h"
#include "celda.h"
#include <fstream>

using namespace std;

// Estructura para los bloqueos
typedef struct {
    int fila;
    int columna;
} tPosicion;

class ReglasSudoku {
private:
    Tablero tablero;
    int celdas_ocupadas;
    
    // Gestionar bloqueos
    int num_bloqueadas;
    tPosicion bloqueadas[MAX_TAM * MAX_TAM]; 

public:
    ReglasSudoku(); 

    // Consultoras 
    int dame_dimension() const; 
    Celda dame_celda(int fila, int columna) const;
    bool terminado() const;
    bool bloqueo() const;
    int dame_num_celdas_bloqueadas() const;
    void dame_celda_bloqueada(int posicion, int& fila, int& columna) const;
    bool es_valor_posible(int fila, int columna, int valor) const;
    void actualizar_bloqueos();

    // Modificadoras
    bool pon_valor(int fila, int columna, int valor);
    bool quita_valor(int fila, int columna); 
    void reset();
    void autocompletar(); 
    
    //Inicializadora
    bool carga_sudoku(ifstream& archivo);
};

#endif