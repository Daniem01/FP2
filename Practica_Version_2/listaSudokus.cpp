#include "listaSudokus.h"
#include<iostream>
using namespace std;

ListaSudokus::ListaSudokus(){
    capacidad = 5; 
    contador = 0;
    lista = new ReglasSudoku*[capacidad];
    // Ponemos la lista a nullptr para que no tenga basura
    for(int i = 0; i < capacidad; i++) {
        lista[i] = nullptr;
    }
}

ListaSudokus::~ListaSudokus(){
    for(int i = 0; i < contador; i++){
        delete lista[i]; // Borra el objeto Sudoku
    }
    delete[] lista;
}

void ListaSudokus::resize(){
    capacidad = capacidad * 2;
    
    // Creamos un array auxiliar para redimensionar
    ReglasSudoku **lista_aux = new ReglasSudoku*[capacidad];

    // Copiamos los punteros que hay al array auxiliar
    for(int i = 0; i < contador; i++){
        lista_aux[i] = lista[i]; 
    }
    // Los nuevos espacios que por ahora estan vacios los ponemos a nulptr
    for(int i = contador; i < capacidad; i++){
        lista_aux[i] = nullptr;
    }

    delete[] lista;
    lista = lista_aux;
}

void ListaSudokus::insertar(const ReglasSudoku& sudoku) {
    if (contador == capacidad) {
        resize();
    }

    int pos = 0;
    while (pos < contador && *lista[pos] < sudoku) {
        pos++;
    }

    for (int i = contador; i > pos; i--) {
        lista[i] = lista[i - 1];
    }

    lista[pos] = new ReglasSudoku(sudoku);

    contador++;
}

void ListaSudokus::eliminar(int indice) {
    if (indice >= 0 && indice < contador) {
        delete lista[indice]; // Liberamos la memoria
        
        // Desplazamos los punteros a la izquierda para cerrar el hueco que ha dejado el objeto eliminado
        for (int i = indice; i < contador - 1; i++) {
            lista[i] = lista[i + 1];
        }
        
        lista[contador - 1] = nullptr; // Lo ponemos a nullptr el ultimo
        contador--; // Restamos al contador
    }
}

int ListaSudokus::dame_num_elems() const{
    return contador;
}

ReglasSudoku& ListaSudokus::dame_sudoku(int indice) const{
    return *lista[indice];
}

void ListaSudokus::mostrar_lista() const {
    for (int i = 0; i < contador; i++) {
        cout << i + 1 << ": Sudoku con " << lista[i]->contar_vacias() << " casillas vacias" << endl;

        for (int k = 1; k <= 9; k++) {
            cout << "  celdas con " << k << " valores posibles: "
                << lista[i]->contar_k_opciones(k) << endl;
        }
    }
}