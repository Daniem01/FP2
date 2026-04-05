#include "MultiConjunto.h"

MultiConjunto::MultiConjunto() : num_elementos(0) {}

int MultiConjunto::buscar_indice(int v) const {
    for (int i = 0; i < num_elementos; i++) {
        if (elementos[i].valor == v) return i;
    }
    return -1;
}

int MultiConjunto::dame_num_elems() const {
    return num_elementos;
}

bool MultiConjunto::pertenece(int v) const {
    return buscar_indice(v) != -1;
}

void MultiConjunto::insertar(int v) {
    int idx = buscar_indice(v);
    if (idx != -1) {
        elementos[idx].multiplicidad++; 
    }
    else {
        elementos[num_elementos].valor = v;
        elementos[num_elementos].multiplicidad = 1; 
        num_elementos++;
    }
}

void MultiConjunto::eliminar(int v) {
    int idx = buscar_indice(v);
    if (idx != -1) {
        elementos[idx].multiplicidad--; 
        if (elementos[idx].multiplicidad == 0) {
            // Eliminar desplazando el resto 
            for (int i = idx; i < num_elementos - 1; i++) {
                elementos[i] = elementos[i + 1];
            }
            num_elementos--;
        }
    }
}