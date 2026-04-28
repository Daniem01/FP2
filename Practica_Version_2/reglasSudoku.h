#ifndef REGLAS_H
#define REGLAS_H

#include "tablero.h"
#include "MultiConjunto.h"
#include "celda.h"
#include <fstream>
#include "checkML.h"

using namespace std;

class ReglasSudoku
{
    friend bool operator<(const ReglasSudoku& s1, const ReglasSudoku& s2);
    friend bool operator==(const ReglasSudoku& s1, const ReglasSudoku& s2);
private:
    // Estructura para los bloqueos
    typedef struct
    {
        int fila;
        int columna;
    } tPosicion;

    Tablero tablero;
    int celdas_ocupadas;

    // Gestionar bloqueos
    int num_bloqueadas;
    tPosicion* bloqueadas[MAX_TAM * MAX_TAM];

    typedef struct
    {
        int nFilas;
        int nColumnas;
        MultiConjunto no_validos[MAX_TAM][MAX_TAM];
    } tValores_invalidos;

    tValores_invalidos info_valores_no_validos;

    // Metodos auxiliares
    void actualizar_vecinos(int f, int c, int v, bool poner);
    int contar_vacias() const;
    int contar_k_opciones(int k) const;

public:
    ReglasSudoku();

    // Gestion de memoria dinamica
    // Destructor
    ~ReglasSudoku();
    // Constructor
    ReglasSudoku(const ReglasSudoku &sudoku);
    // Sobrecarga de operadores
    ReglasSudoku& operator=(const ReglasSudoku &sudoku);

    // Consultoras
    int dame_dimension() const;
    Celda dame_celda(int fila, int columna) const;
    bool terminado() const;
    bool bloqueo() const;
    int dame_num_celdas_bloqueadas() const;
    void dame_celda_bloqueada(int posicion, int &fila, int &columna) const;
    bool es_valor_posible(int fila, int columna, int valor) const;
    void actualizar_bloqueos();

    // Modificadoras
    bool pon_valor(int fila, int columna, int valor);
    bool quita_valor(int fila, int columna);
    void reset();
    void autocompletar();

    // Inicializadora
    bool carga_sudoku(ifstream &archivo);
};



#endif