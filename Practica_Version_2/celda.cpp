#include "celda.h"

// Constructores
Celda::Celda(){
   valor = 0;
   estado = VACIA;
}

Celda::Celda(int v, tEstado estado){
    this->valor = v;
    this->estado = estado;
}

// Metodos
bool Celda::es_vacia()const{
    return estado == VACIA;
}

bool Celda::es_original()const{
    return estado == ORIGINAL;
}

bool Celda::es_ocupada()const{
    return estado == OCUPADA;
}

int Celda::dame_valor()const{
    return valor;
}

// Metodos modificadores
void Celda::set_valor(int v){
    valor = v;
}

void Celda::set_ocupada(){
    estado = OCUPADA;
}

void Celda::set_original(){
    estado = ORIGINAL;
}

void Celda::set_vacia(){
    estado = VACIA;
}