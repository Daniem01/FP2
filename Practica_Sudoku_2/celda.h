#ifndef CELDA_H
#define CELDA_H

// Definicion tEstado
typedef enum
{
    ORIGINAL,
    OCUPADA,
    VACIA
} tEstado;

// Definicion de la clase Celda
class Celda
{
private:
    int valor;
    tEstado estado;

public:
// Constructores
Celda();
Celda(int v, tEstado estado);

// Metodos
bool es_vacia() const;
bool es_original() const;
bool es_ocupada() const;
int dame_valor() const;
// Metodos modificadores
void set_valor(int v);
void set_ocupada();
void set_original();
void set_vacia();
};

#endif