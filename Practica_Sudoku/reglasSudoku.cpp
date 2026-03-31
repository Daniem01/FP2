#include "reglasSudoku.h"
#include <cmath>

// Constructor
ReglasSudoku::ReglasSudoku(){
    celdas_ocupadas = 0;
    num_bloqueadas = 0;
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

bool ReglasSudoku::es_valor_posible(int fila, int columna, int valor) const {
    bool posible = true;
    int dim = dame_dimension();
    int n = sqrt(dim); // El tamaño de bloque

    // Miramos la fila
    for(int c = 0; c < dim && posible; c++){
        if(!tablero.get_celda(fila, c).es_vacia() && tablero.get_celda(fila, c).dame_valor() == valor){
            posible = false;
        }
    }

    // Miramos la columna
    for(int f = 0; f < dim && posible; f++){
        if(!tablero.get_celda(f, columna).es_vacia() && tablero.get_celda(f, columna).dame_valor() == valor){
            posible = false;
        }
    }

    // Miramos el bloque donde esta 
    int filaInicio = (fila / n) * n;
    int colInicio = (columna / n) * n;
    for(int f = filaInicio; f < filaInicio + n && posible; f++){
        for(int c = colInicio; c < colInicio + n && posible; c++){
            if(!tablero.get_celda(f, c).es_vacia() && tablero.get_celda(f, c).dame_valor() == valor){
                posible = false;
            }
        }
    }
    return posible;
}

void ReglasSudoku::actualizar_bloqueos() {
    num_bloqueadas = 0; 
    int dim = dame_dimension();

    // Recorremos buscando celdas vacias y miramos si tiene algun valor posible
    for (int f = 0; f < dim; f++) {
        for (int c = 0; c < dim; c++) {
            
            if (tablero.get_celda(f, c).es_vacia()) {
                bool hay_alguna_opcion = false;

                for (int v = 1; v <= dim && !hay_alguna_opcion; v++) {
                    if (es_valor_posible(f, c, v)) {
                        hay_alguna_opcion = true;
                    }
                }

                // Si no hay opciones estamos bloqueados
                if (!hay_alguna_opcion) {
                    bloqueadas[num_bloqueadas].fila = f;
                    bloqueadas[num_bloqueadas].columna = c;
                    num_bloqueadas++; 
                }
            }
        }
    }
}

// Modificadoras
bool ReglasSudoku::pon_valor(int fila, int columna, int valor) {
    bool exito = false;
    // Comprobamos si la celda se puede ocupar
    if (tablero.get_celda(fila, columna).es_vacia() && es_valor_posible(fila, columna, valor)) {
        Celda nueva(valor, OCUPADA); 
        tablero.set_celda(fila, columna, nueva);
        celdas_ocupadas++;
        actualizar_bloqueos();
        exito = true;
    }
    return exito;
}

bool ReglasSudoku::quita_valor(int fila, int columna) {
    bool exito = false;
    // Solo permitimos cambios si la celda es OCUPADA
    if (tablero.get_celda(fila, columna).es_ocupada()) {
        tablero.set_celda(fila, columna, Celda(0, VACIA));
        celdas_ocupadas--;
        actualizar_bloqueos();
        exito = true;
    }
    return exito;
}

void ReglasSudoku::reset() {
    // Todas las celdas ocupadas las ponemos vacias
    int dim = dame_dimension();
    for (int f = 0; f < dim; f++) {
        for (int c = 0; c < dim; c++) {
            if (tablero.get_celda(f, c).es_ocupada()) {
                tablero.set_celda(f, c, Celda(0, VACIA));
                celdas_ocupadas--;
            }
        }
    }
}

void ReglasSudoku::autocompletar() {
    int dim = dame_dimension();
    for (int f = 0; f < dim; f++) {
        for (int c = 0; c < dim; c++) {
            if (tablero.get_celda(f, c).es_vacia()) {
                int contador = 0;
                int valor_unico = 0;
                for (int v = 1; v <= dim; v++) {
                    if (es_valor_posible(f, c, v)) {
                        contador++;
                        valor_unico = v;
                    }
                }
                // Si solo hay un valor posible lo ponemos
                if (contador == 1) {
                    pon_valor(f, c, valor_unico);
                }
            }
        }
    }
}
    
//Inicializadora
bool ReglasSudoku::carga_sudoku(ifstream& archivo) {
    int dim, valor;
    archivo >> dim;
    
    // Inicializamos el tablero con la dimension que hemos leido antes
    tablero = Tablero(dim); 
    celdas_ocupadas = 0;

    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            archivo >> valor;
            if (valor == 0) {
                tablero.set_celda(i, j, Celda(0, VACIA)); // 0 Si es celda vacia
            } else {
                tablero.set_celda(i, j, Celda(valor, ORIGINAL)); // Valor si es original
                celdas_ocupadas++;
            }
        }
    }

    // Actualizamos los bloqueos por si vienen mal y bloqueados por lo que sea
    actualizar_bloqueos();
    return true;
}