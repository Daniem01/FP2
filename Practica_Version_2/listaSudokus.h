#ifndef LISTASUDOKUS_H
#define LISTASUDOKUS_H

#include "reglasSudoku.h"
#include <string>
#include "checkML.h"

class ListaSudokus {
private:
    // Puntero al array de punteros 
    ReglasSudoku** lista; 
    int contador;   // Numero de sudokus guardados
    int capacidad;

    // Metodo auxiliar doblar el tamaño del array cuando se llene
    void resize();

public:
    ListaSudokus();
    ~ListaSudokus();

    // Ponemos que no usamos ni constructor por copia ni asignacion
    ListaSudokus(const ListaSudokus& otra) = delete;
    ListaSudokus& operator=(const ListaSudokus& otra) = delete;

    // Metodos
    void insertar(const ReglasSudoku& sudoku);
    void eliminar(int indice);
    
    // Consultoras
    int get_contador() const;
    ReglasSudoku* obtener_sudoku(int indice) const;
};

#endif