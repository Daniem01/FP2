#ifndef REGLAS_H
#define REGLAS_H
#include "tablero.h"
#include "celda.h"
#include <fstream>

using namespace std;

const int MAX_TAM = 10000;

typedef struct{
    int celdas;
    int tam;
    Celda bloqueadas[];
}tContador;

class Reglas{
    private:
        Tablero tablero;
        tContador contador;

    public:
    // Constructores
    Reglas();

    // Metodos
    int dameDimension();
    int dameCelda(int fila, int columna);
    bool terminado();
    bool bloqueo();
    int dame_num_celdas_bloqueadas();
    Celda dame_celda_bloqueada(int posicion, int& fila, int& columna);
    bool es_valor_posible(int fila, int columna, int valor);

    // Metodos modificadores
    bool pon_valor(int fila, int columna, int valor);
    bool quita_valor(int fila, int columna);
    void reset();
    void autocompletar();
    bool carga_sudoku(ifstream& archivo);

};
#endif