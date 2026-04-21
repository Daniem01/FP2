#include "MultiConjunto.h"

MultiConjunto::MultiConjunto() : num_elementos(0) {}

int MultiConjunto::buscar_indice(int v) const {
    int i = 0, resultado = -1;
    bool encontrado = false;

    while(i < num_elementos && !encontrado){
        if (elementos[i].valor == v){
            resultado = i;
            encontrado = true;
        }
        i++;
    }
    return resultado;
}

int MultiConjunto::dame_num_elems() const {
    return num_elementos;
}

bool MultiConjunto::pertenece(int v) const {
    return buscar_indice(v) != -1;
}

void MultiConjunto::insertar(int v) {
    int i = buscar_indice(v);
    if (i != -1) {
        elementos[i].multiplicidad++; 
    }
    else {
        elementos[num_elementos].valor = v;
        elementos[num_elementos].multiplicidad = 1; 
        num_elementos++;
    }
}

void MultiConjunto::eliminar(int v) {
    int i = buscar_indice(v);
    if (i != -1) {
        elementos[i].multiplicidad--; 
        if (elementos[i].multiplicidad == 0) {
            // Eliminamos desplazando el resto 
            for (int j = i; j < num_elementos - 1; j++) {
                elementos[j] = elementos[j + 1];
            }
            num_elementos--;
        }
    }
}