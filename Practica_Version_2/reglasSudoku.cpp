#include "reglasSudoku.h"
#include <cmath>

// Constructor
ReglasSudoku::ReglasSudoku(){
    celdas_ocupadas = 0;
    num_bloqueadas = 0;
    // Inicializamos el array dinamico a nullptr
    for (int i = 0; i < MAX_TAM * MAX_TAM; i++) {
        bloqueadas[i] = nullptr;
    }
}

// Metodos para la gestion de memoria dinamica
ReglasSudoku::~ReglasSudoku(){
    for(int i = 0; i < num_bloqueadas; i++){
        // Borramos las direcciones que hay en bloqueadas y las ponemos a nullptr
        delete bloqueadas[i];
        bloqueadas[i] = nullptr;
    }
}

ReglasSudoku::ReglasSudoku(const ReglasSudoku &sudoku){
    // Copiamos los atributos
    this->num_bloqueadas = sudoku.num_bloqueadas;
    this->celdas_ocupadas = sudoku.celdas_ocupadas;
    this->tablero = sudoku.tablero;
    this->info_valores_no_validos = sudoku.info_valores_no_validos;

    // Copiamos el array bloqueadas
    for(int i = 0; i < num_bloqueadas; i++){
        this->bloqueadas[i] = new tPosicion;
        this->bloqueadas[i]->fila = sudoku.bloqueadas[i]->fila;
        this->bloqueadas[i]->columna = sudoku.bloqueadas[i]->columna;
    }

    // Para que el resto del array no este sucio lo ponemos a nullptr desde num_bloqueadas en adelante
    for (int i = num_bloqueadas; i < MAX_TAM * MAX_TAM; ++i) {
        this->bloqueadas[i] = nullptr;
    }
}

ReglasSudoku& ReglasSudoku::operator=(const ReglasSudoku &sudoku) {
    // Si no son iguales, procedemos a hacer la asignacion
    if (this != &sudoku) {
        
        //  Primero antes de copiar nada debemos liberar la memoria que tuviera ocupada
        for (int i = 0; i < num_bloqueadas; ++i) {
            if (bloqueadas[i] != nullptr) {
                delete bloqueadas[i];
                bloqueadas[i] = nullptr;
            }
        }

        // Copiamos los atributos estaticos
        this->num_bloqueadas = sudoku.num_bloqueadas;
        this->celdas_ocupadas = sudoku.celdas_ocupadas;
        this->tablero = sudoku.tablero;
        this->info_valores_no_validos = sudoku.info_valores_no_validos;

        // Copiamos bloqueadas reservando la memoria
        for (int i = 0; i < num_bloqueadas; ++i) {
            this->bloqueadas[i] = new tPosicion;
            this->bloqueadas[i]->fila = sudoku.bloqueadas[i]->fila;
            this->bloqueadas[i]->columna = sudoku.bloqueadas[i]->columna;
        }

        // El resto del array lo ponemos a nullptr
        for (int i = num_bloqueadas; i < MAX_TAM * MAX_TAM; ++i) {
            this->bloqueadas[i] = nullptr;
        }
    }

    return *this;
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
    fila = bloqueadas[posicion]->fila; 
    columna = bloqueadas[posicion]->columna;
}

bool ReglasSudoku::es_valor_posible(int fila, int columna, int valor) const {
    // El valor es posible si no pertenece al multiconjunto de esa celda 
    return !info_valores_no_validos.no_validos[fila][columna].pertenece(valor);
}

void ReglasSudoku::actualizar_bloqueos() {
    // Limpieamos primero los bloqueos antiguos
    for (int i = 0; i < num_bloqueadas; i++) {
        delete bloqueadas[i];
        bloqueadas[i] = nullptr;
    }

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
                    bloqueadas[num_bloqueadas] = new tPosicion;
                    bloqueadas[num_bloqueadas]->fila = f;
                    bloqueadas[num_bloqueadas]->columna = c;
                    num_bloqueadas++; 
                }
            }
        }
    }
}

// Modificadoras
bool ReglasSudoku::pon_valor(int fila, int columna, int valor) {
    bool exito = false;

    // Comprobamos si la celda está vacía y si el valor es valido usando el multiconjunto
    if (tablero.get_celda(fila, columna).es_vacia() && es_valor_posible(fila, columna, valor)) {
        Celda nueva(valor, OCUPADA);
        tablero.set_celda(fila, columna, nueva);

        //Notificar a los vecinos 
        actualizar_vecinos(fila, columna, valor, true);

        celdas_ocupadas++; 
        actualizar_bloqueos(); // Refrescamos los bloqueos que pueda haber
        exito = true;
    }
    return exito;
}

