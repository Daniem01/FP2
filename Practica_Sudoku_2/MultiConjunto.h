#ifndef MULTICONJUNTO_H
#define MULTICONJUNTO_H

// Estructura para almacenar el valor y la multiplicidad
typedef struct {
    int valor;
    int multiplicidad;
} tElementoMC;

class MultiConjunto {
private:
    static const int MAX_VALORES = 9; 
    tElementoMC elementos[MAX_VALORES];
    int num_elementos;

    int buscar_indice(int v) const;

public:
    MultiConjunto(); // Constructor 
    int dame_num_elems() const; 
    bool pertenece(int v) const; 
    void insertar(int v); // Incrementa multiplicidad o añade un nuevo valor
    void eliminar(int v); // Decrementa multiplicidad o elimina si llega a 0 
};

#endif