bool ReglasSudoku::quita_valor(int fila, int columna) {
    bool exito = false;

    // Solo permitimos quitar si la celda es OCUPADA (no ORIGINAL) 
    if (tablero.get_celda(fila, columna).es_ocupada()) {
        int valor_a_quitar = tablero.get_celda(fila, columna).dame_valor();

        // Ponemos la celda a VACIA  
        tablero.set_celda(fila, columna, Celda(0, VACIA));

        //Avisar a los vecinos que el valor se ha ido 
        actualizar_vecinos(fila, columna, valor_a_quitar, false);

        celdas_ocupadas--; 
        actualizar_bloqueos(); 
        exito = true;
    }
    return exito;
}

void ReglasSudoku::reset() {
    // Primero limpiamos
    for (int i = 0; i < num_bloqueadas; i++) {
        delete bloqueadas[i];
        bloqueadas[i] = nullptr;
    }
    num_bloqueadas = 0;
    
    // Todas las celdas ocupadas las ponemos vacias
    int dim = dame_dimension();
    for (int f = 0; f < dim; f++) {
        for (int c = 0; c < dim; c++) {
            if (tablero.get_celda(f, c).es_ocupada()) {
                int v = tablero.get_celda(f, c).dame_valor();
                actualizar_vecinos(f, c, v, false);
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
                actualizar_vecinos(i, j, valor, true);
            }
        }
    }

    // Actualizamos los bloqueos por si vienen mal y bloqueados por lo que sea
    actualizar_bloqueos();
    return true;
}

void ReglasSudoku::actualizar_vecinos(int f, int c, int v, bool poner) {
    int dim = dame_dimension();
    int n = static_cast<int>(sqrt(dim)); 

    for (int i = 0; i < dim; i++) {
        if (poner) {
            info_valores_no_validos.no_validos[f][i].insertar(v);
            info_valores_no_validos.no_validos[i][c].insertar(v);
        } else {
            info_valores_no_validos.no_validos[f][i].eliminar(v);
            info_valores_no_validos.no_validos[i][c].eliminar(v);
        }
    }

    int filaInicio = (f / n) * n;
    int colInicio = (c / n) * n;
    for (int i = filaInicio; i < filaInicio + n; i++) {
        for (int j = colInicio; j < colInicio + n; j++) {
            // Solo actualizamos si no esta en la misma fila o columna sinono
            if (i != f && j != c) {
                if (poner) info_valores_no_validos.no_validos[i][j].insertar(v);
                else info_valores_no_validos.no_validos[i][j].eliminar(v);
            }
        }
    }
}

// Funcion auxiliar para contar celdas que estan vacias
int ReglasSudoku::contar_vacias() const {
    int dim = tablero.get_dimension();
    return (dim * dim) - celdas_ocupadas;
}

// Funcion auxiliar para contar cuántas celdas tienen exactamente k candidatos
int ReglasSudoku::contar_k_opciones(int k) const {
    int contador = 0;
    int dim = tablero.get_dimension();
    for (int f = 0; f < dim; f++) {
        for (int c = 0; c < dim; c++) {
            if (tablero.get_celda(f, c).es_vacia()) {
                int opciones = 0;
                for (int v = 1; v <= dim; v++) {
                    if (es_valor_posible(f, c, v)) opciones++;
                }
                if (opciones == k) contador++;
            }
        }
    }
    return contador;
}

bool operator<(const ReglasSudoku& s1, const ReglasSudoku& s2) {
    int v1 = s1.contar_vacias();
    int v2 = s2.contar_vacias(); 
    bool sol = false;
    bool decidido = false; 

    if (v1 < v2) {
        sol = true;
        decidido = true;
    } 
    else if (v1 > v2) {
        sol = false;
        decidido = true;
    }

    // Desempate por si son iguales en celdas vacias
    int k = 1;
    while (k <= 9 && !decidido) {
        int n1 = s1.contar_k_opciones(k);
        int n2 = s2.contar_k_opciones(k);
    
        if (n1 > n2) {
            sol = true;
            decidido = true;
        } 
        else if (n1 < n2) {
            sol = false;
            decidido = true;
        }
        k++;
    }
    
    return sol;
}

bool operator==(const ReglasSudoku&s1, const ReglasSudoku& s2) {
    bool sol = true;
    if (s1.contar_vacias() != s2.contar_vacias()) {
        sol = false;
    }

    int k = 1;
    while (k <= 9 && sol) { 
        if (s1.contar_k_opciones(k) != s2.contar_k_opciones(k)) {
            sol = false;
        }
        k++;
    }
    return sol;
}